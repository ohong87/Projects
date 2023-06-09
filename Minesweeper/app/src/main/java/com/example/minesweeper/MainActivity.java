package com.example.minesweeper;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import androidx.appcompat.app.AppCompatActivity;
import androidx.gridlayout.widget.GridLayout;

import android.content.res.Resources;
import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;


import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    Grid masterGrid = new Grid();
    private static final int COLUMN_COUNT = 8;
    private int clock = 0;
    private boolean running = true;
    private boolean isGameOver = false;
    private boolean hasWon = false;

    // save the TextViews of all cells in an array, so later on,
    // when a TextView is clicked, we know which cell it is
    private ArrayList<TextView> cell_tvs;

    private int dpToPixel(int dp) {
        float density = Resources.getSystem().getDisplayMetrics().density;
        return Math.round(dp * density);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (savedInstanceState != null) {
            clock = savedInstanceState.getInt("clock");
            running = savedInstanceState.getBoolean("running");
        }

        runTimer();

        cell_tvs = new ArrayList<TextView>();

        // Method (2): add four dynamically created cells
        GridLayout grid = (GridLayout) findViewById(R.id.gridLayout01);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 8; j++) {
                TextView tv = new TextView(this);
                tv.setId(i * 8 + j);
                tv.setHeight(dpToPixel(34));
                tv.setWidth(dpToPixel(34));
                tv.setTextSize(20);//dpToPixel(32) );
                tv.setTextAlignment(TextView.TEXT_ALIGNMENT_CENTER);
                tv.setTextColor(Color.BLACK);
                tv.setBackgroundColor(Color.GREEN);
                tv.setOnClickListener(this::onClickTV);

                GridLayout.LayoutParams lp = new GridLayout.LayoutParams();
                lp.setMargins(dpToPixel(2), dpToPixel(2), dpToPixel(2), dpToPixel(2));
                lp.rowSpec = GridLayout.spec(i);
                lp.columnSpec = GridLayout.spec(j);

                grid.addView(tv, lp);

                cell_tvs.add(tv);
            }
        }
        masterGrid.setValues();
        final TextView modeView = (TextView) findViewById(R.id.textView2);
        modeView.setTextColor(Color.GRAY);
    }

    private int findIndexOfCellTextView(TextView tv) {
        for (int n=0; n<cell_tvs.size(); n++) {
            if (cell_tvs.get(n) == tv)
                return n;
        }
        return -1;
    }

    // changes btwn mine and flag mode
    public void onClickMode(View view){
        final TextView modeView = (TextView) findViewById(R.id.textView2);

        if (masterGrid.isFlagMode()) {
            masterGrid.setMineMode();
            modeView.setText(R.string.pick);
            modeView.setTextColor(Color.GRAY);
        } else {
            modeView.setText(R.string.flag);
            masterGrid.setFlagMode();
        }
    }

    public void onClickTV(View view){
        TextView tv = (TextView) view;
        int n = findIndexOfCellTextView(tv);
        int i = n/COLUMN_COUNT;
        int j = n%COLUMN_COUNT;
        final TextView modeView = (TextView) findViewById(R.id.textView2);

        //(********************Mine mode***************************
        if(masterGrid.isMineMode()){
            if(isGameOver){
                final TextView timeView = (TextView) findViewById(R.id.textView);
                Intent intent = new Intent(this, DisplayMessageActivity.class);
                intent.putExtra("time",timeView.getText());

                if(hasWon){
                    intent.putExtra("result", "w");
                } else{
                    intent.putExtra("result", "l");
                }
                startActivity(intent);
            }

            if(masterGrid.getValues(i,j) != 0 && !masterGrid.getCell(i,j).getFlagState())
            {
                tv.setText(String.valueOf(masterGrid.getValues(i,j))); // reveal cell
                masterGrid.getCell(i,j).setReveal(); // update cell state

                tv.setTextColor(Color.GRAY);
                tv.setBackgroundColor(Color.LTGRAY);

                masterGrid.setPick(i,j);
                if(this.isOver())
                {
                    running = false;
                    this.revealBombs();
                    isGameOver = true;
                    hasWon = true;
                }

            } else if (masterGrid.getValues(i,j) == 0 && !masterGrid.getCell(i,j).getBombState() && !masterGrid.getCell(i,j).getFlagState()) {
                masterGrid.getCell(i,j).setReveal();

                tv.setTextColor(Color.GRAY);
                tv.setBackgroundColor(Color.LTGRAY);

                masterGrid.setPick(i,j);
                this.revealCells();
                if(this.isOver()){
                    running = false;
                    this.revealBombs();
                    isGameOver = true;
                    hasWon = true;
                }

            }

            if(masterGrid.getCell(i,j).getBombState() && !masterGrid.getCell(i,j).getFlagState()) {
                running = false;
                tv.setText(R.string.mine); // reveal bomb
                masterGrid.setGameEnd();
                masterGrid.getCell(i,j).setReveal(); // update cell state
                tv.setTextColor(Color.GRAY);
                tv.setBackgroundColor(Color.LTGRAY);
                this.revealBombs();
                isGameOver = true;
            }

        } else {
            //**************************FLAG MODE*******************************
            final TextView flagView = (TextView) findViewById(R.id.textView10);

            if(!masterGrid.getCell(i,j).getReveal() && !masterGrid.getCell(i,j).getFlagState()) {
                tv.setText(R.string.flag);

                masterGrid.getCell(i,j).setFlag(true);
                masterGrid.setFlag(i,j);

                flagView.setText(String.valueOf(4 - masterGrid.getFlagsPlaced()));
            } else if(!masterGrid.getCell(i,j).getReveal() && masterGrid.getCell(i,j).getFlagState()){
                masterGrid.getCell(i,j).setFlag(false);
                masterGrid.removeFlag(i,j);
                flagView.setText(String.valueOf(4 - masterGrid.getFlagsPlaced()));

                tv.setText("");
            }
        }
    }

    public void onSaveInstanceState(Bundle savedInstanceState) {
        super.onSaveInstanceState(savedInstanceState);
        savedInstanceState.putInt("clock", clock);
        savedInstanceState.putBoolean("running", running);
    }

    private void runTimer() {
        final TextView timeView = (TextView) findViewById(R.id.textView);
        final Handler handler = new Handler();

        handler.post(new Runnable() {
            @Override
            public void run() {
                int hours =clock/3600;
                int minutes = (clock%3600) / 60;
                int seconds = clock%60;
                String time = String.format("%03d", seconds);
                timeView.setText(time);

                if (running) {
                    clock++;
                }
                handler.postDelayed(this, 1000);
            }
        });
    }

    private void revealCells(){
        TextView tv = new TextView(this);
        final TextView flagView = (TextView) findViewById(R.id.textView10);

        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 8; c++){
                if(masterGrid.getCell(r,c).getReveal()){
                    tv = findViewById(r*8+c);
                    tv.setTextColor(Color.GRAY);
                    tv.setBackgroundColor(Color.LTGRAY);

                    if(masterGrid.getCell(r,c).getValue() > 0){
                        tv.setText(String.valueOf(masterGrid.getValues(r,c))); // reveal cell
                    }

                    if(masterGrid.getCell(r,c).getFlagState()){
                        masterGrid.getCell(r,c).setFlag(false);
                        masterGrid.removeFlag(r,c);

                        flagView.setText(String.valueOf(4 - masterGrid.getFlagsPlaced()));

                        tv.setText("");
                    }
                }
            }
        }
    }

    private boolean isOver(){
        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 8; c++) {
                if(!masterGrid.getCell(r,c).getBombState() && !masterGrid.getCell(r,c).getReveal()){
                    return false;
                }
            }
        }
        return true;
    }

    private void revealBombs(){
        TextView tv = new TextView(this);
        final TextView flagView = (TextView) findViewById(R.id.textView10);

        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 8; c++){
                if(masterGrid.getCell(r,c).getBombState()){
                    tv = findViewById(r*8+c);
                    tv.setText(R.string.mine); // reveal bomb
                    tv.setBackgroundColor(Color.LTGRAY);

                    if(masterGrid.getCell(r,c).getFlagState()){
                        masterGrid.getCell(r,c).setFlag(false);
                        masterGrid.removeFlag(r,c);

                        flagView.setText(String.valueOf(4 - masterGrid.getFlagsPlaced()));
                    }
                }
            }
        }
    }
}

