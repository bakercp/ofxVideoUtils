//// =============================================================================
////
//// Copyright (c) 2010-2013 Christopher Baker <http://christopherbaker.net>
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in
//// all copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//// THE SOFTWARE.
////
//// =============================================================================
//
//
//#pragma once
//
//
//#include "Poco/Exception.h"
//#include "Poco/Net/MediaType.h"
//#include "Poco/Path.h"
//#include "ofEvents.h"
//#include "Buffer.h"
//#include "BufferLoaderEvents.h"
//#include "BufferLoaderTask.h"
//
//
//namespace ofx {
//namespace Video {
//
//
//class BufferLoader
//{
//public:
//    enum MediaType {
//        VIDEO = 0,
//        IMAGE = 1,
//        IMAGE_SEQUENCE = 2,
//    };
//
//    BufferLoader();
//    BufferLoader(Poco::ThreadPool& threadPool);
//    
//    virtual ~BufferLoader();
//
//    void load(Buffer::SharedPtr buffer,
//              const std::string& path,
//              Poco::Net::MediaType mimeType,
//              Poco::Thread::Priority priority = Poco::Thread::PRIO_NORMAL);
//
//    void load(Buffer::SharedPtr buffer,
//              const std::string& path,
//              Poco::Net::MediaType mimeType,
//              unsigned long startFrame,
//              unsigned long endFrame,
//              Poco::Thread::Priority priority = Poco::Thread::PRIO_NORMAL);
//
//    void load(Buffer::SharedPtr buffer,
//              const std::vector<std::string>& paths,
//              Poco::Net::MediaType mimeType,
//              Poco::Thread::Priority priority = Poco::Thread::PRIO_NORMAL);
//
//    void cancel(Buffer::SharedPtr buffer);
//
//    template<class ListenerClass>
//    void registerBufferLoaderEvents(ListenerClass* listener);
//
//    template<class ListenerClass>
//    void unregisterBufferLoaderEvents(ListenerClass* listener);
//
//    BufferLoaderEvents events;
//
//private:
//    void onFinished(const BufferLoaderEventArgs& eventArgs);
//
//    enum
//    {
//        FIRST_FRAME = -1,
//        LAST_FRAME = -1,
//    };
//
//    typedef std::map<Buffer::SharedPtr, BufferLoaderTask::SharedPtr> BufferTaskMap;
//
//    BufferTaskMap _taskMap;
//
//    Poco::ThreadPool& _threadPool;
//
//    mutable Poco::FastMutex _mutex;
//
//};
//
//
//template<class ListenerClass>
//void BufferLoader::registerBufferLoaderEvents(ListenerClass* listener)
//{
//    ofAddListener(events.onStarted,     listener, &ListenerClass::onStarted);
//    ofAddListener(events.onCancelled,   listener, &ListenerClass::onCancelled);
//    ofAddListener(events.onFinished,    listener, &ListenerClass::onFinished);
//    ofAddListener(events.onFailed,      listener, &ListenerClass::onFailed);
//    ofAddListener(events.onProgress,    listener, &ListenerClass::onProgress);
//}
//
//template<class ListenerClass>
//void BufferLoader::unregisterBufferLoaderEvents(ListenerClass* listener)
//{
//    ofRemoveListener(events.onStarted,     listener, &ListenerClass::onStarted);
//    ofRemoveListener(events.onCancelled,   listener, &ListenerClass::onCancelled);
//    ofRemoveListener(events.onFinished,    listener, &ListenerClass::onFinished);
//    ofRemoveListener(events.onFailed,      listener, &ListenerClass::onFailed);
//    ofRemoveListener(events.onProgress,    listener, &ListenerClass::onProgress);
//}
//
//
//} } // namespace ofx::Video
