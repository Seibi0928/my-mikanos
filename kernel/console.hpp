#pragma once

#include "graphics.hpp"

class Console {
   public:
    static const int kRows = 25, kColumns = 80;

    Console(PixelWriter& writer, const PixcelColor& fg_color,
            const PixcelColor& bg_color);
    void PutString(const char* s);

   private:
    void NewLine();

    PixelWriter& writer_;
    const PixcelColor fg_color_, bg_color_;
    char buffer_[kRows][kColumns + 1];
    int cursor_row_, cursor_column_;
};
