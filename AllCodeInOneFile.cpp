#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
#include <queue>
#include <fstream>
#include <vector>
#include <cctype>
#include <mutex>
using namespace std;


//	class ChatTime provides an interface to the system time 
class ChatTime {

private:

	time_t rawtime;
	tm curTime;
	string timeStr;

	//	void ChatTime::refreshChatTime() loads the current time into the program
	void refreshChatTime()
	{
		time(&rawtime);
		localtime_s(&curTime, &rawtime);
	}

public:

	//	const string &ChatTime::getTimeStr() returns a string with the current time
	const string &getTimeStr()
	{
		char buf[10] = "\0";
		refreshChatTime();
		strftime(buf, 10, "%H:%M:%S", &curTime);
		timeStr = buf;
		return timeStr;
	}

	//	int ChatTime::getSeconds() returns the current seconds
	int getSeconds()
	{
		refreshChatTime();
		return curTime.tm_sec;
	}

	//	int ChatTime::getMinutes() returns the current minutes
	int getMinutes()
	{
		refreshChatTime();
		return curTime.tm_min;
	}

	//	int ChatTime::getHours() returns the current hours
	int getHours()
	{
		refreshChatTime();
		return curTime.tm_hour;
	}

};


//	abstract class ChatThreadObj provides an interface for creating objects with its own thread
class ChatThreadObj{

private:

	int timeGap;
	ChatThreadObj() = delete;
	thread *chatThread;
	
	//	void ChatThreadObj::threadSleep() makes the thread sleep
	void threadSleep()
	{
		time_t rawtime;
		tm curTime, wakeupTime;
		time(&rawtime);
		localtime_s(&curTime, &rawtime);

		wakeupTime = curTime;
		wakeupTime.tm_sec += timeGap;
		this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(&wakeupTime)));
	}

	//	void ChatThreadObj::executionFun() is used to make the thread sleep between the necessary actions execution
	void executionFunc()
	{
		while (isWorking())
		{
			threadSleep();
			action();
		}
	}

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
	void joinThread()
	{
		chatThread->join();
		delete chatThread;
	}

};


//	class ChatException is a special exception class
class ChatException{

private:

	const string errDescription;

	ChatException() = delete;

public:

	//	ChatException::ChatException(const string &_errDescription, const string &_whereFunc) creates throwing object with
	//	a description of the exception reason in _errDescription and the name of the method which has throwed the exception
	ChatException(const string &_errDescription, const string &_whereFunc) :
		errDescription("\nError in " + _whereFunc + "\n" + _errDescription + "\n\n")
	{

	}

	//	const string &ChatException::what() const returns string containing the information about the exception reason
	const string &what() const
	{
		return errDescription;
	}

};


ostream &operator<<(ostream &os, const ChatException &_exception)
{
	os << _exception.what();
	return os;
}


//	class ChatMessage incapsulates sending messages
class ChatMessage {

private:

	const string text;
	const string time;
	int nClient;

	ChatMessage() = delete;

	ChatMessage(ChatMessage &) = delete;

public:

	ChatMessage(const string &_text, const string &_time, int _nClient) :text(_text), time(_time), nClient(_nClient)
	{

	}

	const int whoseMessage() const
	{
		return nClient;
	}

	const string &getTime() const
	{
		return time;
	}

	const string &getText() const
	{
		return text;
	}

};


ostream &operator<<(ostream &os, const ChatMessage &_message)
{
	os << _message.getTime() << "; " << _message.whoseMessage() << ": " << _message.getText();
	return os;
}


//	class ChatFile provides an interface for writing to a chat file 
class ChatFile {

private:

	const string filename;

	ChatFile() = delete;

	ChatFile(ChatFile &) = delete;

public:

	//	ChatFile::ChatFile(const string &_filename) initializes chat file _filename 
	ChatFile(const string &_filename) :filename(_filename)
	{
		ofstream curFile(filename, std::ofstream::trunc);
		if (!curFile.is_open())
			throw (ChatException("Cannot open file", "ChatFile::ChatFile(const string &_filename)"));
		curFile.close();
	}

	//	ChatFile::Write(const ChatMessage &_message) writes _message in the chat file
	void Write(const ChatMessage &_message)
	{
		ofstream curFile(filename, std::ofstream::app);
		if (!curFile.is_open())
			throw (ChatException("Cannot open file", "void ChatFile::Write(const ChatMessage&_message)"));
		curFile << _message << "\n";
		curFile.close();
	}

};


//	class ChatServer manages message receiving 
class ChatServer :public ChatThreadObj{

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
	void getMessage(const string  &_messageText, const string &_timeStr, int _nClient)
	{
		const ChatMessage *curMessage = new ChatMessage(_messageText, _timeStr, _nClient);
		mu.lock();
		messages.push(curMessage);
		mu.unlock();
	}

	//	void ChatServer::writeMessages() refers to the chat file's write interface
	void writeMessages()
	{
		mu.lock();
		while (!messages.empty())
		{
			const ChatMessage *curMessage = messages.front();
			file.Write(*curMessage);
			delete curMessage;
			messages.pop();
		}
		mu.unlock();
	}

	//	void ChatServer::startChat() starts chat execution
	void startChat()
	{
		working = true;
		startExecution();
	}

