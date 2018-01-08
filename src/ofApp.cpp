/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"

#define RATE 12
#define PADDING 10
#define CELL_PADDING 1
#define ROWS 15
#define COLUMNS 15

int cell_width, cell_height;

int counter;

maxiDistortion dist;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);
    myLife = Life(ROWS, COLUMNS);
    counter = 0;
    cell_width = (ofGetWidth() - PADDING*2.0)/ROWS;
    cell_height = (ofGetHeight() - PADDING*2.0)/COLUMNS;
    
    mSoundGrid = SoundGrid(ROWS, COLUMNS);
    
    // audio setup
    sampleRate 	= 44100;
    bufferSize	= 512;
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // update the Life simulation once every RATE frames
    if(counter % RATE == 0) {
        myLife.update();
    }
    counter++;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw grid based on data contained in Life object
    int x, y;
    float brightness;
    for(int i=0 ; i<myLife.getRows() ; i++) {
        for(int j=0 ; j<myLife.getColumns() ; j++) {
            // draw black rectangle
            x = PADDING + i * cell_width;
            y = PADDING + j * cell_height;
            ofSetColor(0);
            ofDrawRectangle(x, y, cell_width, cell_height);
            float val = myLife.valueAt(i,j);
            if(val == 0) {
                brightness = 0;
            } else {
                brightness = 255 / val;
                mSoundGrid.trigger_at(i, j, 1/val);
            }
            ofSetColor(brightness);
            ofDrawRectangle(x + CELL_PADDING, y + CELL_PADDING, cell_width - 2.0*CELL_PADDING, cell_height - 2.0*CELL_PADDING);
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        // defer audio processing to the SoundGrid object
        double wave = mSoundGrid.get_signal();
        output[i*nChannels    ] = wave; /* You may end up with lots of outputs. add them here */
        output[i*nChannels + 1] = wave;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // when a key is pressed, stimulate a few cells
    myLife.stimulateCellAt(4, 4);
    myLife.stimulateCellAt(4, 5);
    myLife.stimulateCellAt(4, 6);
    myLife.stimulateCellAt(5, 5);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
