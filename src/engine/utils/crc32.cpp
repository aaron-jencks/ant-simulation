#include <cstddef>
#include <cstdint>
#include <span>

namespace engine::utils {
    static bool CRC32_TABLE_INIT = false;
    static std::uint32_t CRC32_LOOKUP[256];

    static void init_crc32() {
        CRC32_LOOKUP[0] = 0;
        std::uint32_t crc32 = 1;
        for(std::size_t i = 128; i; i >>= 1) {
            crc32 = (crc32 >> 1) ^ (crc32 & 1 ? 0xedb88320 : 0);
            for(std::size_t j = 0; j < 256; j += 2 * i) {
                CRC32_LOOKUP[i + j] = crc32 ^ CRC32_LOOKUP[j];
            }
        }
        CRC32_TABLE_INIT = true;
    }

    std::uint32_t compute_crc32(std::span<std::uint8_t> data) {
        std::uint32_t crc32 = 0xffffffff;
        if(!CRC32_TABLE_INIT) init_crc32();
        for(std::size_t i = 0; i < data.size(); i++) {
            crc32 ^= data[i];
            crc32 = (crc32 >> 8) ^ CRC32_LOOKUP[crc32 & 0xff];
        }
        crc32 ^= 0xffffffff;
        return crc32;
    }
}