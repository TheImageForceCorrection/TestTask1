#pragma once

#include <string>
#include <iostream>
#include "ChatException.h"

using namespace std;

//	class ChatUserInterface manages chat initializing information input
class ChatUserInterface {

private:

	string chatFileName;
	unsigned int nClients;
	string *clientMessageTexts;
	int *clientTimeGaps;

	bool isChSpace(int ch) const { return (ch >= -1 && ch <= 255) ? isspace(ch) : 0; }

	bool isChDigit(int ch) const { return (ch >= -1 && ch <= 255) ? isdigit(ch) : 0; }

	//	int  ChatUserInterface::parseClientTimeGap(char *_str, unsigned int _len)
	//	processes _str and returns client thread sleep time and leaves in _str sending message text 
	int parseClientTimeGap(char *_str, unsigned int _len);

	//	void ChatUserInterface::readFromUI() reads initializing information
	void readFromUI();

public:

	ChatUserInterface()
	{
		readFromUI();
	}

	const string &getChatFileName() const
	{
		return chatFileName;
	}

	unsigned int getNClients() const
	{
		return nClients;
	}

	const string &getClientMessageText(int _clientN) const
	{
		return clientMessageTexts[_clientN];
	}

	int getClientTimeGap(int _clientN) const
	{
		return clientTimeGaps[_clientN];
	}

	const string *getClientMessageTexts() const
	{
		return clientMessageTexts;
	}

	const int *getClientTimeGaps() const
	{
		return clientTimeGaps;
	}

	//	void ChatUserInterface::execution() const waiting for the user enters the terminating command
	void execution() const;


	~ChatUserInterface()
	{
		delete[] clientMessageTexts;
		delete[] clientTimeGaps;
	}

};
