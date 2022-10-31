#include "InvalidTokenException.h"

#include "SyntaxError.h"

InvalidTokenException::InvalidTokenException(std::string invalid_token) : SyntaxError(invalid_token) {
    this->invalid_token_ = invalid_token;
}

std::string InvalidTokenException::what() const throw () {
    return "Invalid token encountered : " + this->invalid_token_;
}