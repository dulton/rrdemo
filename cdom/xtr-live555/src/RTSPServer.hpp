/** \file
 *  \author zhengrr
 *  \date 2016-11-2
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_RTSPSERVER_HPP
#define _RRDEMOCDOMLIVE555_RTSPSERVER_HPP

#include <live555/RTSPServerSupportingHTTPStreaming.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

class RTSPServer : public RTSPServerSupportingHTTPStreaming {
public:
    static RTSPServer* createNew(UsageEnvironment& env,
                                 Port ourPort,
                                 UserAuthenticationDatabase* authDatabase,
                                 unsigned reclamationTestSeconds = 65);

protected:
    RTSPServer(UsageEnvironment& env, int ourSocket, Port ourPort,
               UserAuthenticationDatabase* authDatabase,
               unsigned reclamationTestSeconds);

    ~RTSPServer() override;

    ServerMediaSession *lookupServerMediaSession(
        char const* streamName, Boolean isFirstLookupInSession) override;
};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_RTSPSERVER_HPP
