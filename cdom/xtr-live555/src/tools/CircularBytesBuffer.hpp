/** \file
 *  \author zhengrr
 *  \date 2017-1-6 – 7
 *  \copyright The MIT License
 */
#ifndef RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__HPP
#define RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__HPP

#include <cstdint>

namespace rrdemo {
namespace cdom {
namespace live555 {

/// 循环字节缓冲。
class CircularBytesBuffer final {
    explicit CircularBytesBuffer() = delete;
    explicit CircularBytesBuffer(const CircularBytesBuffer &) = delete;
    explicit CircularBytesBuffer(CircularBytesBuffer &&) = delete;
    CircularBytesBuffer &operator=(const CircularBytesBuffer &) = delete;
    CircularBytesBuffer &operator=(CircularBytesBuffer &&) = delete;

public:
    /// 构造函数。
    inline explicit CircularBytesBuffer(size_t bufferSize = 500000);

    /// 析构函数。
    inline ~CircularBytesBuffer();

    /// 获取负载缓存量。
    inline size_t getLoadLength() const;

    /// 获取闲置缓存量。
    inline size_t getIdleLength() const;

    /// 从…增加数据。
    /** 若欲增加的数据过多，超过闲置缓存，则会将多余的数据丢弃。
     *  \param source 来源地；
     *  \param length 欲增加的数据量。
     *  \return 丢弃的数据量。
     */
    inline size_t addDataFrom(const uint8_t * const source, const size_t length);

    /// 复制数据到…。
    /** 若欲复制的数据过多，超过目的地可用尺寸的限制，则多余的数据将不会复制。
     *  \param destination 目的地；
     *  \param size        目的地可用尺寸限制；
     *  \param length      欲复制的数据量。
     *  \return 多余的数据量。
     *  \pre 欲复制的数据量应小于或等于负载缓存量。
     */
    inline size_t copyDataInto(uint8_t * const destination, const size_t size, const size_t length) const;

    /// 丢弃数据。
    /** 若欲丢弃的数据过多，超过负载缓存，则丢弃全部数据。
     *  \param length 欲丢弃的数据量。
     *  \return 超出负载缓存的欲丢弃数据量。
     */
    inline size_t discardData(const size_t length);

    /// 剪切数据到…。
    /** 若欲剪切的数据过多，超过目的地可用尺寸的限制，则会将多余的数据丢弃。
     *  \param destination 目的地；
     *  \param size        目的地可用尺寸限制；
     *  \param length      欲剪切的数据量。
     *  \return 丢弃的数据量。
     *  \pre 欲剪切的数据量应小于或等于负载缓存量。
     */
    inline size_t cutDataInto(uint8_t * const destination, const size_t size, const size_t length);

    /// 清空数据。
    inline void clearData();

private:
    /*
     * HAVE NOT INVERTED POINT    HAVE THE INVERTED POINT
     *    start      end                  end  start
     *      v > > > o v              > > o v     v >
     * |?|_|B|B|B|B|B|_|_|?|?|    |?|B|B|B|_|_|_|B|B|?|?|
     *    ^               ^          ^               ^
     *    0 <-- SIZE --> MAX         0 <-- SIZE --> MAX
     */

    /// 检查负载缓存受否包含“颠倒点”。
    inline bool haveInvertedPoint() const;

    /// 起点偏移量（内存连续地）前移，负载量减小。
    /** 前移不可穿透“颠倒点”，若恰好停留在之上，则置偏移量为 0。
     *  \pre 前移量应小于或等于负载缓存量；
     *  \pre 前移量不可穿透“颠倒点”。
     */
    inline void startPositionDash(const size_t length);

    /// 终点偏移量（内存连续地）前移，负载量增大。
    /** 前移不可穿透“颠倒点”，若恰好停留在之上，则置偏移量为 0。
     *  \pre 前移量应小于或等于闲置缓存量；
     *  \pre 前移量不可穿透“颠倒点”。
     */
    inline void endPositionDash(const size_t length);

    const size_t SIZE;         //< 缓存尺寸；
    uint8_t *data {};          //< 缓存数据；
    size_t length {};          //< 负载量；
    size_t start_position {};  //< 起点偏移量；
    size_t end_position {};    //< 终点偏移量。

};

}// namespace live555
}// namespace cdom
}// namespace rrdemo

#include "CircularBytesBuffer.inl"

#endif// RRDEMO__CDOM__LIVE555__CIRCULAR_BYTES_BUFFER__HPP
