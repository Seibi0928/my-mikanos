#pragma once

#include "frame_buffer_config.hpp"

struct PixcelColor {
    uint8_t r, g, b;
};

class PixelWriter {
   public:
    PixelWriter(const FrameBufferConfig& config) : config_{config} {}
    virtual ~PixelWriter() = default;
    virtual void Write(int x, int y, const PixcelColor& c) = 0;

   protected:
    uint8_t* PixelAt(int x, int y) {
        return config_.frame_buffer + 4 * (config_.pixel_per_scan_line * y + x);
    }

   private:
    const FrameBufferConfig& config_;
};

class RGBResv8BitPerColorPixelWriter : public PixelWriter {
   public:
    using PixelWriter::PixelWriter;
    virtual void Write(int x, int y, const PixcelColor& c) override;
};

class BGRResv8BitPerColorPixelWriter : public PixelWriter {
   public:
    using PixelWriter::PixelWriter;
    virtual void Write(int x, int y, const PixcelColor& c) override;
};

template <typename T>
struct Vector2D {
    T x, y;
};

void DrawRectangle(PixelWriter& writer, const Vector2D<int>& pos,
                   const Vector2D<int>& sizes, const PixcelColor& c);

void FillRectangle(PixelWriter& writer, const Vector2D<int>& pos,
                   const Vector2D<int>& size, const PixcelColor& c);