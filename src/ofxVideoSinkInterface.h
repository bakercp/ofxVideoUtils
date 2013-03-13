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

#pragma once

#include <set>

#include "ofMain.h"
#include "ofxVideoFrame.h"
#include "ofxVideoSourceInterface.h"

class ofxVideoSourceInterface;

class ofxVideoSinkInterface {
public:
    ofxVideoSinkInterface();
    
    virtual ~ofxVideoSinkInterface();
    
    virtual void update();
    
    bool isFrameNew();

    bool sink(ofxSharedVideoFrame frame);
    virtual bool frameReceived(ofxSharedVideoFrame frame) {
        ofLogWarning("ofxVideoSinkInterface") << "frameReceived() not implemented by subclass.";
        return false;
    }
    
    virtual void clear() {
        ofLogNotice("ofxVideoSinkInterface") << "clear() not implemented by subclass.";
    }
    
    
    // connect / disconnect
    bool hasSources() const;
    bool hasSource(ofxVideoSourceInterface* source) const;
   
    void attachToSource(ofxVideoSourceInterface* source);
    void detachFromSource(ofxVideoSourceInterface* source);
    void detachFromSources();
    
    // callbacks
    void sourceWasAttached(ofxVideoSourceInterface* source)  {
        ofLogNotice("ofxVideoSinkInterface") << "sourceWasAttached() not implemented by subclass.";
    }; // these callbacks are available
    
    void sourceWasDetatched(ofxVideoSourceInterface* source) {
        ofLogNotice("ofxVideoSinkInterface") << "sourceWasDetatched() not implemented by subclass.";
    }; // these callbacks are available
    
    void sinkingWasEnabled() {
        ofLogNotice("ofxVideoSinkInterface") << "sinkingWasEnabled() not implemented by subclass.";
    };
    void sinkingWasDisabled() {
        ofLogNotice("ofxVideoSinkInterface") << "sinkingWasDisabled() not implemented by subclass.";
    };
    
    // get source list
    set<ofxVideoSourceInterface*>& getSourcesRef();
    
    bool isSinking() const;
    void setSinking(bool _sinking);
private:
    
    bool bFrameHasChanged;
    bool bIsFrameNew;
    
    friend class ofxVideoSourceInterface;

    void registerSource(ofxVideoSourceInterface* source);
    void unregisterSource(ofxVideoSourceInterface* source);

    bool sinking;
    
    set<ofxVideoSourceInterface*> sources;
    set<ofxVideoSourceInterface*>::iterator sourcesIter;
};
