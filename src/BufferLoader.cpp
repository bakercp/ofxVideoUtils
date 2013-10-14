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
//#include "BufferLoader.h"
//
//
//namespace ofx {
//namespace Video {
//
//
//BufferLoader::BufferLoader(): _threadPool(Poco::ThreadPool::defaultPool())
//{
//}
//
//BufferLoader::BufferLoader(Poco::ThreadPool& threadPool):
//    _threadPool(threadPool)
//{
//}
//
//BufferLoader::~BufferLoader()
//{
//    _threadPool.joinAll();
//}
//
//void BufferLoader::load(Buffer::SharedPtr buffer,
//                        const std::string& path,
//                        Poco::Net::MediaType mimeType,
//                        Poco::Thread::Priority priority)
//{
//    
////        IMAGE,
////        IMAGE_SEQUENCE,
////        MOVIE,
////        AUTO_DETECT
//
////    _threadPool.joinAll();
//
//}
//
//void BufferLoader::load(Buffer::SharedPtr buffer,
//                        const std::string& path,
//                        Poco::Net::MediaType mimeType,
//                        unsigned long startFrame,
//                        unsigned long endFrame,
//                        Poco::Thread::Priority priority)
//{
//
//}
//
//void BufferLoader::load(Buffer::SharedPtr buffer,
//                        const std::vector<std::string>& paths,
//                        Poco::Net::MediaType mimeType,
//                        Poco::Thread::Priority priority)
//{
////    ofNotify(events.onStarted,
//
////    BufferLoaderTask::Ptr task = BufferLoaderTask::Ptr(new BufferLoaderTask(events));
//
////    _threadPool.startWithPriority(Thread::Priority priority, <#Poco::Runnable &target#>, <#const std::string &name#>)
////NoThreadAvailableException
//}
//
//void BufferLoader::cancel(Buffer::SharedPtr buffer)
//{
////    BufferLoaderTask::Ptr task;
//
////    _threadPool.
//
//
////    ofNotify(events.onStarted,
//}
//
//void BufferLoader::onFinished(const BufferLoaderEventArgs& eventArgs)
//{
//
//}
//
//
//} } // namespace ofx::Video
