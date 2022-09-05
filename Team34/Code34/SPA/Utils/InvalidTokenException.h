#pragma once

#include"..\QPS\parser\SyntaxError.h"
class InvalidTokenException : public SyntaxError
{
private:
	char unidentifiable_character;
public:
	InvalidTokenException(char unidentifiable_character);
	const char* what() const throw ();
};

