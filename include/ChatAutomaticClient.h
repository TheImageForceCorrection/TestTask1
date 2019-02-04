#pragma once

#include <string>
#include "ChatServer.h"
#include "ChatClient.h"
#include "ChatTime.h"

//	class ChatAutomaticClient defines the client, that automatically send messages
class ChatAutomaticClient :public ChatClient, public ChatThreadObj {

private:

	ChatServer &chatServer;
	std::string messageText;
	int timeGap;
	ChatTime curTime;

	ChatAutomaticClient() = delete;

	ChatAutomaticClient(ChatAutomaticClient &) = delete;

public:

	ChatAutomaticClient(int _clientN, int _timeGap, const std::string &_messageText, ChatServer &_chatServer) :ChatClient(_clientN),
		timeGap(_timeGap), messageText(_messageText), chatServer(_chatServer), ChatThreadObj(_timeGap)
	{

	}

	//	void ChatAutomaticClient::action() implements the thread behavior
	void action()
	{
		send();
	}

	//	bool ChatAutomaticClient::isWorking() implements the thread stopping conditions
	bool isWorking() const
	{
		return chatServer.isWorking();
	}

	//	void ChatAutomaticClient::startAutomaticSending() starts automatic message sending
	void startAutomaticSending()
	{
		startExecution();
	}

	//	void ChatAutomaticClient::send() implements sending messages behavior
	void send()
	{
		chatServer.getMessage(messageText, curTime.getTimeStr(), getClientN());
	}

};
