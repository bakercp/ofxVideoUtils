//
//  BaseVideoSource.h
//  ofxLivedrawEngineExample
//
//  Created by Christopher Baker on 6/5/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxSimpleSet.h"
#include "ofxVideoSinkInterface.h"

class ofxVideoSinkInterface;

class ofxVideoSourceInterface {
public:
    ofxVideoSourceInterface();
    virtual ~ofxVideoSourceInterface();

    virtual ofxVideoFrame getFrame() = 0;
    
    void source(); // push frames
    virtual void frameSent(ofxVideoFrame frame) {};
    
    virtual bool close() = 0;
    virtual bool open() = 0;
    virtual bool isOpen() = 0;
        
    bool isConnected();
    
    bool attachToSink(ofxVideoSinkInterface* sink); // sinks call this to be fed by this source
    bool detachFromSink(ofxVideoSinkInterface* sink); // sinks call this to be cut off from this source

    void sinkWasAttached(ofxVideoSinkInterface* sink)  {}; // these callbacks are available
    void sinkWasDetatched(ofxVideoSinkInterface* sink) {}; // these callbacks are available
    
    void setOpenOnFirstConnect(bool v);
    void setCloseOnLastDisconnect(bool v);
    
    bool getOpenOnFirstConnect();
    bool getCloseOnLastDisconnect();
    
    vector<ofxVideoSinkInterface*> getSinks() const;

private:
    
    ofxVideoFrame frame;
    
    bool openOnFirstConnection;
    bool closeOnLastDisconnect;
    
    // no subclass access.  all access done via getters 
    // and setters so events will be called
    ofxSimpleSet<ofxVideoSinkInterface*> sinks;
};

