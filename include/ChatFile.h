#pragma once

#include <string>
#include <fstream>
#include "ChatException.h"
#include "ChatMessage.h"

//	class ChatFile provides an interface for writing to a chat file 
class ChatFile {

private:

	const std::string filename;

	ChatFile() = delete;

	ChatFile(ChatFile &) = delete;

public:

	//	ChatFile::ChatFile(const string &_filename) initializes chat file _filename 
	ChatFile(const std::string &_filename);

	//	ChatFile::Write(const ChatMessage &_message) writes _message in the chat file
	void Write(const ChatMessage &_message);

};

