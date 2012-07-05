//
//  BaseVideoSink.h
//  ofxLivedrawEngineExample
//
//  Created by Christopher Baker on 6/5/12.
//  Copyright (c) 2012 School of the Art Institute of Chicago. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "ofxSimpleSet.h"
#include "ofxVideoFrame.h"
#include "ofxBaseVideoSource.h"

class ofxBaseVideoSource;

class ofxBaseVideoSink {
public:
    ofxBaseVideoSink();
    
    virtual ~ofxBaseVideoSink();
    virtual bool sink(ofxVideoFrame frame) = 0;

    // connect / disconnect
    bool isConnected();
    bool attachToSource(ofxBaseVideoSource* source);    
    bool detatchFromSource(ofxBaseVideoSource* source);

//    bool remoteAttachToSource(ofxBaseVideoSource* source);
//    bool remoteDetachFromSource(ofxBaseVideoSource* source);
    
    // callbacks
    void sourceWasAttached(ofxBaseVideoSource* source)  {}; // these callbacks are available
    void sourceWasDetatched(ofxBaseVideoSource* source) {}; // these callbacks are available
    
    // get source list
    vector<ofxBaseVideoSource*> getSources();
    
private:
    ofxSimpleSet<ofxBaseVideoSource*> sources;
};
