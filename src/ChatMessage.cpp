#include "../include/ChatMessage.h"

std::ostream &operator<<(std::ostream &os, const ChatMessage &_message)
{
	os << _message.getTime() << "; " << _message.whoseMessage() << ": " << _message.getText();
	return os;
}
