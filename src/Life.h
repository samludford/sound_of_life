//
//  Life.h
//  life
//
//  Created by Sam Ludford on 10/10/2017.
//

#pragma once

class Life {

    public:
    
        Life();
        Life(int rows, int columns);
        virtual ~Life();
    
        void update();
    
        int valueAt(int x, int y);
        void stimulateCellAt(int x, int y);
        void killCellAt(int x, int y);
    
        int getRows();
        int getColumns();
    
    protected:
    
        int rows;
        int columns;
        int getLivingNeighbourCount(int x, int y);
        int get_position(int x, int y);
    
};


