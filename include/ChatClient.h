#pragma once

//	abstract class ChatClient defines the interface for a client, that can send messages
class ChatClient {

private:

	int clientN;

	ChatClient() = delete;

	ChatClient(ChatClient &) = delete;

public:

	ChatClient(int _clientN) :clientN(_clientN)
	{

	}

	//	void ChatClient::send() defines the client behavior in the implementation class
	virtual void send() = 0;

	// 	int ChatClient::getClientN() returns client number
	int getClientN()
	{
		return clientN;
	}

};
