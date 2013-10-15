// =============================================================================
//
// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#pragma once


#include "ofMain.h"
#include "Grabber.h"
#include "Player.h"
#include "Frame.h"
#include "FrameBuffer.h"
#include "BufferLoader.h"
#include "FrameBufferPlayer.h"

#include "ControlPanelView.h"

using namespace ofx;


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);

    int camWidth;
    int camHeight;

    bool playerSource;
    
    Video::Grabber::SharedPtr grabber;
    Video::Player::SharedPtr player;

    Video::Frame::SharedPtr playerFrame;
    Video::Frame::SharedPtr grabberFrame;
    Video::Frame::SharedPtr bufferPlayerFrame;

//    Video::BufferLoader::SharedPtr bufferLoader;
    Video::FrameBuffer::SharedPtr buffer;
    Video::FrameBufferPlayer::SharedPtr bufferPlayer;

    ofParameter<bool> isRecording;
    ofParameter<ofVec3f> bufferPosition;
    void startRecording();
    
    ControlPanelView controlPanelView;
    /*ofParameter<int> sharpness;
	ofParameter<int> contrast;
	ofParameter<int> brightness;
	ofParameter<int> saturation;
	ofParameter<bool> frameStabilizationEnabled;
	ofParameter<bool> colorEnhancementEnabled;
	ofParameter<bool> ledEnabled;
	ofParameter<bool> hideGui;*/
        
};
