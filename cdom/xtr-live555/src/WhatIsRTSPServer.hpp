/** \file
 *  \brief RTSPServer 是什么鬼.
 *  \sa <http://live555.com/liveMedia/doxygen/html/classRTSPServer.html>
 *  \author zhengrr
 *  \date 2016-10-24 – 11-1
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_WHATISRTSPSERVER_HPP
#define _RRDEMOCDOMLIVE555_WHATISRTSPSERVER_HPP

#include <live555/DigestAuthentication.hh>
#include <live555/GenericMediaServer.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

class RTSPServer : public GenericMediaServer {
public:
    static RTSPServer* createNew(
        UsageEnvironment& env,
        Port ourPort = 554,
        UserAuthenticationDatabase* authDatabase = nullptr,
        unsigned reclamationSeconds = 65);

    static Boolean lookupByName(UsageEnvironment& env,
                                char const* name,
                                RTSPServer*& resultServer);

    typedef void (responseHandlerForREGISTER)(RTSPServer* rtspServer,
                                              unsigned requestId,
                                              int resultCode,
                                              char* resultString);
    unsigned registerStream(ServerMediaSession* serverMediaSession,
                            char const* remoteClientNameOrAddress,
                            portNumBits remoteClientPortNum,
                            responseHandlerForREGISTER* responseHandler,
                            char const* username = nullptr,
                            char const* password = nullptr,
                            Boolean receiveOurStreamViaTCP = False,
                            char const* proxyURLSuffix = nullptr);

    char* rtspURL(ServerMediaSession const* serverMediaSession,
                  int clientSocket = -1) const;
    char* rtspURLPrefix(int clientSocket = -1) const;

    UserAuthenticationDatabase* setAuthenticationDatabase(
        UserAuthenticationDatabase* newDB);

    void disableStreamingRTPOverTCP() {
        fAllowStreamingRTPOverTCP = False;
    }

    Boolean setUpTunnelingOverHTTP(Port httpPort);
    portNumBits httpServerPortNum() const;

protected:
    RTSPServer(UsageEnvironment& env,
               int ourSocket, Port ourPort,
               UserAuthenticationDatabase* authDatabase,
               unsigned reclamationSeconds);
    virtual ~RTSPServer();

    virtual char const* allowedCommandNames();
    virtual Boolean weImplementREGISTER(char const* proxyURLSuffix,
                                        char*& responseStr);
    virtual void implementCmd_REGISTER(char const* url,
                                       char const* urlSuffix,
                                       int socketToRemoteServer,
                                       Boolean deliverViaTCP,
                                       char const* proxyURLSuffix);

    virtual UserAuthenticationDatabase* getAuthenticationDatabaseForCommand(
        char const* cmdName);
    virtual Boolean specialClientAccessCheck(int clientSocket,
                                             sockaddr_in& clientAddr,
                                             char const* urlSuffix);
    virtual Boolean specialClientUserAccessCheck(int clientSocket,
                                                 sockaddr_in& clientAddr,
                                                 char const* urlSuffix,
                                                 char const *username);

private:
    Boolean isRTSPServer() const override;

public:
    class RTSPClientSession;
    class RTSPClientConnection : public ClientConnection {
    public:
        class ParamsForREGISTER {
        public:
            ParamsForREGISTER(RTSPClientConnection* ourConnection,
                              char const* url,
                              char const* urlSuffix,
                              Boolean reuseConnection,
                              Boolean deliverViaTCP,
                              char const* proxyURLSuffix);
            virtual ~ParamsForREGISTER();
        private:
            friend class RTSPClientConnection;
            RTSPClientConnection* fOurConnection;
            char* fURL;
            char* fURLSuffix;
            Boolean fReuseConnection, fDeliverViaTCP;
            char* fProxyURLSuffix;
        };
    protected:
        void handleRequestBytes(int newBytesRead) override;

        RTSPClientConnection(RTSPServer& ourServer,
                             int clientSocket,
                             sockaddr_in clientAddr);
        virtual ~RTSPClientConnection();

        friend class RTSPServer;
        friend class RTSPClientSession;

        virtual void handleCmd_OPTIONS();
        virtual void handleCmd_GET_PARAMETER(char const* fullRequestStr);
        virtual void handleCmd_SET_PARAMETER(char const* fullRequestStr);
        virtual void handleCmd_DESCRIBE(char const* urlPreSuffix,
                                        char const* urlSuffix,
                                        char const* fullRequestStr);
        virtual void handleCmd_REGISTER(char const* url,
                                        char const* urlSuffix,
                                        char const* fullRequestStr,
                                        Boolean reuseConnection,
                                        Boolean deliverViaTCP,
                                        char const* proxyURLSuffix);
        virtual void handleCmd_bad();
        virtual void handleCmd_notSupported();
        virtual void handleCmd_notFound();
        virtual void handleCmd_sessionNotFound();
        virtual void handleCmd_unsupportedTransport();

        virtual Boolean parseHTTPRequestString(char* resultCmdName,
                                               unsigned resultCmdNameMaxSize,
                                               char* urlSuffix,
                                               unsigned urlSuffixMaxSize,
                                               char* sessionCookie,
                                               unsigned sessionCookieMaxSize,
                                               char* acceptStr,
                                               unsigned acceptStrMaxSize);
        virtual void handleHTTPCmd_notSupported();
        virtual void handleHTTPCmd_notFound();
        virtual void handleHTTPCmd_OPTIONS();
        virtual void handleHTTPCmd_TunnelingGET(char const* sessionCookie);
        virtual Boolean handleHTTPCmd_TunnelingPOST(
            char const* sessionCookie,
            unsigned char const* extraData,
            unsigned extraDataSize);
        virtual void handleHTTPCmd_StreamingGET(char const* urlSuffix,
                                                char const* fullRequestStr);
        void resetRequestBuffer();
        void closeSocketsRTSP();
        static void handleAlternativeRequestByte(void*,
                                                 u_int8_t requestByte);
        void handleAlternativeRequestByte1(u_int8_t requestByte);
        Boolean authenticationOK(char const* cmdName,
                                 char const* urlSuffix,
                                 char const* fullRequestStr);
        void changeClientInputSocket(int newSocketNum,
                                     unsigned char const* extraData,
                                     unsigned extraDataSize);
        static void continueHandlingREGISTER(ParamsForREGISTER* params);
        virtual void continueHandlingREGISTER1(ParamsForREGISTER* params);

        void setRTSPResponse(char const* responseStr);
        void setRTSPResponse(char const* responseStr,
                             u_int32_t sessionId);
        void setRTSPResponse(char const* responseStr,
                             char const* contentStr);
        void setRTSPResponse(char const* responseStr,
                             u_int32_t sessionId,
                             char const* contentStr);

        RTSPServer& fOurRTSPServer;
        int& fClientInputSocket;
        int fClientOutputSocket;
        Boolean fIsActive;
        unsigned char* fLastCRLF;
        unsigned fRecursionCount;
        char const* fCurrentCSeq;
        Authenticator fCurrentAuthenticator;
        char* fOurSessionCookie;
        unsigned fBase64RemainderCount;
    };

    class RTSPClientSession : public ClientSession {
    protected:
        RTSPClientSession(RTSPServer& ourServer, u_int32_t sessionId);
        virtual ~RTSPClientSession();

        friend class RTSPServer;
        friend class RTSPClientConnection;
        virtual void handleCmd_SETUP(RTSPClientConnection* ourClientConnection,
                                     char const* urlPreSuffix,
                                     char const* urlSuffix,
                                     char const* fullRequestStr);
        virtual void handleCmd_withinSession(
            RTSPClientConnection* ourClientConnection,
            char const* cmdName,
            char const* urlPreSuffix,
            char const* urlSuffix,
            char const* fullRequestStr);
        virtual void handleCmd_TEARDOWN(
            RTSPClientConnection* ourClientConnection,
            ServerMediaSubsession* subsession);
        virtual void handleCmd_PLAY(
            RTSPClientConnection* ourClientConnection,
            ServerMediaSubsession* subsession,
            char const* fullRequestStr);
        virtual void handleCmd_PAUSE(
            RTSPClientConnection* ourClientConnection,
            ServerMediaSubsession* subsession);
        virtual void handleCmd_GET_PARAMETER(
            RTSPClientConnection* ourClientConnection,
            ServerMediaSubsession* subsession,
            char const* fullRequestStr);
        virtual void handleCmd_SET_PARAMETER(
            RTSPClientConnection* ourClientConnection,
            ServerMediaSubsession* subsession,
            char const* fullRequestStr);

        void deleteStreamByTrack(unsigned trackNum);
        void reclaimStreamStates();
        Boolean isMulticast() const { return fIsMulticast; }

        static void setRTSPResponse(RTSPClientConnection* ourClientConnection,
                                    char const* responseStr) {
            ourClientConnection->setRTSPResponse(responseStr);
        }

        static void setRTSPResponse(RTSPClientConnection* ourClientConnection,
                                    char const* responseStr,
                                    u_int32_t sessionId) {
            ourClientConnection->setRTSPResponse(responseStr, sessionId);
        }

        static void setRTSPResponse(RTSPClientConnection* ourClientConnection,
                                    char const* responseStr,
                                    char const* contentStr) {
            ourClientConnection->setRTSPResponse(responseStr, contentStr);
        }

        static void setRTSPResponse(RTSPClientConnection* ourClientConnection,
                                    char const* responseStr,
                                    u_int32_t sessionId,
                                    char const* contentStr) {
            ourClientConnection->setRTSPResponse(responseStr, sessionId, contentStr);
        }

        RTSPServer& fOurRTSPServer;
        Boolean fIsMulticast, fStreamAfterSETUP;
        unsigned char fTCPStreamIdCount;
        Boolean usesTCPTransport() const { return fTCPStreamIdCount > 0; }
        unsigned fNumStreamStates;
        struct streamState {
            ServerMediaSubsession* subsession;
            int tcpSocketNum;
            void* streamToken;
        } *fStreamStates;
    };

protected:
    ClientConnection* createNewClientConnection(
        int clientSocket,
        sockaddr_in clientAddr) override;

    ClientSession* createNewClientSession(u_int32_t sessionId) override;

private:
    static void incomingConnectionHandlerHTTP(void*, int);
    void incomingConnectionHandlerHTTP();

    void noteTCPStreamingOnSocket(int socketNum,
                                  RTSPClientSession* clientSession,
                                  unsigned trackNum);
    void unnoteTCPStreamingOnSocket(int socketNum,
                                    RTSPClientSession* clientSession,
                                    unsigned trackNum);
    void stopTCPStreamingOnSocket(int socketNum);

    friend class RTSPClientConnection;
    friend class RTSPClientSession;
    friend class RegisterRequestRecord;
    int fHTTPServerSocket;
    Port fHTTPServerPort;
    HashTable* fClientConnectionsForHTTPTunneling;
    HashTable* fTCPStreamingDatabase;
    HashTable* fPendingRegisterRequests;
    unsigned fRegisterRequestCounter;
    UserAuthenticationDatabase* fAuthDB;
    Boolean fAllowStreamingRTPOverTCP;
};


class RTSPServerWithREGISTERProxying : public RTSPServer {
public:
    static RTSPServerWithREGISTERProxying* createNew(
        UsageEnvironment& env,
        Port ourPort = 554,
        UserAuthenticationDatabase* authDatabase = nullptr,
        UserAuthenticationDatabase* authDatabaseForREGISTER = nullptr,
        unsigned reclamationSeconds = 65,
        Boolean streamRTPOverTCP = False,
        int verbosityLevelForProxying = 0);

protected:
    RTSPServerWithREGISTERProxying(
        UsageEnvironment& env,
        int ourSocket,
        Port ourPort,
        UserAuthenticationDatabase* authDatabase,
        UserAuthenticationDatabase* authDatabaseForREGISTER,
        unsigned reclamationSeconds,
        Boolean streamRTPOverTCP,
        int verbosityLevelForProxying);

    virtual ~RTSPServerWithREGISTERProxying();

    char const* allowedCommandNames() override;
    Boolean weImplementREGISTER(char const* proxyURLSuffix,
                                char*& responseStr) override;
    void implementCmd_REGISTER(char const* url,
                               char const* urlSuffix,
                               int socketToRemoteServer,
                               Boolean deliverViaTCP,
                               char const* proxyURLSuffix) override;
    UserAuthenticationDatabase* getAuthenticationDatabaseForCommand(
        char const* cmdName) override;

private:
    Boolean fStreamRTPOverTCP;
    int fVerbosityLevelForProxying;
    unsigned fRegisteredProxyCounter;
    char* fAllowedCommandNames;
    UserAuthenticationDatabase* fAuthDBForREGISTER;
};

void parseTransportHeaderForREGISTER(char const* buf,
                                     Boolean &reuseConnection,
                                     Boolean& deliverViaTCP,
                                     char*& proxyURLSuffix);

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#endif// _RRDEMOCDOMLIVE555_WHATISRTSPSERVER_HPP
