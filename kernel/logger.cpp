#include "logger.hpp"

#include <cstddef>
#include <cstdio>

#include "console.hpp"

namespace {
LogLevel log_level = kWarn;
}  // namespace

extern Console* console;

void SetLogLevel(enum LogLevel level) { log_level = level; }

int Log(enum LogLevel level, const char* format, ...) {
    if (level > log_level) {
        return 0;
    }

    va_list ap;
    va_start(ap, format);
    char s[1024];
    int result = vsprintf(s, format, ap);
    va_end(ap);

    console->PutString(s);
    return result;
}