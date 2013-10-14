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


#include "ofApp.h"


//------------------------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(255,255,255);
    ofSetVerticalSync(true);
	ofSetFrameRate(60);

    playerFrame = Video::Frame::makeShared();
    grabberFrame = Video::Frame::makeShared();
    bufferPlayerFrame = Video::Frame::makeShared();

    playerSource = true;
	
    // video setup
    camWidth    = 640;	// try to grab at this size.
	camHeight   = 480;

    // ready a grabber source
    grabber = Video::Grabber::makeShared();
	grabber->initGrabber(camWidth,camHeight);

    // ready a video source
    player = Video::Player::makeShared();
	player->loadMovie("fingers.mov");
	player->play();
    player->setLoopState(OF_LOOP_NORMAL);
    
    // ready a frame buffer
    buffer = Video::FrameBuffer::makeShared(player->getTotalNumFrames());
    buffer->setFrameRate(30.1);
    buffer->setUnique(true);

    // ready a frame buffer player
    bufferPlayer = Video::FrameBufferPlayer::makeShared();
    bufferPlayer->loadBuffer(buffer);
    bufferPlayer->start();

    isRecording = false;
	
}

//------------------------------------------------------------------------------
void ofApp::update()
{
    grabber->update();
    player->update();
    bufferPlayer->update();

    grabberFrame = grabber->getSharedFrame();
    playerFrame = player->getSharedFrame();
    bufferPlayerFrame = bufferPlayer->getSharedFrame();

    if(grabber->isFrameNew())
    {
        buffer->addFrame(grabberFrame);
    }
}

//------------------------------------------------------------------------------
void ofApp::draw()
{

    ofEnableAlphaBlending();

    ofBackground(0,0,0);

	ofSetColor(255,255,255,255);
    if(grabberFrame) grabberFrame->draw(20,20,160,120);
    ofDrawBitmapStringHighlight("GRABBER", 22,32);
    if(!playerSource) {
        ofSetColor(isRecording ? 0 : 255,255,0);
        ofNoFill();
        ofRect(20,20,160,120);
    }
    
	ofSetColor(255,255,255,255);
    if(playerFrame) playerFrame->draw(20,260,160,120);
    ofDrawBitmapStringHighlight("VIDEO", 22,272);
    if(playerSource) {
        ofSetColor(isRecording ? 0 : 255,255,0);
        ofNoFill();
        ofRect(20,260,160,120);
    }


    ofSetColor(255,255,255,255);
    if(playerFrame) bufferPlayerFrame->draw(20,480,160,120);
    ofDrawBitmapStringHighlight("BUFFER PLAYER", 22,272+220);
    if(playerSource) {
        ofSetColor(isRecording ? 0 : 255,255,0);
        ofNoFill();
        ofRect(20,260,160,120);
    }

    
    std::string keys = "";
    keys += "Keys:\n";
    keys += "Select the Source (ABOVE LEFT)\n";
    keys += "  [1] Next Video Source\n";
    keys += "  [s] Video Grabber Settings\n";
    keys += "\n";
    keys += "Select the Buffer Player (RIGHT)\n";
    keys += "  [`] Next Buffer Player\n";
    keys += "\n";
    keys += "All settings below apply to the\n"; 
    keys += "current player and buffer.\n";
    keys += "  [SPACE] Toggle Recording\n";
    keys += "  [x] Clear Buffer\n";
    keys += "  [?] Load Test Video Into Buffer\n";
    keys += "  [p] Next Buffer Mode\n";
    keys += "  [q] Next Loop Mode\n";
    keys += "\n";
    keys += "  [[] Loop Point (start) (DOWN)\n";
    keys += "  [{] Loop Point (end)   (DOWN)\n";
    keys += "  []] Loop Point (start) (UP)\n";
    keys += "  [}] Loop Point (end)   (UP)\n";
    keys += "  [c] Clear Loop Points\n";
    keys += "\n";
    keys += "  [-] Decrease Speed\n";
    keys += "  [=] Increase Speed\n";
    keys += "\n";
    keys += "  [_] Decrease Position\n";
    keys += "  [+] Increase Position\n";

    
    ofSetColor(255);
    ofDrawBitmapString(keys,20,400);
    
    if(isRecording) {
        
        
//        if(!playerSource && vidGrabber.isFrameNew()) {
//            Frame::Ptr frame(new ofImage());
//            frame->setFromPixels(vidGrabber.getPixelsRef());
//            bufferPlayer->getVideoBuffer()->bufferFrame(frame);
//        } else if(playerSource && vidPlayer.isFrameNew() ) {
//            Frame::Ptr frame(new ofImage());
//            frame->setFromPixels(vidPlayer.getPixelsRef());
//            bufferPlayer->getVideoBuffer()->bufferFrame(frame);
//        }
    }
    
    int x = 320;
    int y = 20;
    

    ofSetColor(255);
    ofFill();
//    bufferPlayer->draw(x,y);

    ofNoFill();
    ofRect(x,y,camWidth,camHeight);

    if(bufferPlayerFrame) bufferPlayerFrame->draw(x,y,camWidth,camHeight);

//    float p = bufferPlayer->getVideoBuffer()->getPercentFull();
    ofFill();
    ofSetColor(255,255,0,127);
//    ofRect(x,y+camHeight-5,camWidth*p,5);

    {
        ofPushStyle();
        float ff = bufferPlayer->getFrame() / (float)bufferPlayer->getCapacity();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(0,255,0);
        ofRect(x + camWidth*ff,y+camHeight-2.5,3,10);
        ofPopStyle();
    }
    
    {
        ofPushStyle();
        float ff = bufferPlayer->getLoopPointStart() / (float)bufferPlayer->getCapacity();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(0,0,255);
        ofRect(x + camWidth*ff,y+camHeight-2.5,3,10);
        ofPopStyle();
    }
    
    {
        ofPushStyle();
        float ff = bufferPlayer->getLoopPointEnd() / (float)bufferPlayer->getCapacity();
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofSetColor(0,0,255);
        ofRect(x + camWidth*ff,y+camHeight-2.5,3,10);
        ofPopStyle();
    }
    
    ofSetColor(255);
    // draw some stats
//    string stats = bufferPlayer->toString();
//    ofDrawBitmapString(stats, x + 20, y + 20);

    
    x += (camWidth + 0);
    if((x + 320)> ofGetWidth()) {
        y+= camHeight + 0;
        x = 320;
    }
    
    ofDisableAlphaBlending();

}

