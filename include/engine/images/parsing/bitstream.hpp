#ifndef BITSTREAM_H
#define BITSTREAM_H

#include <cstddef>
#include <cstdint>
#include <span>

namespace engine::images::parsing {
    class BitStream {
    public:
        explicit BitStream(std::span<const std::uint8_t> data) : data_(data) {}

        std::uint32_t readBits(std::size_t count);
        void alignToBytes();
        void reset();

    private:
        std::span<const std::uint8_t> data_;
        std::size_t bytePos_ = 0;
        std::size_t bitPos_ = 0;
    }
}

#endif
