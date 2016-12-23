/** \file
 *  \author zhengrr
 *  \date 2016-12-22
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_H264VIDEOFIFOSOURCE_HPP
#define _RRDEMOCDOMLIVE555_H264VIDEOFIFOSOURCE_HPP

#include <live555/FramedSource.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

#ifdef CODING

class H264VideoFifoSource : public FramedSource {
public:
    void doGetNextFrame() override;

protected:
    explicit H264VideoFifoSource(UsageEnvironment &env);

    ~H264VideoFifoSource();

};// H264VideoFifoSource

#endif// CODING

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_H264VIDEOFIFOSOURCE_HPP
