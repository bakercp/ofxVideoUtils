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

