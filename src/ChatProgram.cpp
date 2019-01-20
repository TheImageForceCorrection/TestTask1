#include "../include/ChatProgram.h"

void ChatProgram::execute()
{
	chatServer.startChat();
	chatAutomaticClients.startAutomaticSending();
	chatUI.execution();
	chatServer.stopChat();
	chatAutomaticClients.joinThreads();
	chatServer.joinThread();
}
