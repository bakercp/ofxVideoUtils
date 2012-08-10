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
ofxVideoSinkInterface::ofxVideoSinkInterface() {
    sinking = true;
}

//--------------------------------------------------------------
ofxVideoSinkInterface::~ofxVideoSinkInterface() {
    detachFromSources();
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::sink(ofxSharedVideoFrame frame) {
    if(isSinking()) {
        return frameReceived(frame);
    } else {
        return false;
    }
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::hasSources() const {
    return !sources.empty();
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::hasSource(ofxVideoSourceInterface* source) const {
    return source != NULL && sources.find(source) != sources.end();
}



//--------------------------------------------------------------
void ofxVideoSinkInterface::attachToSource(ofxVideoSourceInterface* source) {
    if(!hasSource(source)) {
        source->registerSink(this);
        registerSource(source);
    } else {
        ofLogWarning() << "ofxVideoSinkInterface::attachToSource() : this sink was already attached to source.";
    }
}

//--------------------------------------------------------------
void ofxVideoSinkInterface::detachFromSource(ofxVideoSourceInterface* source) {
    if(hasSource(source)) {
        source->unregisterSink(this);
        unregisterSource(source);
    } else {
        ofLogWarning() << "ofxVideoSinkInterface::detachFromSource() : this sink was not attached to the source.";
    }
}

//--------------------------------------------------------------
void ofxVideoSinkInterface::detachFromSources() {
    for(sourcesIter = sources.begin();
        sourcesIter != sources.end();) {
        detachFromSource(*sourcesIter++); // ++ deals with std::set lack of iterator invalidation during erase operation
    }
}

//--------------------------------------------------------------
bool ofxVideoSinkInterface::isSinking() const {
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


//--------------------------------------------------------------
void ofxVideoSinkInterface::registerSource(ofxVideoSourceInterface* source) {
    if(!hasSource(source)) {
        sources.insert(source);
        sourceWasAttached(source);
    } else {
        ofLogWarning("ofxVideoSinkInterface::registerSource : source already attached to this sink.");
    }
}

//--------------------------------------------------------------
void ofxVideoSinkInterface::unregisterSource(ofxVideoSourceInterface* source) {
    if(hasSource(source)) {
        sources.erase(source);
        sourceWasDetatched(source);
    } else {
        ofLogWarning("ofxVideoSinkInterface::unregisterSource : source not attached to this sink.");
    }
}




