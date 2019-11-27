#include <iostream>
#include <string>
#include <cctype>
#include <Windows.h>

std::string spongemock_txt(std::string input);
void clipboard_copy(std::string input); // Copies input to Clipboard

int main()
{
	std::string input;
	std::string mocked;

	while(true)
	{
		std::cout << "\n-------------\n";
		std::cout << "Insert text to be mocked (\"exit\" to stop): ";
		std::getline(std::cin, input);

		if (input == "exit")
			break;

		mocked = spongemock_txt(input);

		std::cout << "Spongemock text: " << mocked << "\n";
		clipboard_copy(mocked);
		std::cout << "Copied!\n";
		std::cout << "-------------\n";
	}

	return 0;
}

std::string spongemock_txt(std::string input)
{
	for (size_t i = 0; i < input.length(); i++)
	{
		if (i % 2 == 0)
		{
			input[i] = std::tolower(input[i]);
		}

		else
		{
			input[i] = std::toupper(input[i]);
		}
	}

	return input;
}

void clipboard_copy(std::string input)
{
	char const* output = input.data();
	const size_t len = strlen(output) + 1;

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}