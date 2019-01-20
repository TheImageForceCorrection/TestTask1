#include "../include/ChatServer.h"

void ChatServer::getMessage(const string  &_messageText, const string &_timeStr, int _nClient)
{
	const ChatMessage *curMessage = new ChatMessage(_messageText, _timeStr, _nClient);
	mu.lock();
	messages.push(curMessage);
	mu.unlock();
}

void ChatServer::writeMessages()
{
	mu.lock();
	while (!messages.empty())
	{
		const ChatMessage *curMessage = messages.front();
		file.Write(*curMessage);
		delete curMessage;
		messages.pop();
	}
	mu.unlock();
}

void ChatServer::startChat()
{
	Working = true;
	startExecution();
}