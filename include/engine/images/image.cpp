#include <engine/images/image.hpp>

namespace engine {
    Image::Image(std::size_t width, std::size_t height) : width(width), height(height) {
        pixels_ = std::vector<std::uint8_t>(width * height * 4);
    }
}
