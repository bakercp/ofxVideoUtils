


#pragma once

#include "ofEvents.h"
//class BufferListener {
//public:
//    virtual void bufferCleared(Buffer* buffer) = 0;
//    virtual void bufferLoadComplete(Buffer* buffer) = 0;
//};


class BufferEventArgs {
public:

//    Byffer::Ptr& buffer;
};


class BufferEvents {
public:
    ofEvent<BufferEventArgs> cleared;
    ofEvent<BufferEventArgs> complete;
    
};