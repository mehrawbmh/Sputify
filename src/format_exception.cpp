#include "../headers/format_exception.hpp"

FormatException::FormatException(string message) : msg(message) {}

const char* FormatException::what() const noexcept {
    return msg.c_str();
}
