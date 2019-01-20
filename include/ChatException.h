#pragma once

#include <string>

using namespace std;

//	class ChatException is a special exception class
class ChatException {

private:

	const string errDescription;

	ChatException() = delete;

public:

	//	ChatException::ChatException(const string &_errDescription, const string &_whereFunc) creates throwing object with
	//	a description of the exception reason in _errDescription and the name of the method which has throwed the exception
	ChatException(const string &_errDescription, const string &_whereFunc) :
		errDescription("\nError in " + _whereFunc + "\n" + _errDescription + "\n\n")
	{

	}

	//	const string &ChatException::what() const returns string containing the information about the exception reason
	const string &what() const
	{
		return errDescription;
	}

};

ostream &operator<<(ostream &os, const ChatException &_exception);
