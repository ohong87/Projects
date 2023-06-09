package com.example.minesweeper;

public class Cell {
    private int value;
    private boolean isRevealed;
    private boolean hasFlag;
    private boolean isBomb;

    public Cell(int val){
        value = val;
        isRevealed = false;
        hasFlag = false;
        isBomb = false;
    }
    public Cell(){
        value = 0;
        isRevealed = false;
        hasFlag = false;
        isBomb = false;
    }

    // Setters
    public void setReveal() { isRevealed = true; }
    public void setFlag(boolean flagState) { hasFlag = flagState; }
    public void setBomb() { isBomb = true; }
    public void setValue(int v) { value = v; }

    // Getters
    public int getValue() { return value; }
    public boolean getReveal() { return isRevealed; }
    public boolean getFlagState() { return hasFlag; }
    public boolean getBombState() { return isBomb; }
}
