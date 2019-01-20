#pragma once

#include <thread>

using namespace std;

//	abstract class ChatThreadObj provides an interface for creating objects with its own thread
class ChatThreadObj {

private:

	int timeGap;
	ChatThreadObj() = delete;
	thread *chatThread;

	//	void ChatThreadObj::threadSleep() makes the thread sleep
	void threadSleep();

	//	void ChatThreadObj::executionFun() is used to make the thread sleep between the necessary actions execution
	void executionFunc();

public:

	//	ChatThreadObj::ChatThreadObj(int _timeGap) is used to construct object
	//	with associated thread with _timeGap sleep time
	ChatThreadObj(int _timeGap) :timeGap(_timeGap)
	{

	}

	//	void ChatThreadObj::startExecution() creates a thread
	void startExecution()
	{
		chatThread = new thread(&ChatThreadObj::executionFunc, this);
	}

	//	void ChatThreadObj::action() defines the thread behavior in the implementation class
	virtual void action() = 0;

	//	bool ChatThreadObj::isWorking() defines the thread stopping conditions in the implementation class
	virtual bool isWorking() const = 0;

	//	void ChatThreadObj::joinThread() joins the thread
	void joinThread();

};
