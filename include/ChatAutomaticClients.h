#pragma once

#include <string>
#include <vector>
#include "ChatServer.h"
#include "ChatThreadObj.h"
#include "ChatTime.h"
#include "ChatAutomaticClient.h"

//	class ChatAutomaticClients manages the clients, that automatically send messages
class ChatAutomaticClients :public std::vector<ChatAutomaticClient *>
{

public:

	ChatAutomaticClients(unsigned int _nClients, const int *_timeGaps, const std::string *_messageTexts, ChatServer &_chatServer);

	//	void ChatAutomaticClient::startAutomaticSending() starts automatic message sending
	void startAutomaticSending();

	//	void ChatAutomaticClient::joinThread() joins threads
	void joinThreads();

	~ChatAutomaticClients();

};
