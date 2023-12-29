#include "../headers/client_exception.hpp"

ClientException::ClientException(int statusCode): status(statusCode) {}

const char *ClientException::what() const throw()
{
    return "Error happened.\n";
}

int ClientException::getCode()
{
    return status;
}
