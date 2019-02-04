#include "../include/ChatFile.h"

ChatFile::ChatFile(const std::string &_filename) :filename(_filename)
{
	std::ofstream curFile(filename, std::ofstream::trunc);
	if (!curFile.is_open())
		throw (ChatException("Cannot open file", "ChatFile::ChatFile(const string &_filename)"));
	curFile.close();
}

void ChatFile::Write(const ChatMessage &_message)
{
	std::ofstream curFile(filename, std::ofstream::app);
	if (!curFile.is_open())
		throw (ChatException("Cannot open file", "void ChatFile::Write(const ChatMessage&_message)"));
	curFile << _message << "\n";
	curFile.close();
}
