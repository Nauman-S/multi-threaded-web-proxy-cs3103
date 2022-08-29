#pragma once
#ifndef INVALIDTOKENEXCEPTION_H
#define INVALIDTOKENEXCEPTION_H
class InvalidTokenException
{
private:
	char unidentifiable_character;
public:
	InvalidTokenException(char unidentifiable_character);
	const char* what() const throw ();
};
#endif

