#pragma once

#include <string>

class Error {
public:
    virtual std::string what() const throw () = 0;
};