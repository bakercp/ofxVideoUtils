//
//  BaseVideoSource.cpp
//  ofxLivedrawEngineExample
//
//  Created by Christopher Baker on 6/5/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#include "ofxVideoSourceInterface.h"


//--------------------------------------------------------------
ofxVideoSourceInterface::ofxVideoSourceInterface() {
    openOnFirstConnection = true;
    closeOnLastDisconnect = true;;
}

//--------------------------------------------------------------
ofxVideoSourceInterface::~ofxVideoSourceInterface() {
    std::set<ofxVideoSinkInterface*>::iterator iter = sinks.begin();
    while(iter != sinks.end()) detachFromSink(*iter++);
    sinks.clear();
}

//--------------------------------------------------------------
void ofxVideoSourceInterface::source() {
    if(sinks.isEmpty()) return; 
    
    ofxVideoFrame frame = getFrame();
    std::set<ofxVideoSinkInterface*>::iterator iter = sinks.begin();
    while(iter != sinks.end()) (*iter++)->sink(frame);
    
    frameSent(frame);
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::isConnected() { 
    sinks.size() > 0; 
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::attachToSink(ofxVideoSinkInterface* sink) {
    if(openOnFirstConnection && !isConnected() && !isOpen()) {
        if(!open())  ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::open() : error opening source.");
    }
    
    if(sinks.add(sink)) {
        sinkWasAttached(sink);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::attachToSink() : error attaching to sink.");
        if(closeOnLastDisconnect && !isConnected() && isOpen()) {
            close();
//            if(!close())  ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::close() : error closing source.");
        }
        return false;
    }
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::detachFromSink(ofxVideoSinkInterface* sink) {
    if(sinks.remove(sink)) {
        sinkWasDetatched(sink);
        if(closeOnLastDisconnect && !isConnected() && isOpen()) {
            close();
//            if(!close())  ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::close() : error closing source.");
        }
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::attachToSink() : error attaching to sink.");
        return false;
    }
}

//--------------------------------------------------------------
vector<ofxVideoSinkInterface*> ofxVideoSourceInterface::getSinks() const {
    return sinks.toArray();
}

//--------------------------------------------------------------
void ofxVideoSourceInterface::setOpenOnFirstConnect(bool v) {
    openOnFirstConnection = v;
}

//--------------------------------------------------------------
void ofxVideoSourceInterface::setCloseOnLastDisconnect(bool v) {
    closeOnLastDisconnect = v;
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::getOpenOnFirstConnect() {
    return openOnFirstConnection;
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::getCloseOnLastDisconnect() {
    return closeOnLastDisconnect;
}
