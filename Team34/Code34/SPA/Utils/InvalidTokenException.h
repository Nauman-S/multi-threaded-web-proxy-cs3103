#pragma once

#include <string>

#include"..\QPS\parser\SyntaxError.h"

class InvalidTokenException : public SyntaxError
{
private:
    std::string invalid_token_;

public:
    InvalidTokenException(std::string invalid_token);
    std::string what() const throw ();
};

