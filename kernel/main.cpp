#include <cstddef>
#include <cstdint>
#include <cstdio>

#include "console.hpp"
#include "font.hpp"
#include "frame_buffer_config.hpp"
#include "graphics.hpp"

void* operator new(size_t size, void* buf) { return buf; }

void operator delete(void* obj) noexcept {}

char console_buf[sizeof(Console)];
Console* console;

int printk(const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    char s[1024];
    int result = vsprintf(s, format, ap);
    va_end(ap);

    console->PutString(s);
    return result;
}

extern "C" void KernelMain(const FrameBufferConfig& frame_buffer_config) {
    char pixel_writer_buf[sizeof(RGBResv8BitPerColorPixelWriter)];
    PixelWriter* pixel_writer;
    switch (frame_buffer_config.pixel_format) {
        case kPixelRBGResv8BitPerColor:
            pixel_writer = new (pixel_writer_buf)
                RGBResv8BitPerColorPixelWriter{frame_buffer_config};
        case kPixelBGRResv8BitPerColor:
            pixel_writer = new (pixel_writer_buf)
                BGRResv8BitPerColorPixelWriter{frame_buffer_config};
        default:
            break;
    }

    console =
        new (console_buf) Console{*pixel_writer, {0, 0, 0}, {255, 255, 255}};

    char buf[128];
    for (int i = 0; i < 100; ++i) {
        sprintf(buf, "line %d\n", i);
        console->PutString(buf);
    }
    while (1) __asm__("hlt");
}
