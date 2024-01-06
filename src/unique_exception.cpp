#include <utility>

#include "../headers/unique_exception.hpp"

UniqueException::UniqueException(std::string  message) : msg(std::move(message)) {}

const char* UniqueException::what() const noexcept {
    return msg.c_str();
}
