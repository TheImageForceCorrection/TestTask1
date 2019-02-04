#pragma once

#include <string>

//	class ChatException is a special exception class
class ChatException {

private:

	const std::string errDescription;

	ChatException() = delete;

public:

	//	ChatException::ChatException(const string &_errDescription, const string &_whereFunc) creates throwing object with
	//	a description of the exception reason in _errDescription and the name of the method which has throwed the exception
	ChatException(const std::string &_errDescription, const std::string &_whereFunc) :
		errDescription("\nError in " + _whereFunc + "\n" + _errDescription + "\n\n")
	{

	}

	//	const string &ChatException::what() const returns string containing the information about the exception reason
	const std::string &what() const
	{
		return errDescription;
	}

};

std::ostream &operator<<(std::ostream &os, const ChatException &_exception);
