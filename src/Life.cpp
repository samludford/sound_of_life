//
//  Life.cpp
//  life
//
//  Created by Sam Ludford on 10/10/2017.
//

#include "Life.h"

#define DEFAULT_ROWS 10
#define DEFAULT_COLUMNS 10

int* grid;
int* grid_buffer;

// constructor / destructor

Life::Life() {
    rows = DEFAULT_ROWS;
    columns = DEFAULT_COLUMNS;
    
    grid = new int[rows*columns];
    grid_buffer = new int[rows*columns];

}

Life::Life(int rows, int columns){
    
    this->rows = rows;
    this->columns = columns;
    grid = new int[rows*columns];
    grid_buffer = new int[rows*columns];
    
    
    for(int i=0 ; i < rows ; i++) {
        for(int j=0 ; j < columns ; j++) {
            int pos = get_position(i, j);
            grid[pos] = 0;
            grid_buffer[0] = 0;
        }
    }
    
}

Life::~Life() {}

// accessors

int Life::getRows() {
    return rows;
}

int Life::getColumns() {
    return columns;
}

// pubilc methods

void Life::update() {
    
    // populate cell buffer based on current state
    for(int i=0 ; i<rows ; i++) {
        for(int j=0 ; j<columns ; j++) {
            int count = getLivingNeighbourCount(i, j);
            int pos = get_position(i, j);
            if (grid[pos] > 0) {
                grid_buffer[pos] = !(count < 2 || count > 3) ? 1 : 0;
            } else {
                grid_buffer[pos] = (count == 3) ? 1 : 0;
            }
        }
    }
    
    // change current values based on cell buffer
    for(int i=0 ; i<rows ; i++) {
        for(int j=0 ; j<columns ; j++) {
            int pos = get_position(i, j);
            if (grid_buffer[pos] == 1) {
                grid[pos]++;
            } else {
                grid[pos] = 0;
            }
        }
    }
    
}

int Life::valueAt(int x, int y) {
    if (x < rows && y < columns) {
        return grid[get_position(x, y)];
    } else {
        return -1;
    }
}

void Life::stimulateCellAt(int x, int y) {
    if (x < rows && y < columns) {
        grid[get_position(x, y)]++;
    }
}

void Life::killCellAt(int x, int y) {
    if (x < rows && y < columns) {
        grid[get_position(x, y)] = 0;
    }
}

// utilities

int Life::get_position(int x, int y) {
    return x * rows + y;
}



int Life::getLivingNeighbourCount(int x, int y) {
    
    int counter = 0;
    for(int i = -1 ; i <= 1 ; i++) {
        for(int j= -1 ; j <= 1 ; j++) {
            
            // ignore input cell
            if(i==0 && j==0) continue;
            
            int checkCellX = x + i;
            int checkCellY = y + j;
            
            // ignore negatives
            if(checkCellX<0 || checkCellY<0) continue;
            if(checkCellX>=rows || checkCellY>=columns) continue;
            
            int pos = get_position(checkCellX, checkCellY);
            if (grid[pos] > 0) counter++;
        }
    }
    
    return counter;
}
