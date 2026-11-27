#ifndef CRC32_H
#define CRC32_H

#include <cstdint>
#include <span>

namespace engine::utils {
    /**
     * @brief Computes the internal crc-32 state of the given data without finalizing it.
     * Also allows the user to initialize the state from a given value.
     *
     * @param data The data to computer the crc for
     * @param state The initial state for tha algorith, defaults to 0xffffffffu
     * @return Returns the unfinalized crc-32 value
     */
    std::uint32_t update_crc32(std::span<std::uint8_t> data, std::uint32_t state = 0xffffffff);

    /**
     * @brief Computes the CRC-32 hash for a given set of data
     *
     * @param data The data to computer the CRC for
     * @param state The initial state of the CRC state, defaults to 0xffffffffu
     * @return The CRC-32 for the given data
     */
    std::uint32_t compute_crc32(std::span<std::uint8_t> data, std::uint32_t state = 0xffffffff);
}

#endif