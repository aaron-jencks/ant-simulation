#include <engine/images/parsing/png.hpp>

#include <cstdint>
#include <vector>

#include <engine/utils/crc32.hpp>

namespace engine::images::parsing {
    bool check_file_header(BitStream& stream) {
        if(stream.length() < 64) return false;

        auto magic_data = std::vector<std::uint8_t>({
            0x89,               // First byte is always 0x89
            0x50, 0x4e, 0x47,   // ASCII characters "PNG"
            0x0d, 0x0a,         // DOS-style line ending
            0x1a,               // Something to stop the printing in DOS
            0x0a                // UNIX-style line ending
        });

        for(auto byte : magic_data) {
            if(stream.readByte() != byte) return false;
        }

        return true;
    }

    PNGChunk read_file_chunk(BitStream& stream) {
        std::uint32_t data_len = stream.readLong();
        std::uint32_t data_type = stream.readLong();
        auto data_buff = std::vector<std::uint8_t>(data_len);
        for(std::size_t i = 0; i < data_len; i++) {
            data_buff[i] = stream.readByte();
        }
        std::uint32_t crc = stream.readLong();
        return PNGChunk(
            data_len, data_type, crc,
            std::move(data_buff)
        );
    }

    bool PNGChunk::verify_crc() {
        if(data.size() != length) return false;
        auto type_arr = std::vector<std::uint8_t>({
            static_cast<std::uint8_t>(type >> 24),
            static_cast<std::uint8_t>(type >> 16),
            static_cast<std::uint8_t>(type >> 8),
            static_cast<std::uint8_t>(type)
        });
        std::uint32_t computed_crc = engine::utils::update_crc32(type_arr);
        computed_crc = engine::utils::compute_crc32(data, computed_crc);
        return computed_crc == crc;
    }
}