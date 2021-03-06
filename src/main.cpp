#include "../include/ChatProgram.h"
#include "../include/ChatException.h"

int main()
{
	try
	{
		ChatProgram chatProgram;
		chatProgram.execute();
	}
	catch (const ChatException &e)
	{
		std::cout << e;
	}
	catch (...)
	{
		std::cout << "System error\n";
	}

	return 0;
}
