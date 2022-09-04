#include <string>

#ifndef SYNTAXERROR_H
#define SYNTAXERROR_H

class SyntaxError
{
private:
	std::string message;
public:
	SyntaxError(std::string message);
	std::string what() const throw ();
};

#endif