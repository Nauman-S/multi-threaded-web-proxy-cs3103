#pragma once

#include <string>

#include "Error.h"

class SemanticError
	: public Error
{
private:
	std::string message;
public:
	class SemanticError
	(std::string message);
	std::string what() const throw () override;
};