//------------------------------------------------------------------------------
void ofApp::keyPressed(int key)
{

    cout << "key == " << key << endl;


    if(key == ' ')
        ofHideCursor();
    if(key == 's')
        ofShowCursor();
    
    int l0 = bufferPlayer->getLoopPointStart();
    int l1 = bufferPlayer->getLoopPointEnd();
    ofLoopType lt = bufferPlayer->getLoopType();
//    Video::Buffer::Mode vbt = bufferPlayer->getVideoBuffer()->getBufferType();

    float speed = bufferPlayer->getSpeed();

    int position = bufferPlayer->getFrame();
    
    switch (key) {
        case '1':
            playerSource = !playerSource;;
            break;
        case 's':
//            videoGrabber.videoSettings();
            break;
        case 'p':
//            if(vbt == OFX_VIDEO_BUFFER_FIXED) vbt = OFX_VIDEO_BUFFER_CIRCULAR; 
//            else if(vbt == OFX_VIDEO_BUFFER_CIRCULAR) vbt = OFX_VIDEO_BUFFER_PASSTHROUGH; 
//            else if(vbt == OFX_VIDEO_BUFFER_PASSTHROUGH) vbt = OFX_VIDEO_BUFFER_FIXED; 
//            bufferPlayer->getVideoBuffer()->setBufferType(vbt);
            break;
        case 'q':
            // cycle through the loop mode
            if(lt == OF_LOOP_NONE) lt = OF_LOOP_NORMAL;
            else if(lt == OF_LOOP_NORMAL) lt = OF_LOOP_PALINDROME;
            else if(lt == OF_LOOP_PALINDROME) lt = OF_LOOP_NONE;
            bufferPlayer->setLoopType(lt);
            break;
        case '[':
            bufferPlayer->setLoopPointStart(l0-1);
            break;
        case ';':
            bufferPlayer->setLoopPointEnd(l1-1);
            break;
        case ']':
            bufferPlayer->setLoopPointStart(l0+1);
            break;
        case '\'':
            bufferPlayer->setLoopPointEnd(l1+1);
            break;
        case 'c':
            bufferPlayer->clearLoopPoints();
            break;
        case ' ':
            isRecording = !isRecording;
            break;
        case 'x':
//            bufferPlayer->getVideoBuffer()->clear();
            break;
        case '?':
//            bufferPlayer->getVideoBuffer()->loadMovieAsync("fingers.mov");
            break;
        case '-':
            speed -= .05;
            bufferPlayer->setSpeed(speed);
            break;
        case '=':
            speed += .05;
            bufferPlayer->setSpeed(speed);
            break;
        case '_':
            bufferPlayer->setFrame(position - 1);
            break;
        case '+':
            bufferPlayer->setFrame(position + 1);
            break;
        default:
            break;
    }

}

//------------------------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    float speed = ofMap(x, 0, ofGetWidth(), 0, 20);
//    bufferPlayer->setSpeed(speed);
}
