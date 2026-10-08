#ifndef IMAGE_H
#define IMAGE_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace engine {
    class Image {
    public:
        const std::size_t width;
        const std::size_t height;

        Image(std::size_t width, std::size_t height);
        virtual ~Image() = default;

        std::span<std::uint8_t> pixels() {
            return pixels_;
        }

        std::span<const std::uint8_t> pixels() const {
            return pixels_;
        }

    private:
        std::vector<std::uint8_t> pixels_;
    };
}

#endif
