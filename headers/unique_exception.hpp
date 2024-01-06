#ifndef SPUTIFY_UNIQUE_EXCEPTION_HPP
#define SPUTIFY_UNIQUE_EXCEPTION_HPP

#include <stdexcept>

using namespace std;

class UniqueException : public std::exception {
private:
    std::string msg;

public:
    explicit UniqueException(std::string message);
    const char* what() const noexcept override;
};

#endif // SPUTIFY_UNIQUE_EXCEPTION_HPP
