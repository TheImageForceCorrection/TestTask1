#include "../include/ChatException.h"


ostream &operator<<(ostream &os, const ChatException &_exception)
{
	os << _exception.what();
	return os;
}
