//// =============================================================================
////
//// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in
//// all copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//// THE SOFTWARE.
////
//// =============================================================================
//
//
//#pragma once
//
//
//#include "Frame.h"
//#include "SourceInterface.h"
//
//
//namespace ofx {
//namespace Video {
//
//
//class SourceInterface;
//
//
//class SinkInterface {
//public:
//    SinkInterface();
//    
//    virtual ~SinkInterface();
//    
//    virtual void update();
//    
//    bool isFrameNew();
//
//    bool sink(const FramePtr& framePtr);
//
//    virtual bool frameReceived(const FramePtr& framePtr) {
//        ofLogWarning("ofxVideoSinkInterface") << "frameReceived() not implemented by subclass.";
//        return false;
//    }
//    
//    virtual void clear() {
//        ofLogNotice("ofxVideoSinkInterface") << "clear() not implemented by subclass.";
//    }
//    
//    
//    // connect / disconnect
//    bool hasSources() const;
//    bool hasSource(SourceInterface* source) const;
//   
//    void attachToSource(SourceInterface* source);
//    void detachFromSource(SourceInterface* source);
//    void detachFromSources();
//    
//    // callbacks
//    void sourceWasAttached(SourceInterface* source)  {
//        ofLogNotice("ofxVideoSinkInterface") << "sourceWasAttached() not implemented by subclass.";
//    }; // these callbacks are available
//    
//    void sourceWasDetatched(SourceInterface* source) {
//        ofLogNotice("ofxVideoSinkInterface") << "sourceWasDetatched() not implemented by subclass.";
//    }; // these callbacks are available
//    
//    void sinkingWasEnabled() {
//        ofLogNotice("ofxVideoSinkInterface") << "sinkingWasEnabled() not implemented by subclass.";
//    };
//    void sinkingWasDisabled() {
//        ofLogNotice("ofxVideoSinkInterface") << "sinkingWasDisabled() not implemented by subclass.";
//    };
//    
//    // get source list
//    set<SourceInterface*>& getSourcesRef();
//    
//    bool isSinking() const;
//    void setSinking(bool _sinking);
//private:
//    
//    bool bFrameHasChanged;
//    bool bIsFrameNew;
//    
//    friend class ofxVideoSourceInterface;
//
//    void registerSource(SourceInterface* source);
//    void unregisterSource(SourceInterface* source);
//
//    bool sinking;
//    
//    set<SourceInterface*> sources;
//    set<SourceInterface*>::iterator sourcesIter;
//};
//
//
//} }
