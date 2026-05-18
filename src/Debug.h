// Debug.h - Debug logging utilities
#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <format>
#include <string_view>
#include <source_location>

// C++20 std::source_location - automatic file/line/function info
inline void debugLog(
    std::string_view message,
    const std::source_location location = std::source_location::current()
) {
    std::cout << std::format("[DEBUG] {}:{} in {}() - {}\n",
        location.file_name(),
        location.line(),
        location.function_name(),
        message
    );
}

// Variadic template version - accepts any number of arguments
template<typename... Args>
inline void debugLogf(
    const std::source_location location,
    std::string_view fmt,
    Args&&... args
) {
    std::string message = std::vformat(fmt, std::make_format_args(args...));
    std::cout << std::format("[DEBUG] {}:{} in {}() - {}\n",
        location.file_name(),
        location.line(),
        location.function_name(),
        message
    );
}

// Helper macros that capture source location
#define DEBUG_ALWAYS(msg) debugLog(msg)
#define DEBUG_ALWAYS_F(fmt, ...) debugLogf(std::source_location::current(), fmt, __VA_ARGS__)

// Conditional debug - only prints if DEBUG_ENABLED is defined
#ifdef DEBUG_ENABLED
    #define DEBUG_LOG(msg) debugLog(msg)
    #define DEBUG_LOGF(fmt, ...) debugLogf(std::source_location::current(), fmt, __VA_ARGS__)
#else
    #define DEBUG_LOG(msg) ((void)0)
    #define DEBUG_LOGF(fmt, ...) ((void)0)
#endif

#endif // DEBUG_H
