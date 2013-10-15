#pragma once


#include "ofMain.h"
#include "ofxGui.h"

class ofApp;
class ControlPanelView
{
public:
    ControlPanelView();
    void setup(ofApp* app);
    void update();
    void draw();
    
    ofxPanel gui;
    ofApp *app;
    ofParameterGroup parameters;
    void onIsRecordingChanged(bool & doRecording);
    void onBufferPositionChanged(ofVec3f & point);

};

#include "ofApp.h"