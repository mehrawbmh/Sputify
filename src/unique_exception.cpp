#include "../headers/unique_exception.hpp"

UniqueException::UniqueException(const std::string& message) : msg(message) {}

const char* UniqueException::what() const noexcept {
    return msg.c_str();
}
