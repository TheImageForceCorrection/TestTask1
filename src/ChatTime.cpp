#include "../include/ChatTime.h"

void ChatTime::refreshChatTime()
{
	time(&rawtime);
	localtime_s(&curTime, &rawtime);
}

const string &ChatTime::getTimeStr()
{
	char buf[10] = "\0";
	refreshChatTime();
	strftime(buf, 10, "%H:%M:%S", &curTime);
	timeStr = buf;
	return timeStr;
}

int ChatTime::getSeconds()
{
	refreshChatTime();
	return curTime.tm_sec;
}

int ChatTime::getMinutes()
{
	refreshChatTime();
	return curTime.tm_min;
}

int ChatTime::getHours()
{
	refreshChatTime();
	return curTime.tm_hour;
}
