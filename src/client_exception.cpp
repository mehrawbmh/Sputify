#include "../headers/client_exception.hpp"
#include <iostream>

ClientException::ClientException(int statusCode, string message): status(statusCode), extraMessage(message) {}

const char* ClientException::what() const noexcept {
    string output = to_string(this->status) + "Error: " + this->extraMessage;
    // cout << output << endl;
    return "";
}

int ClientException::getCode() {
    return status;
}
