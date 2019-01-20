#pragma once
#include "ChatUserInterface.h"
#include "ChatAutomaticClients.h"
#include "ChatServer.h"


//	class ChatProgram is the main class of the chat application
class ChatProgram {

private:

	ChatUserInterface chatUI;
	ChatAutomaticClients chatAutomaticClients;
	ChatServer chatServer;

public:

	ChatProgram() :chatUI(), chatServer(chatUI.getChatFileName(), chatUI.getNClients()),
		chatAutomaticClients(chatUI.getNClients(), chatUI.getClientTimeGaps(), chatUI.getClientMessageTexts(), chatServer)
	{

	}

	//	void ChatProgram::execute() manages the chat application execution
	void execute();

};
