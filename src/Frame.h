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


#include "Poco/Timestamp.h"
#include "ofImage.h"
#include "BaseSharedFrameProvider.h"


namespace ofx {
namespace Video {


template<typename PixelType>
class Frame_: public ofImage_<PixelType>
{
public:
    typedef std::shared_ptr<Frame_<PixelType> > SharedPtr;
    typedef std::weak_ptr<Frame_<PixelType> >   WeakPtr;

    Frame_();
    Frame_(const ofPixels_<PixelType>& pixels);

    virtual ~Frame_();

    Poco::Timestamp getTimestamp() const;

    std::weak_ptr<BaseSharedFrameProvider_<Frame_<PixelType> > > getSource();

    static SharedPtr makeShared()
    {
        static std::shared_ptr<Frame_<PixelType> > empty;

        if(!empty)
        {
            ofPixels_<PixelType> pixels;
            pixels.allocate(1,1,OF_PIXELS_RGBA);
            empty = std::shared_ptr<Frame_<PixelType> >(new Frame_<PixelType>(pixels));
        }
        
        return empty;
    }

private:
    Poco::Timestamp  _timestamp;

    std::weak_ptr<BaseSharedFrameProvider_<Frame_<PixelType> > > _source;

};


typedef Frame_<unsigned char> Frame;


template<typename PixelType>
Frame_<PixelType>::Frame_():
    ofImage_<PixelType>(),
    _timestamp(Poco::Timestamp())
{
}

template<typename PixelType>
Frame_<PixelType>::Frame_(const ofPixels_<PixelType>& pixels):
    ofImage_<PixelType>(pixels),
    _timestamp(Poco::Timestamp())
{
}

template<typename PixelType>
Frame_<PixelType>::~Frame_()
{
}

template<typename PixelType>
Poco::Timestamp Frame_<PixelType>::getTimestamp() const
{
    return _timestamp;
}

template<typename PixelType>
std::weak_ptr<BaseSharedFrameProvider_<Frame_<PixelType> > > Frame_<PixelType>::getSource()
{
    return _source;
}


} } // namespace ofx::Video
