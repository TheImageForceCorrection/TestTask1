#include "../include/ChatAutomaticClients.h"

ChatAutomaticClients::ChatAutomaticClients(unsigned int _nClients, const int *_timeGaps, const string *_messageTexts, ChatServer &_chatServer)
{
	for (unsigned int i = 0; i < _nClients; i++)
	{
		push_back(new ChatAutomaticClient(i, _timeGaps[i], _messageTexts[i], _chatServer));
	}
}

void ChatAutomaticClients::startAutomaticSending()
{
	for (unsigned int i = 0; i < size(); i++)
		operator[](i)->startAutomaticSending();
}

void ChatAutomaticClients::joinThreads()
{
	for (unsigned int i = 0; i < size(); i++)
		operator[](i)->joinThread();
}

ChatAutomaticClients::~ChatAutomaticClients()
{
	for (unsigned int i = 0; i < size(); i++)
		delete operator[](i);
}
