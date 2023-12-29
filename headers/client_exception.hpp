#ifndef SPUTIFY_CLIENT_EXCEPTION_HPP
#define SPUTIFY_CLIENT_EXCEPTION_HPP

#include <stdexcept>

using namespace std;

class ClientException: public exception {
public:
    ClientException(int statusCode, string message = "");

    const char * what() const throw ();

    int getCode();

private:
    int status;
    string extraMessage;
};

#endif
