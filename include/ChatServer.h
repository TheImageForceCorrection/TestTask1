#pragma once

#include <string>
#include <mutex>
#include <queue>
#include "ChatMessage.h"
#include "ChatFile.h"
#include "ChatThreadObj.h"

using namespace std;

//	class ChatServer manages message receiving 
class ChatServer :public ChatThreadObj {

private:

	ChatFile file;

	bool working;
	mutex mu;
	queue<const ChatMessage *> messages;


	ChatServer() = delete;

	ChatServer(ChatServer &) = delete;

public:

	ChatServer(const string &_chatFileName, int _nClients) : file(_chatFileName), ChatThreadObj(1)
	{

	}

	//	void ChatServer::action() implements the thread behavior
	void action()
	{
		writeMessages();
	}

	//	bool ChatServer::isWorking() implements the thread stopping conditions
	bool isWorking() const
	{
		return working;
	}

	//	void ChatServer::getMessage(const string  &_messageText, const string &_timeStr, int _nClient) receives messages
	void getMessage(const string  &_messageText, const string &_timeStr, int _nClient);

	//	void ChatServer::writeMessages() refers to the chat file's write interface
	void writeMessages();

	//	void ChatServer::startChat() starts chat execution
	void startChat();

	//	void ChatServer::stopChat() stops all threads
	void stopChat()
	{
		working = false;
	}

};
