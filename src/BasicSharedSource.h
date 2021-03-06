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
//#include "SinkInterface.h"
//
//
//class SinkInterface;
//
//
//class SourceInterface {
//public:
//    SourceInterface();
//    virtual ~SourceInterface();
//
//    void update();
//    
//    void sourceFrame(); // push frames
//    
//    virtual void frameSourced(Frame::Ptr frame) {};
//    
//    virtual bool isFrameNew() = 0;
//    virtual ofPixelsRef getPixelsRef() = 0;
//    
//    virtual void close() {};
//    virtual void open()  {};
//    virtual bool isLoaded() = 0;
//        
//    bool hasSinks() const;
//    bool hasSink(ofxVideoSinkInterface* sink) const;
//    
//    void attachToSink(ofxVideoSinkInterface* sink); // sinks call this to be fed by this source
//    void detachFromSink(ofxVideoSinkInterface* sink); // sinks call this to be cut off from this source
//    void detachFromSinks();
//    
//    void sinkWasAttached(ofxVideoSinkInterface* sink)  {}; // these callbacks are available
//    void sinkWasDetatched(ofxVideoSinkInterface* sink) {}; // these callbacks are available
//    
//    void setOpenOnFirstConnect(bool v);
//    void setCloseOnLastDisconnect(bool v);
//    
//    bool getOpenOnFirstConnect() const;
//    bool getCloseOnLastDisconnect() const;
// 
//    set<ofxVideoSinkInterface*> getSinksRef();
//    
//bool fequals(float f0, float f1)
//{
//    return std::fabs(f1 - f0) < std::numeric_limits<float>::epsilon();
//}
//
//protected:
//    
//    Frame::Ptr getFrame() { return _frame; }
//    void setFrame(Frame::Ptr frame) { return _frame = frame; }
//    
//private:
//    
//    Frame::Ptr _frame;
//    
//    friend class ofxVideoSinkInterface;
//    
//    void registerSink(ofxVideoSinkInterface* sink);
//    void unregisterSink(ofxVideoSinkInterface* sink);
//
//    bool openOnFirstConnection;
//    bool closeOnLastDisconnect;
//    
//    // no subclass access.  all access done via getters 
//    // and setters so events will be called
//    set<SinkInterface*> sinks;
//    set<SinkInterface*>::iterator sinksIter;
//};
//
