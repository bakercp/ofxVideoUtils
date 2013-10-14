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


#include <deque>
#include "Frame.h"
#include "BaseFrameBuffer.h"


namespace ofx {
namespace Video {


template<typename FrameType>
class FrameBuffer_: public BaseFrameBuffer_<FrameType>
{
public:
    typedef std::shared_ptr<FrameBuffer_<FrameType> > SharedPtr;
    typedef std::weak_ptr<FrameBuffer_<FrameType> >   WeakPtr;

    enum Type
    {
        TYPE_FIXED   = 0,
        TYPE_CIRCULAR = 1
    };

    enum Trim
    {
        TRIM_FRONT,
        TRIM_BACK
    };
    
    FrameBuffer_<FrameType>(std::size_t capacity = DEFAULT_BUFFER_CAPACITY,
                            Type type = TYPE_FIXED);

    virtual ~FrameBuffer_<FrameType>();

    bool addFrame(std::shared_ptr<FrameType> frame);
    std::shared_ptr<FrameType> getFrame(int frameNumber) const;
    
    std::size_t getCount() const;

    void setCapacity(std::size_t capacity, Trim trim = TRIM_BACK);
    std::size_t getCapacity() const;

    // buffer modes
    void setType(Type type);
    Type getType() const;

    void  setFrameRate(float frameRate);
    float getFrameRate() const;

    void clear();  // resets all shared frames

    void setUnique(bool unique);
    bool getUnique() const;

    bool isReadOnly() const;

    std::string toString() const;

    static SharedPtr makeShared(std::size_t capacity = DEFAULT_BUFFER_CAPACITY,
                                Type type = TYPE_FIXED)
    {
        return SharedPtr(new FrameBuffer_<FrameType>(capacity,type));
    }

private:
    typedef std::deque<std::shared_ptr<FrameType> > Data;

    enum
    {
        DEFAULT_BUFFER_CAPACITY = 1,
        DEFAULT_BUFFER_FRAME_RATE = 30
    };

    FrameBuffer_<FrameType>(FrameBuffer_<FrameType>&);
    FrameBuffer_<FrameType>& operator=(const FrameBuffer_<FrameType>&);

    Data _data;
    Type _type;

    std::size_t _capacity;

    float _frameRate;

    bool _unique;

    bool _readOnly;     // just a loose flag for preventing writes

};


typedef FrameBuffer_<Frame_<unsigned char> >            FrameBuffer;


//------------------------------------------------------------------------------
template<typename FrameType>
FrameBuffer_<FrameType>::FrameBuffer_(std::size_t capacity, Type type):
    _type(type),
    _capacity(capacity),
    _frameRate(DEFAULT_BUFFER_FRAME_RATE),
    _unique(true),
    _readOnly(false)
{
}

//------------------------------------------------------------------------------
template<typename FrameType>
FrameBuffer_<FrameType>::~FrameBuffer_()
{
}

//------------------------------------------------------------------------------
template<typename FrameType>
bool FrameBuffer_<FrameType>::addFrame(std::shared_ptr<FrameType> frame)
{
    if(_readOnly) return false;

    if(_unique && !_data.empty())
    {
        if(frame == _data[_data.size()-1])
        {
            return false;
        }
    }

    switch (_type)
    {
        case TYPE_FIXED:
            if(getCount() < getCapacity())
            {
                _data.push_back(frame);
                return true;
            }
            else
            {
                return false;
            }
            break;
        case TYPE_CIRCULAR:
            if(getCount() < getCapacity())
            {
                _data.push_back(frame);
                return true;
            }
            else
            {
                _data.push_back(frame);
                _data.pop_front();
                return true;
            }
            break;
    }
}

//------------------------------------------------------------------------------
template<typename FrameType>
std::shared_ptr<FrameType> FrameBuffer_<FrameType>::getFrame(int frameNumber) const
{
    if(0 == getCount())
    {
        return FrameType::emptySharedFrame();
    }

    // super modulo
    int r = getCount();

    if(r != 0)
    {
        r = frameNumber % getCount();
        r = (r < 0) ? (r + getCount()) : (r);
    }

    return _data[r]; // wrap both + and -
}

//------------------------------------------------------------------------------
template<typename FrameType>
std::size_t FrameBuffer_<FrameType>::getCount() const
{
    return _data.size();
}

//------------------------------------------------------------------------------
template<typename FrameType>
void FrameBuffer_<FrameType>::clear()
{
    _data.clear();
}

//------------------------------------------------------------------------------
template<typename FrameType>
std::size_t FrameBuffer_<FrameType>::getCapacity() const
{
    return _capacity;
}

//------------------------------------------------------------------------------
template<typename FrameType>
void FrameBuffer_<FrameType>::setCapacity(std::size_t capacity, Trim trim)
{
    if(capacity != getCapacity() && capacity > 0)
    {
        if(capacity < getCount())
        {
            switch(trim)
            {
                case TRIM_BACK:
                    _data.erase(_data.begin(),_data.end()-capacity);
                    break;
                case TRIM_FRONT:
                    _data.erase(_data.begin()+capacity,_data.end());
                    break;
            }
        }

        _capacity = capacity;
    }
}

//------------------------------------------------------------------------------
template<typename FrameType>
void FrameBuffer_<FrameType>::setType(FrameBuffer_::Type type)
{
    _type = type;
}

//------------------------------------------------------------------------------
template<typename FrameType>
typename FrameBuffer_<FrameType>::Type FrameBuffer_<FrameType>::getType() const
{
    return _type;
}

//------------------------------------------------------------------------------
template<typename FrameType>
float FrameBuffer_<FrameType>::getFrameRate() const
{
    return _frameRate;
}

//------------------------------------------------------------------------------
template<typename FrameType>
void FrameBuffer_<FrameType>::setFrameRate(float frameRate)
{
    _frameRate = frameRate;
}

//------------------------------------------------------------------------------
template<typename FrameType>
void FrameBuffer_<FrameType>::setUnique(bool unique)
{
    _unique = unique;
}
    
//------------------------------------------------------------------------------
template<typename FrameType>
bool FrameBuffer_<FrameType>::getUnique() const
{
    return _unique;
}

//------------------------------------------------------------------------------
template<typename FrameType>
bool FrameBuffer_<FrameType>::isReadOnly() const
{
    return _readOnly;
}

//------------------------------------------------------------------------------
template<typename FrameType>
std::string FrameBuffer_<FrameType>::toString() const
{
    std::stringstream ss;
    ss << "Buffer:" << endl;
    if(_type == TYPE_FIXED) {
        ss << "\tTYPE=FIXED" << endl;
    } else if(_type == TYPE_CIRCULAR) {
        ss << "\tTYPE=PASSTHROUGH" << endl;
    }
    ss << "\tFrameRate="<< getFrameRate() << endl;
    ss << "\t%Full="<< getCount() / (float)getCapacity() << endl;
    ss << "\tCapacity="<< getCapacity() << endl;
    ss << "\tCount="<< getCount() << endl;
    ss << "\tFrameRate="<< getFrameRate() << endl;
//    ss << "\tIsLoading="<< isLoading() << endl;
//    ss << "\tIsLocked="<< isLocked() << endl;

    return ss.str();
}


} }  // namespace ofx::Video
