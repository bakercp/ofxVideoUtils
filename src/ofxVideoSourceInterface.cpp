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
    detachFromAllSinks();
}

//--------------------------------------------------------------
void ofxVideoSourceInterface::update() {
    sourceFrame();
}

//--------------------------------------------------------------
void ofxVideoSourceInterface::sourceFrame() {
    if(sinks.empty()) return;
    
    if(isFrameNew()) {
        // anyone who referenced the old frame will keep it.
        // This source does not keep it, but gets a new one.
        frame = ofxSharedVideoFrame(new ofxVideoFrame());
        frame->setFromPixels(getPixelsRef());
        
        for(sinksIter = sinks.begin();
            sinksIter != sinks.end(); sinksIter++) {
            (*sinksIter)->sink(frame);
        }
        frameSourced(frame);
    }
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::hasSinks() const {
    return !sinks.empty();
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::hasSink(ofxVideoSinkInterface* sink) const {
    return sink != NULL && sinks.find(sink) != sinks.end();
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::attachToSink(ofxVideoSinkInterface* sink) {
    if(openOnFirstConnection && !hasSinks() && !isLoaded()) {
        open();
        
        if(!isLoaded()) {
            ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::open() : error opening source.");
        }
    }
    
    if(!hasSink(sink)) {
        sinks.insert(sink);
        sinkWasAttached(sink);
        return true;
    } else {
        ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::attachToSink() : error attaching to sink.");
        if(closeOnLastDisconnect && !hasSinks() && isLoaded()) {
            close();
            //            if(!close())  ofLog(OF_LOG_ERROR, "ofxVideoSourceInterface::close() : error closing source.");
        }
        return false;
    }
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::detachFromSink(ofxVideoSinkInterface* sink) {
    if(hasSink(sink)) {
        sinks.erase(sink);
        sinkWasDetatched(sink);
        
        if(closeOnLastDisconnect && !hasSinks() && isLoaded()) {
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
bool ofxVideoSourceInterface::detachFromAllSinks() {
    for(sinksIter = sinks.begin();
        sinksIter != sinks.end();
        sinksIter++) {
        if(!detachFromSink(*sinksIter)) {
            ofLogError() << "ofxVideoSourceInterface::detachFromAllSinks() : error detatching from sink. Failing.";
        }
        // defer erase till end
    }
    sinks.clear();
    return true;
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
bool ofxVideoSourceInterface::getOpenOnFirstConnect() const {
    return openOnFirstConnection;
}

//--------------------------------------------------------------
bool ofxVideoSourceInterface::getCloseOnLastDisconnect() const {
    return closeOnLastDisconnect;
}
