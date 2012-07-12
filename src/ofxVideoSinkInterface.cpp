//
//  BaseVideoSink.cpp
//  ofxLivedrawEngineExample
//
//  Created by Christopher Baker on 6/5/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxVideoSourceInterface.h"


//bool attachToSource(ofxVideoSourceInterface* source);    
//bool detatchFromSource(ofxVideoSourceInterface* source);
//
//// callbacks
//bool sourceWasAttached(ofxVideoSourceInterface* source)  {}; // these callbacks are available
//bool sourceWasDetatched(ofxVideoSourceInterface* source) {}; // these callbacks are available
//
//// get source list
//vector<ofxVideoSourceInterface*> getSources();


//--------------------------------------------------------------
ofxVideoSinkInterface::ofxVideoSinkInterface() {
    sinking = true;
}

//--------------------------------------------------------------
ofxVideoSinkInterface::~ofxVideoSinkInterface() {
    vector<ofxVideoSourceInterface*> _sources = getSources();
    for(int i = 0; i < _sources.size(); i++) {
        detatchFromSource(_sources[i]);
    }
    sources.clear();
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::sink(ofxVideoFrame frame) {
    if(isSinking()) {
        return frameReceived(frame);
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::isConnected() { 
    return sources.size() > 0; 
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::attachToSource(ofxVideoSourceInterface* source) {
    if(source->attachToSink(this)) {
        sources.add(source);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::attachToSource() : error attaching to source.");
        return false;
    }
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::detatchFromSource(ofxVideoSourceInterface* source) {
    if(source->detachFromSink(this)) {
        sources.remove(source);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::detatchFromSource() : error detatching from source.");
        return false;
    }
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::isSinking() {
    return sinking;
}

//--------------------------------------------------------------
void ofxVideoSinkInterface::setSinking(bool _sinking) {
    if(_sinking != sinking) {
        sinking = _sinking;
        if(sinking) {
            sinkingEnabled();
        } else {
            sinkingDisabled();
        }
    }
}

