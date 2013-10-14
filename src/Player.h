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


#include "ofVideoPlayer.h"
#include "BaseSharedFrameProvider.h"
#include "Frame.h"


namespace ofx {
namespace Video {

    
class AbstractPlayer
{
public:
    virtual ~AbstractPlayer()
    {
    }
};


template<typename FrameType>
class Player_:
    public ofVideoPlayer,
    public BaseSharedFrameProvider_<FrameType>,
    public AbstractPlayer
{
public:
    typedef std::shared_ptr<Player_<FrameType> > SharedPtr;
    typedef std::weak_ptr<Player_<FrameType> >   WeakPtr;

    Player_();
    virtual ~Player_();

    std::shared_ptr<FrameType> getSharedFrame();

    static SharedPtr makeShared()
    {
        return SharedPtr(new Player_<FrameType>());
    }

private:
    std::shared_ptr<FrameType> _frame;
    
};


typedef Player_<Frame_<unsigned char> >              Player;
//typedef Player_<Frame_<unsigned char> >::SharedPtr   SharedPlayer;
//typedef Player_<Frame_<unsigned char> >::WeakPtr     WeakPlayer;


//------------------------------------------------------------------------------
template<typename FrameType>
Player_<FrameType>::Player_()
{
    ofVideoPlayer::setUseTexture(false);
}

//------------------------------------------------------------------------------
template<typename FrameType>
Player_<FrameType>::~Player_()
{
}

//------------------------------------------------------------------------------
template<typename FrameType>
std::shared_ptr<FrameType> Player_<FrameType>::getSharedFrame()
{
    if(!_frame || ofVideoPlayer::isFrameNew())
    {
        _frame = std::shared_ptr<FrameType>(new FrameType(ofVideoPlayer::getPixelsRef()));
    }

    return _frame;
}


} } // namespace ofx::Video
