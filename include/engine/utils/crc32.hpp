#ifndef CRC32_H
#define CRC32_H

#include <cstdint>
#include <span>

namespace engine::utils {
    /**
     * @brief Computes the CRC-32 hash for a given set of data
     *
     * @param data The data to computer the CRC for
     * @return The CRC-32 for the given data
     */
    std::uint32_t compute_crc32(std::span<std::uint8_t> data);
}

#endif