//
//  BaseVideoSink.cpp
//  ofxLivedrawEngineExample
//
//  Created by Christopher Baker on 6/5/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxBaseVideoSink.h"


//bool attachToSource(ofxBaseVideoSource* source);    
//bool detatchFromSource(ofxBaseVideoSource* source);
//
//// callbacks
//bool sourceWasAttached(ofxBaseVideoSource* source)  {}; // these callbacks are available
//bool sourceWasDetatched(ofxBaseVideoSource* source) {}; // these callbacks are available
//
//// get source list
//vector<ofxBaseVideoSource*> getSources();


//--------------------------------------------------------------
ofxBaseVideoSink::ofxBaseVideoSink() {}

//--------------------------------------------------------------
ofxBaseVideoSink::~ofxBaseVideoSink() {
    vector<ofxBaseVideoSource*> _sources = getSources();
    for(int i = 0; i < _sources.size(); i++) {
        detatchFromSource(_sources[i]);
    }
    sources.clear();
}

//--------------------------------------------------------------
bool ofxBaseVideoSink::isConnected() { 
    return sources.size() > 0; 
}

//--------------------------------------------------------------
bool ofxBaseVideoSink::attachToSource(ofxBaseVideoSource* source) {
    if(source->attachToSink(this)) {
        sources.add(source);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxBaseVideoSink::attachToSource() : error attaching to source.");
        return false;
    }
}

//--------------------------------------------------------------
bool ofxBaseVideoSink::detatchFromSource(ofxBaseVideoSource* source) {
    if(source->detachFromSink(this)) {
        sources.remove(source);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxBaseVideoSink::detatchFromSource() : error detatching from source.");
        return false;
    }
}
