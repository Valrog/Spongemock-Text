#include <cctype>

#include <iostream>
#include <string>

#include <Windows.h>

void spongemock_txt(std::string& input);
void clipboard_copy(const std::string& input); // Copies input to Clipboard

int main()
{
	std::string input;

	while (true)
	{
		std::cout << "\n-------------\n";
		std::cout << "Insert text to be mocked (\"exit\" to stop): ";
		std::getline(std::cin, input);

		if (input == "exit")
			break;

		spongemock_txt(input);

		std::cout << "Spongemock text: " << input << "\n";
		clipboard_copy(input);
		std::cout << "Copied!\n";
		std::cout << "-------------\n";
	}

	return 0;
}

void spongemock_txt(std::string& input)
{
	for (auto i = 0; i < input.length(); i++)
	{
		if (i % 2 == 0)
		{
			input[i] = std::toupper(input[i]);
		}

		else
		{
			input[i] = std::tolower(input[i]);
		}
	}
}

void clipboard_copy(const std::string& input)
{
	const char* output = input.data();
	const size_t len = strlen(output) + 1;

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}