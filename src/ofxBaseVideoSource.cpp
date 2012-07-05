//
//  BaseVideoSource.cpp
//  ofxLivedrawEngineExample
//
//  Created by Christopher Baker on 6/5/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxBaseVideoSource.h"


//--------------------------------------------------------------
ofxBaseVideoSource::ofxBaseVideoSource() {
    openOnFirstConnection = true;
    closeOnLastDisconnect = true;;
}

//--------------------------------------------------------------
ofxBaseVideoSource::~ofxBaseVideoSource() {
    std::set<ofxBaseVideoSink*>::iterator iter = sinks.begin();
    while(iter != sinks.end()) detachFromSink(*iter++);
    sinks.clear();
}

//--------------------------------------------------------------
void ofxBaseVideoSource::source() {
    if(sinks.isEmpty()) return; 
    
    ofxVideoFrame& frame = getFrame();
    std::set<ofxBaseVideoSink*>::iterator iter = sinks.begin();
    while(iter != sinks.end()) (*iter++)->sink(frame);
}

//--------------------------------------------------------------
bool ofxBaseVideoSource::isConnected() { 
    sinks.size() > 0; 
}

//--------------------------------------------------------------
bool ofxBaseVideoSource::attachToSink(ofxBaseVideoSink* sink) {
    if(openOnFirstConnection && !isConnected() && !isOpen()) {
        if(!open())  ofLog(OF_LOG_ERROR, "ofxBaseVideoSource::open() : error opening source.");
    }
    
    if(sinks.add(sink)) {
        sinkWasAttached(sink);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxBaseVideoSource::attachToSink() : error attaching to sink.");
        if(closeOnLastDisconnect && !isConnected() && isOpen()) {
            if(!close())  ofLog(OF_LOG_ERROR, "ofxBaseVideoSource::close() : error closing source.");
        }
        return false;
    }
}

//--------------------------------------------------------------
bool ofxBaseVideoSource::detachFromSink(ofxBaseVideoSink* sink) {
    if(sinks.remove(sink)) {
        sinkWasDetatched(sink);
        if(closeOnLastDisconnect && !isConnected() && isOpen()) {
            if(!close())  ofLog(OF_LOG_ERROR, "ofxBaseVideoSource::close() : error closing source.");
        }
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxBaseVideoSource::attachToSink() : error attaching to sink.");
        return false;
    }
}

//--------------------------------------------------------------
vector<ofxBaseVideoSink*> ofxBaseVideoSource::getSinks() const {
    return sinks.toArray();
}

//--------------------------------------------------------------
void ofxBaseVideoSource::setOpenOnFirstConnect(bool v) {
    openOnFirstConnection = v;
}

//--------------------------------------------------------------
void ofxBaseVideoSource::setCloseOnLastDisconnect(bool v) {
    closeOnLastDisconnect = v;
}

//--------------------------------------------------------------
bool ofxBaseVideoSource::getOpenOnFirstConnect() {
    return openOnFirstConnection;
}

//--------------------------------------------------------------
bool ofxBaseVideoSource::getCloseOnLastDisconnect() {
    return closeOnLastDisconnect;
}
