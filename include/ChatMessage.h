#pragma once

#include <string>

//	class ChatMessage incapsulates message and information about it
class ChatMessage {

private:

	const std::string text;
	const std::string time;
	int nClient;

	ChatMessage() = delete;

	ChatMessage(ChatMessage &) = delete;

public:

	ChatMessage(const std::string &_text, const std::string &_time, int _nClient) :text(_text), time(_time), nClient(_nClient)
	{

	}

	const int whoseMessage() const
	{
		return nClient;
	}

	const std::string &getTime() const
	{
		return time;
	}

	const std::string &getText() const
	{
		return text;
	}

};

std::ostream &operator<<(std::ostream &os, const ChatMessage &_message);
