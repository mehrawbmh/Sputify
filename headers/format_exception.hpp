#ifndef SPUTIFY_FORMAT_EXCEPTION_HPP
#define SPUTIFY_FORMAT_EXCEPTION_HPP

#include <stdexcept>

using namespace std;

class FormatException : public std::exception {
private:
    std::string msg;

public:
    FormatException(const std::string& message);
    const char* what() const noexcept;
};

#endif // SPUTIFY_FORMAT_EXCEPTION_HPP
