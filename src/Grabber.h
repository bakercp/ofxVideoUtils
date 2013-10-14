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


#include "ofVideoGrabber.h"
#include "BaseSharedFrameProvider.h"
#include "Frame.h"


namespace ofx {
namespace Video {


class AbstractGrabber
{
public:
    virtual ~AbstractGrabber()
    {
    }
};


template<typename FrameType>
class Grabber_:
    public AbstractGrabber,
    public ofVideoGrabber,
    public BaseSharedFrameProvider_<FrameType>
{
public:
    typedef std::shared_ptr<Grabber_<FrameType> > SharedPtr;
    typedef std::weak_ptr<Grabber_<FrameType> >   WeakPtr;

    Grabber_();
    virtual ~Grabber_();

    bool initGrabber(int w, int h);

    std::shared_ptr<FrameType> getSharedFrame();

    static SharedPtr makeShared()
    {
        return SharedPtr(new Grabber_<FrameType>());
    }

private:
    std::shared_ptr<FrameType> _frame;

};


typedef Grabber_<Frame_<unsigned char> >             Grabber;
typedef Grabber_<Frame_<unsigned char> >::SharedPtr  SharedGrabber;
typedef Grabber_<Frame_<unsigned char> >::WeakPtr    WeakGrabber;


//------------------------------------------------------------------------------
template<typename FrameType>
Grabber_<FrameType>::Grabber_()
{
    // we only upload to texture when wrapping it in a shared pointer
    // this will change when default direct-to-textures enter the oF API
    ofVideoGrabber::setUseTexture(false);
}

//------------------------------------------------------------------------------
template<typename FrameType>
Grabber_<FrameType>::~Grabber_()
{
}

//------------------------------------------------------------------------------
// override because we don't want automatic texture upload
template<typename FrameType>
bool Grabber_<FrameType>::initGrabber(int w, int h)
{
    return ofVideoGrabber::initGrabber(w,h,false);
}

//------------------------------------------------------------------------------
template<typename FrameType>
std::shared_ptr<FrameType> Grabber_<FrameType>::getSharedFrame()
{
    if(!_frame || ofVideoGrabber::isFrameNew())
    {
        _frame = std::shared_ptr<FrameType>(new FrameType(ofVideoGrabber::getPixelsRef()));
    }
    
    return _frame;
}
    

} } // namespace ofx::Video
