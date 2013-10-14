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


#include "ofBaseTypes.h"
#include "BaseTypes.h"
#include "BaseSharedFrameProvider.h"
#include "FrameBuffer.h"


namespace ofx {
namespace Video {

template<typename FrameType, typename PixelType>
class FrameBufferPlayer_:
    public BaseVideoDraws_<PixelType>,
    public BaseSharedFrameProvider_<FrameType>
{
public:
    typedef std::shared_ptr<FrameBufferPlayer_<FrameType,PixelType> > SharedPtr;
    typedef std::weak_ptr<FrameBufferPlayer_<FrameType,PixelType> >   WeakPtr;

    FrameBufferPlayer_();
    ~FrameBufferPlayer_();

    void loadBuffer(std::shared_ptr<FrameBuffer_<FrameType> > buffer);
    bool isLoaded() const;

    void reset();

    //////////////////////////////////////////////////
    // ofBaseVideo ///////////////////////////////////
    bool isFrameNew() const;
	void close();

    //////////////////////////////////////////////////
    // ofBaseDraws ///////////////////////////////////
	void draw(float x, float y);
	void draw(float x, float y, float w, float h);

    float getHeight() const;
	float getWidth() const;

	float getHeight(); // base class const correct issue
	float getWidth(); // base class const correct issue

    //////////////////////////////////////////////////
    // ofBaseTexture /////////////////////////////////
	ofTexture& getTextureReference();
	void setUseTexture(bool bUseTex);

    //////////////////////////////////////////////////
    // ofBaseHasPixels ///////////////////////////////
	PixelType* getPixels();
	ofPixels_<PixelType>& getPixelsRef();

    //////////////////////////////////////////////////
    // ofBaseUpdate //////////////////////////////////
	void update();  // like idle(), claculates the current frame position
                    // for the player based on real-time values

    //////////////////////////////////////////////////
    // Looping ///////////////////////////////////////
    void setLoopPoints(int start, int end);
    void setLoopPointStart(int frame);
    void setLoopPointEnd(int frame);

    void setLoopPointsNorm(float startn, float endn);
    void setLoopPointStartNorm(float framen);
    void setLoopPointEndNorm(float framen);
    
	int getLoopPointStart() const;
    int getLoopPointEnd() const;

    float getLoopPointStartNorm() const;
    float getLoopPointEndNorm() const;

    void clearLoopPoints();
    
    void setLoopType(ofLoopType loopType);
	ofLoopType getLoopType() const;
    
    //////////////////////////////////////////////////
    // Positioning ///////////////////////////////////
    void  setFrame(int frame);
    void  setFrameNorm(float framen);
    int   getFrame() const;
    float getFrameNorm() const;
    
    //////////////////////////////////////////////////
    // Playback //////////////////////////////////////
    void  start();
    void  stop();
    
    bool  isPlaying() const;
    
    void  setPaused(bool isPaused);
    bool  isPaused() const;
    
    void  setSpeed(float speed);
    float getSpeed() const;
    
    float getFrameRate() const;
    float getFrameDuration() const;

    // Buffer access
    int getCount() const;
    int getCapacity() const;

    //////////////////////////////////////////////////
    // Utility ///////////////////////////////////////
    
    std::string toString() /*const of is not const correct */;

    std::shared_ptr<FrameType> getSharedFrame() const;
    std::shared_ptr<FrameType> getSharedFrame();

    static SharedPtr makeShared()
    {
        return SharedPtr(new FrameBufferPlayer_());
    }

private:
    typedef std::weak_ptr<FrameBuffer_<FrameType> > Data;

    Data _buffer;

    // playback
    bool  _isPlaying;       // is stopped?
    bool  _isPaused;        // is paused?
    float _speed;           // the speed scaler
    float _playDirection;   // forward or backward (for palindrome)
    
    // frame indicies, times, etc
    bool _isFrameNew;
    int _lastFrame;             // the last frame that was pushed
    int _currentFrame;          // the current frame
    float _lastFramePushTime;   // the time when the last frame was pushed, (ms)
    float _lastFrameFraction;   // the fraction of the frame that will be sent
                                // with the next batch (i.e. if if our pushed
                                // frame calculation ended up in the middle
                                // of a frame.)
    // looping        
    ofLoopType _loopType;   // the player's loop type
    
	int _loopPointsStart;   // the loop start point
	int _loopPointsEnd;     // the loop stop  point
	
    int bufferMod(int frame) const;


    int frameNormToFrame(float n) const;
    float frameToFrameNorm(int frame) const;

    bool fequals(float f0, float f1)
    {
        return std::fabs(f1 - f0) < std::numeric_limits<float>::epsilon();
    }

};


typedef FrameBufferPlayer_<Frame_<unsigned char>,unsigned char > FrameBufferPlayer;
//typedef FrameBufferPlayer_<Frame_<unsigned char>,unsigned char >::SharedPtr SharedFrameBufferPlayer;
//typedef FrameBufferPlayer_<Frame_<unsigned char>,unsigned char >::WeakPtr   WeakFrameBufferPlayer;


//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
FrameBufferPlayer_<FrameType,PixelType>::FrameBufferPlayer_()
{
    reset();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
FrameBufferPlayer_<FrameType,PixelType>::~FrameBufferPlayer_()
{
    reset();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::loadBuffer(std::shared_ptr<FrameBuffer_<FrameType> > buffer)
{
    _buffer = buffer;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
bool FrameBufferPlayer_<FrameType,PixelType>::isLoaded() const
{
    return !_buffer.expired();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::reset()
{
    _buffer.reset();

    _speed = 1.0f;
    _playDirection = true;

    // frame indicies, times, etc
    _isPlaying = false;
    _isPaused = false;
    _isFrameNew = true;
    _lastFrame = -1;
    _currentFrame = 0;

    _lastFramePushTime = -1;
    _lastFrameFraction = 0.0f;

    _loopPointsStart = -1;
    _loopPointsEnd = -1;

    _loopType = OF_LOOP_NORMAL;

}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
bool FrameBufferPlayer_<FrameType,PixelType>::isFrameNew() const
{
    return _isFrameNew;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::close()
{
    reset();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
PixelType* FrameBufferPlayer_<FrameType,PixelType>::getPixels()
{
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
ofPixels_<PixelType>& FrameBufferPlayer_<FrameType,PixelType>::getPixelsRef()
{
    return getSharedFrame()->getPixelsRef();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::draw(float x, float y)
{
    return getSharedFrame()->draw(x,y);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::draw(float x,
                                                   float y,
                                                   float w,
                                                   float h)
{
    return getSharedFrame()->draw(x,y,w,h);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getHeight() const
{
    return getSharedFrame()->getHeight();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getWidth() const
{
    return getSharedFrame()->getWidth();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getHeight()
{
    return getSharedFrame()->getHeight();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getWidth()
{
    return getSharedFrame()->getWidth();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
ofTexture& FrameBufferPlayer_<FrameType,PixelType>::getTextureReference()
{
    return getSharedFrame()->getTextureReference();
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setUseTexture(bool bUseTex)
{
    return getSharedFrame()->setUseTexture(bUseTex);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::getCount() const
{
    std::shared_ptr<FrameBuffer_<FrameType> > buffer = _buffer.lock();

    if(buffer)
    {
        return buffer->getCount();
    }
    else
    {
        return 0;
    }
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::getCapacity() const
{
    std::shared_ptr<FrameBuffer_<FrameType> > buffer = _buffer.lock();

    if(buffer)
    {
        return buffer->getCapacity();
    }
    else
    {
        return 0;
    }
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::update() {


    if(!isLoaded()) {
        // cout << "failed to update - not loaded" << endl;

        return;
    }

    //    if(isEmpty()) {
    //        //cout << "failed to update - is empty" << endl;
    //
    //        return;
    //    }

    if(!isPlaying()) {
        // cout << "failed to update - is not playing" << endl;

        return;
    }

    float now = ofGetElapsedTimef();

    if(isPaused()) {
        //        cout << "failed to update - is paused" << endl;
        _lastFramePushTime = now;
        return;
    }


    // if this is the first time
    if(_lastFramePushTime < -1)
    {
        _lastFramePushTime = now;
    }

    float elapsedTime = (now - _lastFramePushTime); // elapsed time, ms

    float numFramesToPush = 0; // can be negative

    if(!fequals(getSpeed(), 0.0f))
    {
        float frameDuration = getFrameDuration();  //
        numFramesToPush     = elapsedTime / frameDuration; // can be negative
        numFramesToPush    += _lastFrameFraction;           // add on any leftovers from last frame

        float fNumFramesToPush = std::floor(numFramesToPush);

        _lastFrameFraction   =  numFramesToPush - fNumFramesToPush;
        numFramesToPush     = fNumFramesToPush;

    } else {
        _lastFrameFraction = 0; //
    }

    ///////////////////////////////////////////

    _lastFramePushTime = now;

    if(!fequals(numFramesToPush,0.0f))
    {
        if(_loopType == OF_LOOP_NONE)
        {
            _currentFrame += numFramesToPush; // may not be w/in range
            _currentFrame = CLAMP(_currentFrame, 0, getCount() - 1);
        }
        else
        {
            // get loop points
            int loopStart = getLoopPointStart();
            int loopEnd   = getLoopPointEnd();

            // check to see if they are set.  when -1, they are not set, so assum maximums
            if(loopStart < 0) loopStart = 0;
            if(loopEnd < 0)   loopEnd   = getCount() - 1;

            int minFrame = MIN(loopStart,loopEnd);  // already accounts for loop enabled
            int maxFrame = MAX(loopStart,loopEnd); // already accounts for loop enabled

            int nFramesInLoop = maxFrame - minFrame;

            if(nFramesInLoop <= 0)
            {
                // there's nothing to do here
                // except stay in the same place
                return;
            }

            if(_loopType == OF_LOOP_NORMAL)
            {
                _currentFrame += numFramesToPush;
                // may not be w/in range, could be negative
                // check range and loop appropraitely

                if(_currentFrame > maxFrame)
                {
                    _currentFrame = minFrame + (_currentFrame - maxFrame) % (nFramesInLoop);
                }
                else if(_currentFrame < minFrame)
                {
                    _currentFrame = maxFrame - (minFrame - _currentFrame) % (nFramesInLoop);
                }

            }
            else if(_loopType == OF_LOOP_PALINDROME)
            {
                // directionality is controlled not by speed vector but by palindrome state
                int absNumFramesToPush = std::fabs(numFramesToPush);

                _currentFrame += (_playDirection) ? absNumFramesToPush : -absNumFramesToPush;

                // we are outside of the range!
                if(_currentFrame < minFrame || _currentFrame > maxFrame)
                {
                    int overshoot = 0;

                    if(_currentFrame > maxFrame)
                    {
                        overshoot = (_currentFrame - maxFrame);
                    }
                    else
                    {
                        overshoot = (minFrame - _currentFrame);
                    }

                    // recursively reduce overshoot by folding

                    while (overshoot > nFramesInLoop)
                    {
                        overshoot -= nFramesInLoop;
                        _playDirection = !_playDirection;
                    }

                    if(_playDirection)
                    {
                        _currentFrame = (maxFrame - overshoot);
                    }
                    else
                    {
                        _currentFrame = (minFrame + overshoot);
                    }

                    _playDirection = !_playDirection;

                }
                else
                {
                    // just stick with it!
                }
            }
        }
    }

    _isFrameNew = (_lastFrame != _currentFrame);
    _lastFrame = _currentFrame;

}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopPoints(int start, int end)
{
    setLoopPointStart(start);
    setLoopPointEnd(end);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopPointStart(int frame)
{
    _loopPointsStart = frame;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopPointEnd(int frame)
{
    _loopPointsEnd = frame;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::getLoopPointStart() const
{
    return _loopPointsStart;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::getLoopPointEnd() const
{
    return _loopPointsEnd;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopPointsNorm(float start,
                                                                float end)
{
    setLoopPointStartNorm(start);
    setLoopPointEndNorm(end);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopPointStartNorm(float frame)
{
    setLoopPointStart(frameNormToFrame(frame));
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopPointEndNorm(float frame)
{
    setLoopPointEnd(frameNormToFrame(frame));
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getLoopPointStartNorm() const
{
    return frameToFrameNorm(getLoopPointStart());
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getLoopPointEndNorm() const
{
    return frameToFrameNorm(getLoopPointEnd());
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::clearLoopPoints()
{
    _loopPointsStart = -1;
    _loopPointsEnd   = -1;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setLoopType(ofLoopType loopType)
{
    switch (loopType)
    {
        case OF_LOOP_PALINDROME:
            _playDirection = (getSpeed() > 0); // reset
            break;
        case OF_LOOP_NORMAL:
        case OF_LOOP_NONE:
        default:
            break;
    }

    _loopType = loopType;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
ofLoopType FrameBufferPlayer_<FrameType,PixelType>::getLoopType() const
{
    return _loopType;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setFrame(int frame)
{
    _currentFrame = bufferMod(frame);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setFrameNorm(float n)
{
    setFrame(frameNormToFrame(n));
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::getFrame() const
{
    return _currentFrame;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getFrameNorm() const
{
    return frameToFrameNorm(_currentFrame);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::start()
{
    _isPlaying = true;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::stop()
{
    _isPlaying = false;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
bool FrameBufferPlayer_<FrameType,PixelType>::isPlaying() const
{
    return _isPlaying;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setPaused(bool isPaused)
{
    _isPaused = isPaused;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
bool FrameBufferPlayer_<FrameType,PixelType>::isPaused() const
{
    return _isPaused;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
void FrameBufferPlayer_<FrameType,PixelType>::setSpeed(float speed)
{
    _speed = speed;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getSpeed() const
{
    return _speed;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getFrameRate() const
{
    std::shared_ptr<FrameBuffer_<FrameType> > buffer = _buffer.lock();

    if(buffer)
    {
        return buffer->getFrameRate();
    }
    else
    {
        return 0;
    }
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::getFrameDuration() const
{
    return 1.0f / (getFrameRate() * getSpeed());
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
std::string FrameBufferPlayer_<FrameType,PixelType>::toString() /*const of is not const correct */{
    std::string stats = "";
//    stats+= ("Count, Size   [" + ofToString(getCount())) + "," + ofToString(getSize()) + "]\n";
//    stats+=  "IsEmpty       [" + ofToString(isEmpty()) + "]\n";
//    stats+=  "Loop Points   [" + ofToString(getLoopPointStart()) + "," + ofToString(getLoopPointEnd()) + "]\n";
//    
//    stats+= "Buffer Type   [";
//    
//    if(!isLoaded()) {
////        stats+= "No Source Loaded";
////    } else if(isImagePlayer()) {
////        stats+= "Image Player";
////    } else if(isVideoPlayer()) {
////        stats+= "Video Player";
////    } else if(isBufferPlayer()) {
////        // cout << "IN HERE BUFFER PLAYER!! > source type == " << sourceType << endl;
//        Buffer::Mode type = getVideoBuffer()->getMode();
//
//        
//
////        if(type == Buffer::FIXED) {
////            stats+="Buffer Player FIXED";
////        } else if(type == Buffer::CIRCULAR) {
////            stats+="Buffer Player CIRCULAR";
////        } else if(type == Buffer::PASSTHROUGH) {
////            stats+="Buffer Player PASSTHROUGH";
////        }
////    }
//
//    stats+= "]\n";
//    
//    string lts = "";
//    ofLoopType lt = getLoopType();
//    if(lt == OF_LOOP_NONE) {
//        lts = "NONE";
//    } else if(lt == OF_LOOP_NORMAL) {
//        lts = "NORMAL";
//    } else if(lt == OF_LOOP_PALINDROME) {
//        lts = "PALINDROME";
//    }
//    
//    stats+= "Loop Mode     [" + lts + "]\n";
//    stats+= "Is Playing    [" + ofToString(isPlaying()) + "]\n";
//    stats+= "Current Frame [" + ofToString(getFrame()) + "]\n";
//    stats+= "Speed         [" + ofToString(getSpeed()) + "]";
//    return stats;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::bufferMod(int frame) const
{
    int cnt = getCount();
    int r = cnt;
    if(r != 0)
    {
        r = frame % cnt;
        if(r < 0)
        {
            r += cnt;
        }
    }
    
    return r;
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
int FrameBufferPlayer_<FrameType,PixelType>::frameNormToFrame(float n) const
{
    return bufferMod(ofMap(n, 0, 1, 0, getCount()));
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
float FrameBufferPlayer_<FrameType,PixelType>::frameToFrameNorm(int frame) const
{
    return ofMap(bufferMod(frame), 0, getCount(), 0, 1);
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
std::shared_ptr<FrameType> FrameBufferPlayer_<FrameType,PixelType>::getSharedFrame() const
{
    std::shared_ptr<FrameBuffer_<FrameType> > buffer = _buffer.lock();

    if(buffer)
    {
        return buffer->getFrame(_currentFrame);
    }
    else
    {
        return FrameType::emptySharedFrame();
    }
}

//------------------------------------------------------------------------------
template<typename FrameType,typename PixelType>
std::shared_ptr<FrameType> FrameBufferPlayer_<FrameType,PixelType>::getSharedFrame()
{
    std::shared_ptr<FrameBuffer_<FrameType> > buffer = _buffer.lock();

    if(buffer)
    {
        return buffer->getFrame(_currentFrame);
    }
    else
    {
        return FrameType::makeShared();
    }
}

    
} }  // namespace ofx::Video
