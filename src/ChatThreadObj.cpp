#include "../include/ChatThreadObj.h"

void ChatThreadObj::threadSleep()
{
	time_t rawtime;
	tm curTime, wakeupTime;
	time(&rawtime);
	localtime_s(&curTime, &rawtime);

	wakeupTime = curTime;
	wakeupTime.tm_sec += timeGap;
	this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(&wakeupTime)));
}

void ChatThreadObj::executionFunc()
{
	while (isWorking())
	{
		threadSleep();
		action();
	}
}

void ChatThreadObj::joinThread()
{
	chatThread->join();
	delete chatThread;
}
