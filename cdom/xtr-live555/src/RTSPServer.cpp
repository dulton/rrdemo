/** \copyright The MIT License */
#include "RTSPServer.hpp"

#include <CString>

#include <live555/liveMedia.hh>

namespace {

struct MatroskaDemuxCreationState {
    MatroskaFileServerDemux* demux;
    char watchVariable;
};
void onMatroskaDemuxCreation(MatroskaFileServerDemux* newDemux,
                             void* clientData) {
    auto creationState = static_cast<MatroskaDemuxCreationState*>(clientData);
    creationState->demux = newDemux;
    creationState->watchVariable = 1;
}

struct OggDemuxCreationState {
    OggFileServerDemux* demux;
    char watchVariable;
};
void onOggDemuxCreation(OggFileServerDemux* newDemux,
                        void* clientData) {
    auto creationState = static_cast<OggDemuxCreationState*>(clientData);
    creationState->demux = newDemux;
    creationState->watchVariable = 1;
}

#define NEW_SMS(description) do {\
    char const* descStr = description\
    ", streamed by the LIVE555 Media Server";\
    sms = ServerMediaSession::createNew(env, fileName, fileName, descStr);\
} while(0)

ServerMediaSession* createNewSMS(UsageEnvironment& env,
                                 char const* fileName,
                                 FILE*) {
    auto extension = strrchr(fileName, '.');
    if (!extension) return nullptr;

    ServerMediaSession* sms = nullptr;
    auto const reuseSource = false;
    if (!strcmp(extension, ".aac")) {
        sms->addSubsession(ADTSAudioFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".amr")) {
        sms->addSubsession(AMRAudioFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".ac3")) {
        sms->addSubsession(AC3AudioFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".m4e")) {
        sms->addSubsession(MPEG4VideoFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".264")) {
        OutPacketBuffer::maxSize = 100000;
        sms->addSubsession(H264VideoFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".265")) {
        OutPacketBuffer::maxSize = 100000;
        sms->addSubsession(H265VideoFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".mp3")) {
        auto useADUs = False;
        Interleaving* interleaving = nullptr;
        sms->addSubsession(MP3AudioFileServerMediaSubsession::createNew(
            env, fileName, reuseSource, useADUs, interleaving));
    } else if (!strcmp(extension, ".mpg")) {
        auto demux = MPEG1or2FileServerDemux::createNew(
            env, fileName, reuseSource);
        sms->addSubsession(demux->newVideoServerMediaSubsession());
        sms->addSubsession(demux->newAudioServerMediaSubsession());
    } else if (!strcmp(extension, ".vob")) {
        auto demux = MPEG1or2FileServerDemux::createNew(
            env, fileName, reuseSource);
        sms->addSubsession(demux->newVideoServerMediaSubsession());
        sms->addSubsession(demux->newAC3AudioServerMediaSubsession());
    } else if (!strcmp(extension, ".ts")) {
        auto indexFileNameLen = strlen(fileName) + 2;
        auto indexFileName = new char[indexFileNameLen];
        sprintf(indexFileName, "%sx", fileName);
        sms->addSubsession(MPEG2TransportFileServerMediaSubsession::createNew(
            env, fileName, indexFileName, reuseSource));
        delete[] indexFileName;
    } else if (!strcmp(extension, ".wav")) {
        auto convertToULaw = False;
        sms->addSubsession(WAVAudioFileServerMediaSubsession::createNew(
            env, fileName, reuseSource, convertToULaw));
    } else if (!strcmp(extension, ".dv")) {
        OutPacketBuffer::maxSize = 300000;
        sms->addSubsession(DVVideoFileServerMediaSubsession::createNew(
            env, fileName, reuseSource));
    } else if (!strcmp(extension, ".mkv") ||
               !strcmp(extension, ".webm")) {
        OutPacketBuffer::maxSize = 100000;
        MatroskaDemuxCreationState creationState;
        creationState.watchVariable = 0;
        MatroskaFileServerDemux::createNew(
            env, fileName, onMatroskaDemuxCreation, &creationState);
        env.taskScheduler().doEventLoop(&creationState.watchVariable);

        ServerMediaSubsession* smss;
        while ((smss = creationState.demux->newServerMediaSubsession())
               != nullptr) {
            sms->addSubsession(smss);
        }
    } else if (!strcmp(extension, ".ogg") ||
               !strcmp(extension, ".ogv") ||
               !strcmp(extension, ".opus")) {
        OggDemuxCreationState creationState;
        creationState.watchVariable = 0;
        OggFileServerDemux::createNew(
            env, fileName, onOggDemuxCreation, &creationState);
        env.taskScheduler().doEventLoop(&creationState.watchVariable);

        ServerMediaSubsession* smss;
        while ((smss = creationState.demux->newServerMediaSubsession())
               != nullptr) {
            sms->addSubsession(smss);
        }
    }

    return sms;
}
}

namespace rrdemo {
namespace cdom {
namespace live555 {

RTSPServer*RTSPServer::createNew(UsageEnvironment& env,
                                 Port ourPort,
                                 UserAuthenticationDatabase* authDatabase,
                                 unsigned reclamationTestSeconds) {
    auto ourSocket = setUpOurSocket(env, ourPort);
    if (ourSocket == -1) return nullptr;

    return new RTSPServer(env, ourSocket, ourPort, authDatabase, reclamationTestSeconds);
}

RTSPServer::RTSPServer(
    UsageEnvironment& env, int ourSocket, Port ourPort,
    UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds)
    : RTSPServerSupportingHTTPStreaming(
    env, ourSocket, ourPort, authDatabase, reclamationTestSeconds) {}

RTSPServer::~RTSPServer() {}

ServerMediaSession* RTSPServer::lookupServerMediaSession(
    char const* streamName, Boolean isFirstLookupInSession) {
    auto fid = fopen(streamName, "rb");
    auto fileExists = static_cast<bool>(fid);

    auto sms = ::RTSPServer::lookupServerMediaSession(streamName);
    auto smsExists = static_cast<bool>(sms);

    if (!fileExists) {
        if (smsExists) {
            removeServerMediaSession(sms);
            sms = nullptr;
        }

        return nullptr;

    } else {

        if (smsExists && isFirstLookupInSession) {
            removeServerMediaSession(sms);
            sms = nullptr;
        }

        if (!sms) {
            sms = createNewSMS(envir(), streamName, fid);
            addServerMediaSession(sms);
        }

        fclose(fid);
        return sms;
    }
}

}// namespace live555
}// namespace cdom
}// namespace rrdemo
