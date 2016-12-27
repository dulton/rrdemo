/** \copyright The MIT License */
#include "H264VideoFIFOSource.hpp"

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

void H264VideoFIFOSource::doGetNextFrame()
{}

H264VideoFIFOSource::H264VideoFIFOSource(UsageEnvironment &env) :
FramedSource(env)
{}

H264VideoFIFOSource::~H264VideoFIFOSource()
{}

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo
