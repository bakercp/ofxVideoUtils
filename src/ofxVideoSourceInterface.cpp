/*==============================================================================
 
 Copyright (c) 2010, 2011, 2012 Christopher Baker <http://christopherbaker.net>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ==============================================================================*/

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
