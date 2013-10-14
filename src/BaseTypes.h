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


//----------------------------------------------------------
// ofBaseVideo
//----------------------------------------------------------
template<typename T>
class BaseVideo_: virtual public ofBaseHasPixels_<T>, public ofBaseUpdates
{
public:
	virtual ~BaseVideo_(){}
	virtual bool isFrameNew() const = 0;
	virtual void close() = 0;
};


typedef BaseVideo_<unsigned char>  BaseVideo;
typedef BaseVideo_<float>          BaseFloatVideo;
typedef BaseVideo_<unsigned short> BaseShortVideo;


template<typename T>
class BaseVideoDraws_: virtual public BaseVideo_<T>, public ofBaseImage_<T>
{
public:
	virtual ~BaseVideoDraws_(){}
};


typedef BaseVideoDraws_<unsigned char>  BaseVideoDraws;
typedef BaseVideoDraws_<float>          BaseFloatVideoDraws;
typedef BaseVideoDraws_<unsigned short> BaseShortVideoDraws;

