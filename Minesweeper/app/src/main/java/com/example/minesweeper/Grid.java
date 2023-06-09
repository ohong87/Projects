package com.example.minesweeper;

import java.lang.reflect.Array;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

public class Grid {
    private Cell grid[][];
    private boolean isMine;
    private int flagsPlaced;
    private boolean isEnd;

    public Grid(){
        grid = new Cell[10][8];
        isMine = true;
        flagsPlaced = 0;
        isEnd = false;

        // initializes grid
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 8; j++){
                grid[i][j] = new Cell();
            }
        }

        //sets bombs randomly
        int bombCount = 0;
        while(bombCount < 4){
            Random rand = new Random();
            int bombRow = rand.nextInt(10); // bomb #
            int bombCol = rand.nextInt(8); // bomb #

            if (!grid[bombRow][bombCol].getBombState()) {
                grid[bombRow][bombCol].setBomb();
                bombCount++;
            }
        }
    }

    public void setValues(){
//        grid[1][1].setBomb(); //tester
//        grid[1][2].setBomb(); //tester

//        grid[1][2].setBomb(); //tester


        //loops thru for each cell in the grid
        for(int r = 0; r < 10; r++){
            for(int c = 0; c < 8; c++){

                if(grid[r][c].getBombState()){ // if bomb then skip
                    continue;
                }

                //checks all 8 adjacent for each cell
                for(int i = 0; i < 8; i++){
                    int value = 0;

                    if(r == 0 && c == 0){ // top left corner
                        if (grid[r][c + 1].getBombState()) value++; // mid right

                        if (grid[r + 1][c].getBombState()) value++; // bottom mid
                        if (grid[r + 1][c + 1].getBombState()) value++; // bottom right
//                        System.out.println(value);
//                        System.out.println(grid[r][c].getBombState());
                    } else if(r == 0 && c == 7){ // top right corner
                        if (grid[r][c - 1].getBombState()) value++; // mid left

                        if (grid[r + 1][c - 1].getBombState()) value++; // bottom left
                        if (grid[r + 1][c].getBombState()) value++; // bottom mid
                    } else if(r == 9 && c == 0){ // bottom left corner
                        if (grid[r - 1][c].getBombState()) value++; // top mid
                        if (grid[r - 1][c + 1].getBombState()) value++; // top right

                        if (grid[r][c + 1].getBombState()) value++; // mid right
                    } else if(r == 9 && c == 7){ // bottom right corner
                        if (grid[r - 1][c - 1].getBombState()) value++; // top left
                        if (grid[r - 1][c].getBombState()) value++; // top mid

                        if (grid[r][c - 1].getBombState()) value++; // mid left
                    } else if(r == 0){ // top row
                        if (grid[r][c - 1].getBombState()) value++; // mid left
                        if (grid[r][c + 1].getBombState()) value++; // mid right

                        if (grid[r + 1][c - 1].getBombState()) value++; // bottom left
                        if (grid[r + 1][c].getBombState()) value++; // bottom mid
                        if (grid[r + 1][c + 1].getBombState()) value++; // bottom right
                    } else if(r == 9){ // bottom row
                        if (grid[r - 1][c - 1].getBombState()) value++; // top left
                        if (grid[r - 1][c].getBombState()) value++; // top mid
                        if (grid[r - 1][c + 1].getBombState()) value++; // top right

                        if (grid[r][c - 1].getBombState()) value++; // mid left
                        if (grid[r][c + 1].getBombState()) value++; // mid right
                    } else if(c == 0){ // left col
                        if (grid[r - 1][c].getBombState()) value++; // top mid
                        if (grid[r - 1][c + 1].getBombState()) value++; // top right

                        if (grid[r][c + 1].getBombState()) value++; // mid right

                        if (grid[r + 1][c].getBombState()) value++; // bottom mid
                        if (grid[r + 1][c + 1].getBombState()) value++; // bottom right
                    } else if(c == 7){ // right col
                        if (grid[r - 1][c - 1].getBombState()) value++; // top left
                        if (grid[r - 1][c].getBombState()) value++; // top mid

                        if (grid[r][c - 1].getBombState()) value++; // mid left

                        if (grid[r + 1][c - 1].getBombState()) value++; // bottom left
                        if (grid[r + 1][c].getBombState()) value++; // bottom mid
                    } else { // others
                        if (grid[r - 1][c - 1].getBombState()) value++; // top left
                        if (grid[r - 1][c].getBombState()) value++; // top mid
                        if (grid[r - 1][c + 1].getBombState()) value++; // top right

                        if (grid[r][c - 1].getBombState()) value++; // mid left
                        if (grid[r][c + 1].getBombState()) value++; // mid right

                        if (grid[r + 1][c - 1].getBombState()) value++; // bottom left
                        if (grid[r + 1][c].getBombState()) value++; // bottom mid
                        if (grid[r + 1][c + 1].getBombState()) value++; // bottom right
                    }
                    grid[r][c].setValue(value);
//                    System.out.println(grid[0][0].getValue());

                }
            }
        }
//        System.out.println(grid[0][2].getValue());
    }
    public void setMineMode() { isMine = true; }
    public void setFlagMode() { isMine = false; }
    public void setFlag(int r, int c) {
        if(!grid[r][c].getReveal()){
            flagsPlaced++;
            grid[r][c].setFlag(true);
        }
//        System.out.println(flagsPlaced);
    }
    public void removeFlag(int r, int c){
        flagsPlaced--;
        grid[r][c].setFlag(false);
    }
    public void setGameEnd() { isEnd = true; }
    public void setPick(int r, int c){
        // reveal all adjacent squares that arent numbers using BFS

        Queue <int[]> q = new LinkedList<>();
        Boolean visited[][] = new Boolean[10][8];

        // initializes visited
        for(int row = 0; row < 10; row++){
            for(int col = 0; col < 8; col++){
                visited[row][col] = false;
            }
        }

        q.add(new int[]{r, c}); // add selected pos to queue

        while(!q.isEmpty()){ // check for already revealed?
            int temp[] = q.poll(); // remove from top of queue
            int tempR = temp[0];
            int tempC = temp[1];

            // if current is a #, then skip and reveal as explore
            if(grid[tempR][tempC].getValue() > 0){
                visited[tempR][tempC] = true;
                grid[tempR][tempC].setReveal();
                continue;
            }

            // going through all the neighbors if not a number
            if(tempR == 0 && tempC == 0){ // top left corner
                if (!visited[tempR][tempC+1]){ // mid right visited?
                    q.add(new int[]{tempR, tempC+1});
                    visited[tempR][tempC+1] = true;
                    grid[tempR][tempC+1].setReveal();
                }
                if (!visited[tempR+1][tempC]){ // bottom mid visited?
                    q.add(new int[]{tempR+1, tempC});
                    visited[tempR+1][tempC] = true;
                    grid[tempR+1][tempC].setReveal();

                }
                if (!visited[tempR+1][tempC+1]){ // bottom right visited?
                    q.add(new int[]{tempR+1, tempC+1});
                    visited[tempR+1][tempC+1] = true;
                    grid[tempR+1][tempC+1].setReveal();

                }
            } else if(tempR == 0 && tempC == 7){ // top right corner
                if (!visited[tempR][tempC-1]){ // mid left visited?
                    q.add(new int[]{tempR, tempC-1});
                    visited[tempR][tempC-1] = true;
                    grid[tempR][tempC-1].setReveal();

                }
                if (!visited[tempR+1][tempC-1]){ // bottom left visited?
                    q.add(new int[]{tempR+1, tempC-1});
                    visited[tempR+1][tempC-1] = true;
                    grid[tempR+1][tempC-1].setReveal();

                }
                if (!visited[tempR+1][tempC]){ // bottom mid visited?
                    q.add(new int[]{tempR+1, tempC});
                    visited[tempR+1][tempC] = true;
                    grid[tempR+1][tempC].setReveal();

                }
            } else if(tempR == 9 && tempC == 0){ // bottom left corner
                if (!visited[tempR-1][tempC]){ // top mid visited?
                    q.add(new int[]{tempR-1, tempC});
                    visited[tempR-1][tempC] = true;
                    grid[tempR-1][tempC].setReveal();

                }
                if (!visited[tempR-1][tempC+1]){ // top right visited?
                    q.add(new int[]{tempR-1, tempC+1});
                    visited[tempR-1][tempC+1] = true;
                    grid[tempR-1][tempC+1].setReveal();

                }
                if (!visited[tempR][tempC+1]){ // mid right visited?
                    q.add(new int[]{tempR, tempC+1});
                    visited[tempR][tempC+1] = true;
                    grid[tempR][tempC+1].setReveal();
                }
            } else if(tempR == 9 && tempC == 7){ // bottom right corner
                if (!visited[tempR-1][tempC-1]){ // top left visited?
                    q.add(new int[]{tempR-1, tempC-1});
                    visited[tempR-1][tempC-1] = true;
                    grid[tempR-1][tempC-1].setReveal();

                }
                if (!visited[tempR-1][tempC]){ // top mid visited?
                    q.add(new int[]{tempR-1, tempC});
                    visited[tempR-1][tempC] = true;
                    grid[tempR-1][tempC].setReveal();

                }
                if (!visited[tempR][tempC-1]){ // mid left visited?
                    q.add(new int[]{tempR, tempC-1});
                    visited[tempR][tempC-1] = true;
                    grid[tempR][tempC-1].setReveal();

                }
            } else if(tempR == 0){ // top row
                if (!visited[tempR][tempC-1]){ // mid left visited?
                    q.add(new int[]{tempR, tempC-1});
                    visited[tempR][tempC-1] = true;
                    grid[tempR][tempC-1].setReveal();

                }
                if (!visited[tempR][tempC+1]){ // mid right visited?
                    q.add(new int[]{tempR, tempC+1});
                    visited[tempR][tempC+1] = true;
                    grid[tempR][tempC+1].setReveal();


                }
                if (!visited[tempR+1][tempC-1]){ // bottom left visited?
                    q.add(new int[]{tempR+1, tempC-1});
                    visited[tempR+1][tempC-1] = true;
                    grid[tempR+1][tempC-1].setReveal();

                }
                if (!visited[tempR+1][tempC]){ // bottom mid visited?
                    q.add(new int[]{tempR+1, tempC});
                    visited[tempR+1][tempC] = true;
                    grid[tempR+1][tempC].setReveal();

                }
                if (!visited[tempR+1][tempC+1]){ // bottom right visited?
                    q.add(new int[]{tempR+1, tempC+1});
                    visited[tempR+1][tempC+1] = true;
                    grid[tempR+1][tempC+1].setReveal();

                }
            } else if(tempR == 9){ // bottom row
                if (!visited[tempR-1][tempC-1]){ // top left visited?
                    q.add(new int[]{tempR-1, tempC-1});
                    visited[tempR-1][tempC-1] = true;
                    grid[tempR-1][tempC-1].setReveal();

                }
                if (!visited[tempR-1][tempC]){ // top mid visited?
                    q.add(new int[]{tempR-1, tempC});
                    visited[tempR-1][tempC] = true;
                    grid[tempR-1][tempC].setReveal();

                }
                if (!visited[tempR-1][tempC+1]){ // top right visited?
                    q.add(new int[]{tempR-1, tempC+1});
                    visited[tempR-1][tempC+1] = true;
                    grid[tempR-1][tempC+1].setReveal();

                }
                if (!visited[tempR][tempC-1]){ // mid left visited?
                    q.add(new int[]{tempR, tempC-1});
                    visited[tempR][tempC-1] = true;
                    grid[tempR][tempC-1].setReveal();

                }
                if (!visited[tempR][tempC+1]){ // mid right visited?
                    q.add(new int[]{tempR, tempC+1});
                    visited[tempR][tempC+1] = true;
                    grid[tempR][tempC+1].setReveal();

                }
            } else if(tempC == 0){ // left col
                if (!visited[tempR-1][tempC]){ // top mid visited?
                    q.add(new int[]{tempR-1, tempC});
                    visited[tempR-1][tempC] = true;
                    grid[tempR-1][tempC].setReveal();

                }
                if (!visited[tempR-1][tempC+1]){ // top right visited?
                    q.add(new int[]{tempR-1, tempC+1});
                    visited[tempR-1][tempC+1] = true;
                    grid[tempR-1][tempC+1].setReveal();

                }
                if (!visited[tempR][tempC+1]){ // mid right visited?
                    q.add(new int[]{tempR, tempC+1});
                    visited[tempR][tempC+1] = true;
                    grid[tempR][tempC+1].setReveal();

                }
                if (!visited[tempR+1][tempC]){ // bottom mid visited?
                    q.add(new int[]{tempR+1, tempC});
                    visited[tempR+1][tempC] = true;
                    grid[tempR+1][tempC].setReveal();

                }
                if (!visited[tempR+1][tempC+1]){ // bottom right visited?
                    q.add(new int[]{tempR+1, tempC+1});
                    visited[tempR+1][tempC+1] = true;
                    grid[tempR+1][tempC+1].setReveal();

                }
            } else if(tempC == 7){ // right col
                if (!visited[tempR-1][tempC-1]){ // top left visited?
                    q.add(new int[]{tempR-1, tempC-1});
                    visited[tempR-1][tempC-1] = true;
                    grid[tempR-1][tempC-1].setReveal();

                }
                if (!visited[tempR-1][tempC]){ // top mid visited?
                    q.add(new int[]{tempR-1, tempC});
                    visited[tempR-1][tempC] = true;
                    grid[tempR-1][tempC].setReveal();

                }
                if (!visited[tempR][tempC-1]){ // mid left visited?
                    q.add(new int[]{tempR, tempC-1});
                    visited[tempR][tempC-1] = true;
                    grid[tempR][tempC-1].setReveal();

                }
                if (!visited[tempR+1][tempC-1]){ // bottom left visited?
                    q.add(new int[]{tempR+1, tempC-1});
                    visited[tempR+1][tempC-1] = true;
                    grid[tempR+1][tempC-1].setReveal();

                }
                if (!visited[tempR+1][tempC]){ // bottom mid visited?
                    q.add(new int[]{tempR+1, tempC});
                    visited[tempR+1][tempC] = true;
                    grid[tempR+1][tempC].setReveal();

                }
            } else{
                if (!visited[tempR-1][tempC-1]){ // top left visited?
                    q.add(new int[]{tempR-1, tempC-1});
                    visited[tempR-1][tempC-1] = true;
                    grid[tempR-1][tempC-1].setReveal();

                }
                if (!visited[tempR-1][tempC]){ // top mid visited?
                    q.add(new int[]{tempR-1, tempC});
                    visited[tempR-1][tempC] = true;
                    grid[tempR-1][tempC].setReveal();

                }
                if (!visited[tempR-1][tempC+1]){ // top right visited?
                    q.add(new int[]{tempR-1, tempC+1});
                    visited[tempR-1][tempC+1] = true;
                    grid[tempR-1][tempC+1].setReveal();

                }

                if (!visited[tempR][tempC-1]){ // mid left visited?
                    q.add(new int[]{tempR, tempC-1});
                    visited[tempR][tempC-1] = true;
                    grid[tempR][tempC-1].setReveal();

                }
                if (!visited[tempR][tempC+1]){ // mid right visited?
                    q.add(new int[]{tempR, tempC+1});
                    visited[tempR][tempC+1] = true;
                    grid[tempR][tempC+1].setReveal();

                }

                if (!visited[tempR+1][tempC-1]){ // bottom left visited?
                    q.add(new int[]{tempR+1, tempC-1});
                    visited[tempR+1][tempC-1] = true;
                    grid[tempR+1][tempC-1].setReveal();

                }
                if (!visited[tempR+1][tempC]){ // bottom mid visited?
                    q.add(new int[]{tempR+1, tempC});
                    visited[tempR+1][tempC] = true;
                    grid[tempR+1][tempC].setReveal();

                }
                if (!visited[tempR+1][tempC+1]){ // bottom right visited?
                    q.add(new int[]{tempR+1, tempC+1});
                    visited[tempR+1][tempC+1] = true;
                    grid[tempR+1][tempC+1].setReveal();

                }
            }
        }
    }
    public int getValues(int r, int c) { return grid[r][c].getValue(); }
    public Cell getCell(int r, int c) { return grid[r][c]; }
    public boolean isMineMode() { return this.isMine; }
    public boolean isFlagMode() { return !this.isMine; }
    public int getFlagsPlaced() { return flagsPlaced; }
}
