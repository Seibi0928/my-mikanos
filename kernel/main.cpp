#include <cstddef>
#include <cstdint>

#include "frame_buffer_config.hpp"

struct PixcelColor {
    uint8_t r, g, b;
};

/// @brief WritePixelは1つの点を描画する
/// @return 0   成功
/// @return 非0 失敗
int WritePixel(const FrameBufferConfig& config, int x, int y,
               const PixcelColor& c) {
    const int pixel_position = config.pixel_per_scan_line * y + x;
    uint8_t* p = &config.frame_buffer[4 * pixel_position];
    if (config.pixel_format == kPixelRBGResv8BitPerColor) {
        p[0] = c.r;
        p[1] = c.g;
        p[2] = c.b;
        return 0;
    } else if (config.pixel_format == kPixelBGRResv8BitPerColor) {
        p[0] = c.b;
        p[1] = c.g;
        p[2] = c.r;
        return 0;
    }
    return -1;
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
    for (int x = 0; x < frame_buffer_config.horizontal_resolution; ++x) {
        for (int y = 0; y < frame_buffer_config.vertical_resolution; ++y) {
            WritePixel(frame_buffer_config, x, y, {255, 255, 255});
        }
    }
    for (int x = 0; x < 200; ++x) {
        for (int y = 0; y < 100; ++y) {
            WritePixel(frame_buffer_config, 100 + x, 100 + y, {0, 255, 0});
        }
    }
    while (1) __asm__("hlt");
}
