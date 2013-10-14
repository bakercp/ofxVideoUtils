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
//#include "SourceInterface.h"
//
//
////------------------------------------------------------------------------------
//ofxVideoSourceInterface::ofxVideoSourceInterface() {
//    openOnFirstConnection = true;
//    closeOnLastDisconnect = true;
//    
//    _frame = Frame::Ptr(new Frame());
//}
//
////------------------------------------------------------------------------------
//ofxVideoSourceInterface::~ofxVideoSourceInterface() {
//    detachFromSinks();
//}
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::update() {
//    sourceFrame();
//}
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::sourceFrame() {
//    //cout << ">>" << endl;
//    if(sinks.empty()) {
//        //cout << "><<<<" << endl;
//        return;
//    }
//    //cout << ">> en" << endl;
//    if(isFrameNew()) {
//        
//        //cout << ">> 1. en" << endl;
//
//        // anyone who referenced the old frame will keep it.
//        // This source does not keep it, but gets a new one.
//        _frame = Frame::Ptr(new Frame());
//        _frame->setFromPixels(getPixelsRef());
//        
//        for(sinksIter = sinks.begin();
//            sinksIter != sinks.end(); sinksIter++) {
//            (*sinksIter)->sink(_frame);
//            //cout << ">> 2. en" << endl;
//        }
//        frameSourced(_frame);
//    }
//}
//
////------------------------------------------------------------------------------
//bool ofxVideoSourceInterface::hasSinks() const {
//    return !sinks.empty();
//}
//
////------------------------------------------------------------------------------
//bool ofxVideoSourceInterface::hasSink(ofxVideoSinkInterface* sink) const {
//    return sink != NULL && sinks.find(sink) != sinks.end();
//}
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::attachToSink(ofxVideoSinkInterface* sink) {
//    if(!hasSink(sink)) {
//        sink->registerSource(this);
//        registerSink(sink);
//    } else {
//        ofLogWarning("ofxVideoSourceInterface") << "attachToSink : sink already attached to this source.";
//    }
//}
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::detachFromSink(ofxVideoSinkInterface* sink) {
//    if(hasSink(sink)) {
//        sink->unregisterSource(this);
//        unregisterSink(sink);
//    } else {
//        ofLogWarning("ofxVideoSourceInterface") << "detachFromMe() : Was not attached to you.";
//    }
//}
//
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::detachFromSinks() {
//    for(sinksIter = sinks.begin();
//        sinksIter != sinks.end();
//        ) {
//        detachFromSink(*sinksIter++); // ++ deals with std::set lack of iterator invalidation during erase operation
//    }
//}
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::setOpenOnFirstConnect(bool v) {
//    openOnFirstConnection = v;
//}
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::setCloseOnLastDisconnect(bool v) {
//    closeOnLastDisconnect = v;
//}
//
////------------------------------------------------------------------------------
//bool ofxVideoSourceInterface::getOpenOnFirstConnect() const {
//    return openOnFirstConnection;
//}
//
////------------------------------------------------------------------------------
//bool ofxVideoSourceInterface::getCloseOnLastDisconnect() const {
//    return closeOnLastDisconnect;
//}
//
//
//
//
//
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::registerSink(ofxVideoSinkInterface *sink) {
//    if(!hasSink(sink)) {
//        sinks.insert(sink);
//        sink->sink(_frame); // immediately send the latest image
//        sinkWasAttached(sink);
//        
//        // open this source if it is not already open
//        if(openOnFirstConnection && !isLoaded()) {
//            open();
//        }
//    } else {
//        ofLogWarning("ofxVideoSourceInterface") << "attachToSink : sink already attached to this source.";
//    }
//}
//
//
////------------------------------------------------------------------------------
//void ofxVideoSourceInterface::unregisterSink(ofxVideoSinkInterface* sink) {
//    if(hasSink(sink)) {
//        sinks.erase(sink);
//        sinkWasDetatched(sink);
//        if(closeOnLastDisconnect && // if we are supposed to
//           !hasSinks() && // and all the sinks are gone
//           isLoaded()) { // and we are running
//            close();
//        }
//    } else {
//        ofLogWarning("ofxVideoSourceInterface") << "unregisterSink() : Was not attached to you.";
//    }
//}
//
//
