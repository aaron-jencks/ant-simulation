#include <engine/images/parsing/bitstream.hpp>

#include <bit>
#include <stdexcept>


namespace engine::images::parsing {
    void BitStream::reset() {
        bytePos_ = 0;
        bitPos_ = 0;
    }

    std::uint32_t BitStream::readBits(std::size_t count) {
        if(count > 32 ) throw std::invalid_argument("Too many bits");
        std::uint32_t result = 0;
        for(std::size_t i = 0; i < count; i++) {
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

    std::uint8_t BitStream::readByte() {
        return static_cast<std::uint8_t>(readBits(8));
    }

    std::uint32_t BitStream::readLong() {
        auto be_data = readBits(32);
        return std::byteswap(be_data);
    }

    void BitStream::alignToBytes() {
        if(bitPos_ != 0) {
            bitPos_ = 0;
            bytePos_++;
        }
    }

    std::size_t BitStream::length() {
        std::size_t current_position = bytePos_ * 8 + bitPos_;
        std::size_t total_bit_count = data_.size() * 8;
        return total_bit_count - current_position;
    }
}
