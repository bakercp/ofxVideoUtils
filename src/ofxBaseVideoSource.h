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
#include "ofxVideoBufferData.h"
#include "ofxBaseVideoSink.h"

class ofxBaseVideoSink;

class ofxBaseVideoSource {
public:
    ofxBaseVideoSource();
    virtual ~ofxBaseVideoSource();
    virtual ofxVideoFrame& getFrame() = 0;

    void source(); // push frames
    
    virtual bool open() = 0;
    virtual bool close() = 0; // called when nobody else is connected 
    virtual bool isOpen() = 0;
        
    bool isConnected();
    
    bool attachToSink(ofxBaseVideoSink* sink); // sinks call this to be fed by this source
    bool detachFromSink(ofxBaseVideoSink* sink); // sinks call this to be cut off from this source

    void sinkWasAttached(ofxBaseVideoSink* sink)  {}; // these callbacks are available
    void sinkWasDetatched(ofxBaseVideoSink* sink) {}; // these callbacks are available
    
    void setOpenOnFirstConnect(bool v);
    void setCloseOnLastDisconnect(bool v);
    
    bool getOpenOnFirstConnect();
    bool getCloseOnLastDisconnect();
    
    vector<ofxBaseVideoSink*> getSinks() const;

private:
    
    bool openOnFirstConnection;
    bool closeOnLastDisconnect;
    
    // no subclass access.  all access done via getters 
    // and setters so events will be called
    ofxSimpleSet<ofxBaseVideoSink*> sinks;
};

