#include <engine/images/parsing/bitstream.hpp>

namespace engine::images::parsing {
    void Bitstream::reset() {
        bytePos_ = 0;
        bitPos_ = 0;
    }

    std::uint32_t BitStream::readBits(std::size_t count) {
        if(count > 32 ) throw std::invalid_argument("Too many bits");
        std::uint32_t result = 0;
        for(std:size_t i = 0; i < count; i++) {
            if(bytePos_ >= data_.size()) throw std::runtime_error("Unexpected EOF");
            std::uint8_t bit = (data_[bytePos_] >> bitPos_) & 1;
            result |= static_cast<std::uint32_t>(bit) << i;
            if(++bitPos_ == 8) {
                bitPos_ = 0;
                bytePos_++;
            }
        }
        return result;
    }

    void BitStream::alignToBytes() {
        if(bitPos_ != 0) {
            bitPos_ = 0;
            bytePost_++;
        }
    }
}
