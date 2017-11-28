//
//  SoundGrid.cpp
//  life_sounds
//
//  Created by Sam Ludford on 27/10/2017.
//

#include "SoundGrid.h"

//vector<vector<Sound*>> sounds;
vector<Sound*> sounds;

// 
double scale[] = { 146.83, 174.61, 196.00, 220.00, 261.63, 293.66, 349.23, 392.00, 440.00, 523.25, 587.33, 698.46, 783.99, 880.00, 1046.50 };
//double scale[] = { 146.83, 155.56, 174.61, 196.00, 220.00, 233.08, 261.63, 293.66, 311.13, 349.23, 392.00, 440.00, 466.16, 523.25, 587.33 };

const double base_freq = 80;
const double freq_gap = 70;

// <SoundGrid>

SoundGrid::SoundGrid() {}

SoundGrid::SoundGrid(int rows, int columns) {
    
    this->rows = rows;
    this->columns = columns;
    
    sounds.resize( rows );
    for(int i=0 ; i<rows ; i++) {
        sounds[i] = new Sound();
        sounds[i]->lfo_freq = 8/(i+1);
    }
}

SoundGrid::~SoundGrid() {}

void SoundGrid::trigger_at(int row, int column, int val) {
//    cout << "set val: (" << row << ", " << column << ")" << endl;
    sounds[row]->trigger(val, scale[column]);
}

double SoundGrid::get_signal() {
    double sig = 0;
    for(int i=0; i<rows; i++) {
        sig += sounds[i]->get_signal();
    }
//    cout << "sig norm: " << sig/rows << endl;
    return sig / rows;
}

// <Sound>

//Sound::Sound(double freq) {
//    this->freq = freq;
//}

Sound::Sound() {
    this->osc = new maxiOsc();
    this->lfo = new maxiOsc();
    this->glide = new maxiFilter();
//    this->env = new maxiEnvelope();
//    this->rampDown = new maxiFilter();
//    this->rampUp = new maxiFilter();
    this->amp = 1;
    this->freq = base_freq;
    this->lfo_freq = 1;
}
Sound::~Sound() {}

void Sound::trigger(double val, double freq) {
    this->freq = freq;
}

double Sound::get_signal() {
    double a = (lfo->sinewave(lfo_freq)+1)/2;
    return osc->sinewave(glide->lopass(this->freq,0.001)) * a;
}
