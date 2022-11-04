#pragma once

#include <string>

#include "SyntaxError.h"

class InvalidTokenException : public SyntaxError {
private:
    std::string invalid_token_;

public:
    explicit InvalidTokenException(std::string invalid_token);
    std::string what() const throw ();
};

