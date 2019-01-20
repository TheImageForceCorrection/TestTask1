#pragma once

#include <string>
#include <ctime>

using namespace std;

//	class ChatTime provides an interface to the system time 
class ChatTime {

private:

	time_t rawtime;
	tm curTime;
	string timeStr;

	//	void ChatTime::refreshChatTime() loads the current time into the program
	void refreshChatTime();

public:

	//	const string &ChatTime::getTimeStr() returns a string with the current time
	const string &getTimeStr();

	//	int ChatTime::getSeconds() returns the current seconds
	int getSeconds();

	//	int ChatTime::getMinutes() returns the current minutes
	int getMinutes();

	//	int ChatTime::getHours() returns the current hours
	int getHours();

};
