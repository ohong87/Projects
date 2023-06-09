package com.example.minesweeper;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class DisplayMessageActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_display_message);

        Intent intent = getIntent();
        String time = intent.getStringExtra("time");
        String result = intent.getStringExtra("result");
        TextView textView = (TextView) findViewById(R.id.textView);

        if (result.equals("w")) textView.setText("Used " + time + " seconds." + "\n" + "You won." + "\n" + "Good job!");
        else textView.setText("Used " + time + " seconds." + "\n" + "You Lost.");
    }

    public void backToMain(View view) {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
    }
}
