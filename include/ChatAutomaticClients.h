#pragma once

#include <string>
#include <vector>
#include "ChatServer.h"
#include "ChatThreadObj.h"
#include "ChatTime.h"
#include "ChatAutomaticClient.h"

using namespace std;

//	class ChatAutomaticClients manages the clients, that automatically send messages
class ChatAutomaticClients :public vector<ChatAutomaticClient *>
{

public:

	ChatAutomaticClients(unsigned int _nClients, const int *_timeGaps, const string *_messageTexts, ChatServer &_chatServer);

	//	void ChatAutomaticClient::startAutomaticSending() starts automatic message sending
	void startAutomaticSending();

	//	void ChatAutomaticClient::joinThread() joins threads
	void joinThreads();

	~ChatAutomaticClients();

};
