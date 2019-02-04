#include "../include/ChatUserInterface.h"

int ChatUserInterface::parseClientTimeGap(char *_str, unsigned int _len)
{
	unsigned int newStrBegin;
	unsigned int j = 0;
	int result = atoi(_str);

	if (result <= 0)
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

void ChatUserInterface::readFromUI()
{
	char buf[256];
	std::cin.getline(buf, 256);
	chatFileName = buf;

	std::cin.getline(buf, 256);
	if ((nClients = atoi(buf)) <= 0)
		throw (ChatException("Invalid input data format", "void ChatUserInterface::readFromUI()"));

	clientMessageTexts = new std::string[nClients];
	clientTimeGaps = new int[nClients];

	for (unsigned int i = 0; i < nClients; i++)
	{
		std::cin.getline(buf, 256);
		clientTimeGaps[i] = parseClientTimeGap(buf, 256);
		clientMessageTexts[i] = buf;
	}
}

void ChatUserInterface::execution() const
{
	char buf[256];
	do
	{
		std::cout << "Enter q to exit\n";
		std::cin.getline(buf, 256);

		int j = 0;
		for (; j < 256 && isChSpace(buf[j]); j++);

		unsigned int newStrBegin = j;

		if (j != 0)
		{
			for (; j < 256 && j != '\0'; j++)
				buf[j - newStrBegin] = buf[j];

			buf[j - newStrBegin] = '\0';
		}

		for (j = 0; j < 256 && buf[j] != '\0'; j++);
		for (--j; j >= 0 && isChSpace(buf[j]); --j);
		buf[j + 1] = '\0';

	}
	
	while (!(std::string(buf) == "q"));

}
