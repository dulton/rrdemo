/** \file
 *  \author zhengrr
 *  \date 2016-12-9 – 12
 *  \copyright The MIT License
 */
#include <live555/BasicUsageEnvironment.hh>
#include <live555/liveMedia.hh>

namespace {

const char const *INPUT_FILE_NAME {"in.264"};
const char const *OUTPUT_FILE_NAME {"out.ts"};

void AfterPlaying(void *);

UsageEnvironment *env {nullptr};

int Main(int, char *[])
{
    // 创建调度器与环境
    TaskScheduler *scheduler {BasicTaskScheduler::createNew()};
    env = BasicUsageEnvironment::createNew(*scheduler);

    // 打开输入源文件
    FramedSource *inputSource;
    if (!((inputSource = ByteStreamFileSource::createNew(*env, INPUT_FILE_NAME)))) {
        *env << "Unable to open file \"" << INPUT_FILE_NAME << "\" as a byte-stream file source.\n";
        return EXIT_FAILURE;
    }
    H264VideoStreamFramer* framer {
        H264VideoStreamFramer::createNew(*env, inputSource, True)};
    MPEG2TransportStreamFromESSource* tsFrames {
        MPEG2TransportStreamFromESSource::createNew(*env)};
    tsFrames->addNewVideoSource(framer, 5/*H.264*/);

    // 打开输出槽文件
    MediaSink *outputSink;
    if (!((outputSink = FileSink::createNew(*env, OUTPUT_FILE_NAME)))) {
        *env << "Unable to open file \"" << OUTPUT_FILE_NAME << "\" as a file sink.\n";
        return EXIT_FAILURE;
    }

    // 转换
    *env << "Beginning to read...\n";
    outputSink->startPlaying(*tsFrames, AfterPlaying, nullptr);

    env->taskScheduler().doEventLoop();// noreturn

    return EXIT_SUCCESS;
}

void AfterPlaying(void */*clientData*/)
{
    *env << "Done reading.\n";
    *env << "Wrote output file: \"" << OUTPUT_FILE_NAME << "\"\n";
    exit(EXIT_SUCCESS);
}

}// namespace

#ifdef ENTRY_SWITCH
int main(int argc, char *argv[]) { return Main(argc, argv); }
#endif// ENTRY SWITCH
