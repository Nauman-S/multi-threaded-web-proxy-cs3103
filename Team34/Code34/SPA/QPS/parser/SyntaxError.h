#pragma once
#include <string>

class SyntaxError
{
private:
	std::string message;
public:
	SyntaxError() {}
	explicit SyntaxError(std::string message);
	std::string what() const throw ();
};