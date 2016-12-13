/** \file
 *  \author zhengrr
 *  \date 2016-12-9 – 13
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include <live555/liveMedia.hh>

namespace {

const char const *INPUT_FILE_NAME {"in.264"};
const char const *OUTPUT_FILE_NAME {"out.ts"};

UsageEnvironment *env {nullptr};

/// 将 H.264 基本流（Elementary Stream）转换为传输流（Transport Stream）。
int Main(int, char *[])
{
    /* 创建任务调度器与使用环境 */
    TaskScheduler *schr {BasicTaskScheduler::createNew()};
    env = BasicUsageEnvironment::createNew(*schr);

    /* 创建源 */
    FramedSource *src;                           // 源
    if (!((src = ByteStreamFileSource::createNew(*env, INPUT_FILE_NAME)))) {
        *env << "Unable to open file \"" << INPUT_FILE_NAME << "\" as a byte-stream file source.\n";
        return EXIT_FAILURE;
    }
    H264VideoStreamFramer *framer {              // 成帧器
        H264VideoStreamFramer::createNew(*env, src, True)};
    MPEG2TransportStreamFromESSource *mplexor {  // 多路复用器
        MPEG2TransportStreamFromESSource::createNew(*env)};
    mplexor->addNewVideoSource(framer, 5/*H.264*/);

    /* 创建接收器 */
    MediaSink *sink;
    if (!((sink = FileSink::createNew(*env, OUTPUT_FILE_NAME)))) {
        *env << "Unable to open file \"" << OUTPUT_FILE_NAME << "\" as a file sink.\n";
        return EXIT_FAILURE;
    }

    /* 执行转换 */
    *env << "Beginning to read..." << "\n";
    sink->startPlaying(*mplexor, [](void *) {
        *env << "Done reading.\n";
        *env << "Wrote output file: \"" << OUTPUT_FILE_NAME << "\"\n";
        exit(EXIT_SUCCESS);
    }, nullptr);

    env->taskScheduler().doEventLoop();// noreturn
    return EXIT_SUCCESS;
}

}// namespace

#ifndef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
