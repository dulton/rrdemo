/** \copyright The MIT License */
#include "h264_video_fifo_source.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

void H264VideoFifoSource::doGetNextFrame()
{}

H264VideoFifoSource::H264VideoFifoSource(UsageEnvironment &env) :
FramedSource(env)
{}

H264VideoFifoSource::~H264VideoFifoSource()
{}

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo
