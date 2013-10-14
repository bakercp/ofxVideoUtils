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


#include "BufferLoaderTask.h"



namespace ofx {
namespace Video {

    
//------------------------------------------------------------------------------
BufferLoaderTask::BufferLoaderTask()
{
}

//------------------------------------------------------------------------------
BufferLoaderTask::~BufferLoaderTask()
{
}

////------------------------------------------------------------------------------
//void BufferLoader::loadImageAsync(Buffer::Data* buffer,
//                                          const string& filename) {
//    
//    if(isLoading()) {
//        ofLogError("BufferLoader") << "is already loading a video.  You must wait.";
//        return;
//    }
//    
//    _image = Frame::Ptr(new Frame());
//    
//    if(_image->loadImage(filename)) {
//        _loadType = BufferLoader::IMAGE;
//        _buffer = buffer;
//        _image->setUseTexture(false); // important
//        _frameCount = 1;
//        _startFrame = 0;
//        _endFrame   = 0;
//        _currentFrame = 0;
//        _buffer->clear(); // erase all of the items
//        startThread(true,false);
//    } else {
//        reset();
//        ofLog(OF_LOG_ERROR, "BufferLoader::loadImage() - image load error.");
//    }    
//}

////------------------------------------------------------------------------------
//void BufferLoader::loadMovieAsync(BufferData* _buffer,
//                                     const string& _filename) {
//    loadMovieAsync(_buffer,_filename,0);
//}
//
////------------------------------------------------------------------------------
//void BufferLoader::loadMovieAsync(BufferData* _buffer,
//                                     const string& _filename,
//                                     int _startFrame, 
//                                     int _endFrame) {
//
//    if(isLoading()) {
//        ofLogError("BufferLoader") << "is already loading a video.  You must wait.";
//        return;
//    }
//
//    if(player.loadMovie(_filename)) {
//        loadType = BufferLoader::VIDEO;
//        buffer = _buffer;
//        player.setUseTexture(false); // important
//        frameCount = player.getTotalNumFrames();
//        // TODO : fancy modulo these start / end frames
//        startFrame     = ofClamp(_startFrame,        0, frameCount - 1);
//        endFrame       = ofClamp(_endFrame, _startFrame, frameCount - 1);
//        currentFrame   = startFrame;
//        buffer->clear(); // erase all of the items
//    
//        startThread(true,false);
//    } else {
//        reset();
//        ofLog(OF_LOG_ERROR, "BufferLoader::loadMovie() - image load error.");
//    }
//}

//------------------------------------------------------------------------------
void BufferLoaderTask::cancel()
{
}

//------------------------------------------------------------------------------
float BufferLoaderTask::getPercentLoaded() const
{
    return float(_currentFrame) / (_endFrame - _startFrame);
}

////------------------------------------------------------------------------------
//bool BufferLoaderTask::isIdle() const
//{
//    return _state == BufferLoaderTask::IDLE;
//}
//
////------------------------------------------------------------------------------
//bool BufferLoaderTask::isLoading() const
//{
//    return _state == BufferLoaderTask::LOADING;
//}
//
////------------------------------------------------------------------------------
//bool BufferLoaderTask::isComplete() const
//{
//    return _state == BufferLoaderTask::COMPLETE;
//}

////------------------------------------------------------------------------------
//void BufferLoaderTask::reset()
//{
////    setState(BufferLoaderTask::IDLE);
//    _frameCount   = 0;
//    _currentFrame = 0;
//    _startFrame   = 0;
//    _endFrame     = numeric_limits<int>::max();
//
////	_buffer = NULL;
////    _player.close();
//    _frame.reset();
//    
//    _loadType = BufferLoaderTask::VIDEO;
//}

////------------------------------------------------------------------------------
//BufferLoaderTask::State BufferLoaderTask::getState() const
//{
//    return _state;
//}

//------------------------------------------------------------------------------
void BufferLoaderTask::run()
{
//    
////    setState(BufferLoaderTask::LOADING);
//
//    if(_loadType == BufferLoaderTask::IMAGE)
//    {
////        Poco::FastMutex::ScopedLock lock(_mutex);
//        //            _buffer->push_back(_frame);
//        _currentFrame++;
//    }
//    else if(_loadType == BufferLoaderTask::VIDEO)
//    {
//        while (_currentFrame <= _endFrame)
//        {
////            Poco::FastMutex::ScopedLock lock(_mutex);
//
//            Frame::Ptr frame = Frame::Ptr(new Frame());
//            //                frame->setUseTexture(false);
//            // TODO: there are strange sitatuations with set frame.
//            // setFrame(0) is equal to setFrame(1) in most cases.
//            // is this normal?
//
////            _player.setFrame(_currentFrame);
////            frame->setFromPixels(_player.getPixelsRef());
//            //                _buffer->push_back(frame);
//            _currentFrame++;
//        }
//    }
//    
////    setState(BufferLoaderTask::COMPLETE);
}

//------------------------------------------------------------------------------
unsigned long BufferLoaderTask::getStartFrame() const
{
    return _startFrame;
}

//------------------------------------------------------------------------------
unsigned long BufferLoaderTask::getEndFrame() const
{
    return _endFrame;
}

//------------------------------------------------------------------------------
unsigned long BufferLoaderTask::getCurrentFrame() const
{
    return _currentFrame;
}

//------------------------------------------------------------------------------
unsigned long BufferLoaderTask::getFrameCount() const
{
//    if(_buffer != NULL) {
//        return _frameCount;
//    } else {
//        ofLogWarning("BufferLoader") << "attempted to get the target number of frames, but the buffer is NULL.";
    return _frameCount;
}

////------------------------------------------------------------------------------
//void BufferLoaderTask::setState(BufferLoaderTask::State state)
//{
//    _state = state;
//}


} } // namespace ofx::Video
