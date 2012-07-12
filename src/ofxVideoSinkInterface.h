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
#include "ofxVideoSourceInterface.h"

class ofxVideoSourceInterface;

class ofxVideoSinkInterface {
public:
    ofxVideoSinkInterface();
    
    virtual ~ofxVideoSinkInterface();
    
    bool sink(ofxVideoFrame frame);
    virtual bool frameReceived(ofxVideoFrame frame) = 0;
    
    // connect / disconnect
    bool isConnected();
    bool attachToSource(ofxVideoSourceInterface* source);    
    bool detatchFromSource(ofxVideoSourceInterface* source);

//    bool remoteAttachToSource(ofxVideoSourceInterface* source);
//    bool remoteDetachFromSource(ofxVideoSourceInterface* source);
    
    // callbacks
    void sourceWasAttached(ofxVideoSourceInterface* source)  {}; // these callbacks are available
    void sourceWasDetatched(ofxVideoSourceInterface* source) {}; // these callbacks are available
    
    void sinkingEnabled() {};
    void sinkingDisabled() {};
    
    // get source list
    vector<ofxVideoSourceInterface*> getSources();
    
    bool isSinking();
    void setSinking(bool _sinking);
private:
    
    bool sinking;
    
    ofxSimpleSet<ofxVideoSourceInterface*> sources;
};
