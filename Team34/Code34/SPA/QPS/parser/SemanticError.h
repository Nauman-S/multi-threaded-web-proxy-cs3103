#pragma once

#include <string>

class SemanticError
{
private:
	std::string message;
public:
	class SemanticError
	(std::string message);
	std::string what() const throw ();
};

