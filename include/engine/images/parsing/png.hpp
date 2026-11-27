#ifndef PNG_H
#define PNG_H

#include <cstdint>
#include <vector>

#include <engine/images/parsing/bitstream.hpp>

namespace engine::images::parsing {
    struct PNGChunk {
        std::uint32_t length;
        std::uint32_t type;
        std::uint32_t crc;
        std::vector<std::uint8_t> data;

        bool verify_crc();
    };

    /**
     * @brief Checks if the given bitstream contains the correct first bytes
     *
     * @param stream The data to check
     * @return True if the bitstream starts with the required png bytes, false otherwise
     */
    bool check_file_header(BitStream& stream);

    /**
     * @brief Reads a raw PNG data chunk from the bitstream
     *
     * @param stream The data to read from
     * @return A PNGChunk with the found data, raises an exception if a chunk cannot be found
     */
    PNGChunk read_file_chunk(BitStream& stream);
}

#endif