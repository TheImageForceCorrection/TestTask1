#pragma once

#include <string>

using namespace std;

//	class ChatMessage incapsulates message and information about it
class ChatMessage {

private:

	const string text;
	const string time;
	int nClient;

	ChatMessage() = delete;

	ChatMessage(ChatMessage &) = delete;

public:

	ChatMessage(const string &_text, const string &_time, int _nClient) :text(_text), time(_time), nClient(_nClient)
	{

	}

	const int whoseMessage() const
	{
		return nClient;
	}

	const string &getTime() const
	{
		return time;
	}

	const string &getText() const
	{
		return text;
	}

};

ostream &operator<<(ostream &os, const ChatMessage &_message);
