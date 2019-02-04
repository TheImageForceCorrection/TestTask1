#include "../include/ChatException.h"

std::ostream &operator<<(std::ostream &os, const ChatException &_exception)
{
	os << _exception.what();
	return os;
}
