//
//  SoundGrid.h
//  life_sounds
//
//  Created by Sam Ludford on 27/10/2017.
//

#pragma once

#include "ofxMaxim.h"
#include "ofMain.h"

class SoundGrid {
    
    public:
    
        SoundGrid();
        SoundGrid(int rows, int columns);
        virtual ~SoundGrid();
    
        double rows;
        double columns;
    
        void trigger_at(int row, int column, int val);
        double get_signal();
    
};

class Sound {
    
    public:
    
        Sound();
        virtual ~Sound();
        double freq;
        double get_signal();
        void trigger(double val, double freq);
        double amp;
        double lfo_freq;
    
    protected:
    
        maxiOsc *lfo;
        maxiOsc *osc;
//        maxiEnvelope *env;
//        maxiFilter *rampDown;
        maxiFilter *glide;
    
};
