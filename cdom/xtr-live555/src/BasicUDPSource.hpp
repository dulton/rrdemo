/** \file
 *  \author zhengrr
 *  \date 2016-12-30
 *  \copyright The MIT License
 */
#ifndef _RRDEMOCDOMLIVE555_BASICUDPSOURCE_HPP
#define _RRDEMOCDOMLIVE555_BASICUDPSOURCE_HPP

#include <cassert>

#include <mutex>
#include <queue>

#include <live555/FramedSource.hh>
#include <live555/Groupsock.hh>

namespace rrdemo {
namespace cdom {
namespace live555 {

class BasicUDPSource : public FramedSource {
public:
    /// 创建新的 BasicUDPSource 实例。
    /** \param env
     *  \param skt  收流套接字。
     */
    static BasicUDPSource *createNew(UsageEnvironment &env, Groupsock *skt)
    {
        return new BasicUDPSource(env, skt);
    }

protected:
    /// 构造函数。
    explicit BasicUDPSource(UsageEnvironment &env, Groupsock *skt);

    /// 析构函数。
    ~BasicUDPSource();

private:
    /// 重写的 doGetNextFrame 函数。
    void doGetNextFrame() override;

protected:
    Groupsock *skt;  //< 收流地址。

public:
    /// 于 LIVE555 事件循环前，手动初始化源。
    /** 受 LIVE555 机制影响，于回调函数中创建的 WinSock 无法接收到数据，原因尚不明；
     *  因而临时提供此函数，用以在事件循环之前手动初始化源。
     *  \param env  用户环境。
     *  \param port 绑定端口，主机序。
     */
    static void initializeSourceBeforeEventLoop(UsageEnvironment *env, u_int16_t port);

    /// 缓存嵌套类。
    class Buf {
    public:
        /// 判断缓存是否为空。
        inline bool empty() const;
        /// 获取缓存长度。
        inline size_t len() const;
        /// 从……复制数据来（CoPY From）。
        /** \param src 数据来源。
         *  \param len 数据长度。
         *  \return 丢弃数据的字节数，0 表示正常。 */
        inline size_t cpyf(const uint8_t * const src, const size_t len);
        /// 将数据复制到……（CoPY To）
        /** \param dst 数据目的。
         *  \param siz 数据目的尺寸。
         *  \param len 数据长度。
         *  \return 丢弃数据的字节数，0 表示正常。 */
        inline size_t cpyt(uint8_t * const dst, const size_t siz, const size_t len) const;
        /// 从……追加数据来（APPend From）。
        /** 参照 cpyf。 */
        inline size_t appf(const uint8_t * const src, const size_t len);
        /// 将数据剪切到……（CUT To）
        /** 参照 cpyt。 */
        inline size_t cutt(uint8_t * const dst, const size_t siz, const size_t len);
        /// 清空缓存。
        inline void clear();
    private:
        static const size_t size {500000};  //< 尺寸（内存）。百兆网25FPS最大尺寸。
        uint8_t data[size] {};              //< 数据。
        size_t cur {};                      //< 游标。
        size_t len_ {};                     //< 长度（数据）。
    } *curb {};  //< 当前处理缓存。

    /// 缓存池嵌套类。
    class Bufs {
    public:
        /// 构造函数。
        inline explicit Bufs();
        /// 获取负载缓存队列长度。
        inline size_t datalen() const;
        /// 获取闲置缓存队列长度。
        inline size_t idlelen() const;
        /// 压入负载缓存。
        inline void push(Buf * const buf);
        /// 弹出负载缓存。
        inline Buf *pop();
        /// 回收闲置缓存。
        inline void recycle(Buf * const buf);
        /// 分配闲置缓存。
        inline Buf *allocate();
        /// 强制分配缓存。
        /** 若闲置缓存已空，则尝试释放负载缓存并将其分配。 */
        inline Buf *allocateforce();
    private:
        Buf entities[3];            //< 缓存实体。
        std::queue<Buf *> dataque;  //< 负载缓存队列。
        std::queue<Buf *> idleque;  //< 闲置缓存队列。
        std::mutex mtx;             //< 缓存队列锁。
    } bufs;  //< 缓存队列。

    /// 用户数据报协议包回调处理函数。
    /** param PCKS 尺寸（内存）。
     *  param pck  数据。
     *  param pckl 长度。
     */
    virtual void newpck(const size_t PCKS, const uint8_t * const pck, const size_t pckl);

};// H264VideoUdpSource

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#include "BasicUDPSourceBuf.inl"
#include "BasicUDPSourceBufs.inl"

#endif// _RRDEMOCDOMLIVE555_BASICUDPSOURCE_HPP
