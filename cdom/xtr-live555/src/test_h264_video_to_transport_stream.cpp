/** \file
 *  \author zhengrr
 *  \date 2016-12-9
 *  \copyright The MIT License
 */
#include <live555/liveMedia.hh>
#include <live555/BasicUsageEnvironment.hh>

char const* inputFileName = "in.264";
char const* outputFileName = "out.ts";

namespace {

UsageEnvironment* env {nullptr};

void afterPlaying(void* /*clientData*/)
{
    *env << "Done reading.\n";
    *env << "Wrote output file: \"" << outputFileName << "\"\n";
    exit(EXIT_SUCCESS);
}

int altmain(int, char *[])
{
    // 创建调度器与环境
    TaskScheduler *scheduler {BasicTaskScheduler::createNew()};
    env = BasicUsageEnvironment::createNew(*scheduler);

    // 打开输入源文件
    FramedSource *inputSource;
    if (!((inputSource = ByteStreamFileSource::createNew(*env, inputFileName)))) {
        *env << "Unable to open file \"" << inputFileName << "\" as a byte-stream file source.\n";
        return EXIT_FAILURE;
    }
    H264VideoStreamFramer* framer {
        H264VideoStreamFramer::createNew(*env, inputSource, True)};
    MPEG2TransportStreamFromESSource* tsFrames {
        MPEG2TransportStreamFromESSource::createNew(*env)};
    tsFrames->addNewVideoSource(framer, 5/*H.264*/);

    // 打开输出槽文件
    MediaSink *outputSink;
    if (!((outputSink = FileSink::createNew(*env, outputFileName)))) {
        *env << "Unable to open file \"" << outputFileName << "\" as a file sink.\n";
        return EXIT_FAILURE;
    }

    // 转换
    *env << "Beginning to read...\n";
    outputSink->startPlaying(*tsFrames, afterPlaying, nullptr);

    env->taskScheduler().doEventLoop();// noreturn

    return EXIT_SUCCESS;
}

}// namespace

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return altmain(argc, argv); }
#endif// ENTRY SWITCH
