#pragma once


#include "ofMain.h"
#include "ofxGui.h"

//class ofApp;
class ControlPanelView
{
public:
    ControlPanelView();
    void setup();
    void update();
    void draw();
    
    ofxPanel gui;
   // ofApp *app;
    ofParameterGroup parameters;
    ofParameter<bool> isRecording;
    void onIsRecordingChanged(bool & doRecording);
    
   // ofParameter<float> bufferViewPosition;
};
//#include "ofApp.h"