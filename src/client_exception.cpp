#include "../headers/client_exception.hpp"
#include <iostream>

ClientException::ClientException(int statusCode, string message): status(statusCode), extraMessage(message) {
    errMessage = to_string(this->status) + " Http Error: " + this->extraMessage + "\n";
}

const char* ClientException::what() const noexcept {
    return errMessage.c_str();
}

int ClientException::getCode() const {
    return status;
}
