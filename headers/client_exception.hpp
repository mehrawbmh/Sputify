#ifndef SPUTIFY_CLIENT_EXCEPTION_HPP
#define SPUTIFY_CLIENT_EXCEPTION_HPP

#include <stdexcept>

using namespace std;

class ClientException: public exception {
private:
    int status;
    string extraMessage;
    string errMessage;

public:
    ClientException(int statusCode, string message = "");

    const char * what() const noexcept;

    int getCode() const;
};

#endif //SPUTIFY_FORMAT_EXCEPTION_HPP