	//	void ChatServer::stopChat() stops all threads
	void stopChat()
	{
		working = false;
	}

};

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

//	class ChatAutomaticClient defines the client, that automatically send messages
class ChatAutomaticClient :public ChatClient, public ChatThreadObj {

private:

	ChatServer &chatServer;
	string messageText;
	int timeGap;
	ChatTime curTime;

	ChatAutomaticClient() = delete;

	ChatAutomaticClient(ChatAutomaticClient &) = delete;

public:

	ChatAutomaticClient(int _clientN, int _timeGap, const string &_messageText, ChatServer &_chatServer) :ChatClient(_clientN),
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


//	class ChatAutomaticClients manages the clients, that automatically send messages
class ChatAutomaticClients :public vector<ChatAutomaticClient *>
{

public:
	
	ChatAutomaticClients(unsigned int _nClients, const int *_timeGaps, const string *_messageTexts, ChatServer &_chatServer)
	{
		for (unsigned int i = 0; i < _nClients; i++)
		{
			push_back(new ChatAutomaticClient(i, _timeGaps[i], _messageTexts[i], _chatServer));
		}
	}

	//	void ChatAutomaticClient::startAutomaticSending() starts automatic message sending
	void startAutomaticSending()
	{
		for (unsigned int i = 0; i < size(); i++)
			operator[](i)->startAutomaticSending();
	}
	
	//	void ChatAutomaticClient::joinThread() joins threads
	void joinThreads()
	{
		for (unsigned int i = 0; i < size(); i++)
			operator[](i)->joinThread();
	}

	~ChatAutomaticClients()
	{
		for (unsigned int i = 0; i < size(); i++)
			delete operator[](i);
	}

};


//	class ChatUserInterface manages chat initializing information input
class ChatUserInterface{

private:

	string chatFileName;
	unsigned int nClients;
	string *clientMessageTexts;
	int *clientTimeGaps;

	bool isChSpace(int ch) const { return (ch >= -1 && ch <= 255) ? isspace(ch) : 0; }

	bool isChDigit(int ch) const { return (ch >= -1 && ch <= 255) ? isdigit(ch) : 0; }

	//int  ChatUserInterface::parseClientTimeGap(char *_str, unsigned int _len)
	//processes _str and returns client thread sleep time and leaves in _str sending message text 
	int parseClientTimeGap(char *_str, unsigned int _len)
	{
		unsigned int newStrBegin;
		unsigned int j = 0;
		int result = atoi(_str);

		if (result<=0)
			throw (ChatException("Invalid input data format", "int ChatUserInterface::parseClientTimeGap(char *_str, unsigned int _len)"));

		for (; j < _len && isChSpace(_str[j]); j++);
		for (; j < _len && isChDigit(_str[j]); j++);
		for (; j < _len && isChSpace(_str[j]); j++);

		if (_str[j] == '\0' || j == _len)
			throw (ChatException("Invalid input data format", "int ChatUserInterface::parseClientTimeGap(char *_str, unsigned int _len)"));

		newStrBegin = j;

		for (; j < _len && _str[j] != '\0'; j++)
			_str[j - newStrBegin] = _str[j];

		_str[j - newStrBegin] = '\0';

		return result;
	}

	//	void ChatUserInterface::readFromUI() reads initializing information
	void readFromUI()
	{
		char buf[256];
		cin.getline(buf, 256);
		chatFileName = buf;

		cin.getline(buf, 256);
		if ((nClients = atoi(buf))<=0)
			throw (ChatException("Invalid input data format", "void ChatUserInterface::readFromUI()"));

		clientMessageTexts = new string[nClients];
		clientTimeGaps = new int[nClients];

		for (unsigned int i = 0; i < nClients; i++)
		{
			cin.getline(buf, 256);
			clientTimeGaps[i] = parseClientTimeGap(buf, 256);
			clientMessageTexts[i] = buf;
		}
	}

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
	void execution() const
	{
		char buf[256];
		do
		{
			cout << "Enter q to exit\n";
			cin.getline(buf, 256);
			
			int j = 0;
			for (; j < 256 && isChSpace(buf[j]); j++);
			
			unsigned int newStrBegin = j;

			if (j != 0)
			{
				for (; j < 256 && j != '\0'; j++)
					buf[j - newStrBegin] = buf[j];

				buf[j - newStrBegin] = '\0';
			}

			for (j=0; j < 256 && buf[j] != '\0'; j++);
			for (--j; j >= 0 && isChSpace(buf[j]); --j);
			buf[j + 1] = '\0';

		}
		while (!(string(buf) == "q"));

	}

	~ChatUserInterface()
	{
		delete[] clientMessageTexts;
		delete[] clientTimeGaps;
	}

};


//	class ChatProgram is the main class of the chat application
class ChatProgram{

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
	void execute()
	{
		chatServer.startChat();
		chatAutomaticClients.startAutomaticSending();
		chatUI.execution();
		chatServer.stopChat();
		chatAutomaticClients.joinThreads();
		chatServer.joinThread();
	}

};


int main()
{
	try
	{
		ChatProgram chatProgram;
		chatProgram.execute();
	}
	catch (const ChatException &e)
	{
		cout << e;
	}
	catch (...)
	{
		cout << "System error\n";
	}

	return 0;
}
