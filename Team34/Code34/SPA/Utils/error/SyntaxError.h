#pragma once

#include <string>

#include "Error.h"

class SyntaxError
    : public Error {
private:
    std::string message;
public:
    SyntaxError() {}
    explicit SyntaxError(std::string message);
    std::string what() const throw () override;
};