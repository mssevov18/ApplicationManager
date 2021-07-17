#include <iostream>
#include <vector>
#include <string>

#include "windows.h"

#include "App.h"
#include "AppHandler.h"
#include "ErrorStruct.h"
#include "TextStyles.h"

bool hasLeadingSpaces(std::string in)
{
	for (size_t i = 0; i < in.length(); i++)
	{
		if (in[i] != ' ')
			return false;
		else
			return true;
	}
	return in.empty();
}

int main()
{
	AppHandler hndl;
	std::string input = "";
	while (input != "exit")
	{
		std::cout << "AppManager> ";
		try
		{
			std::getline(std::cin, input);
			CLROUT(successClr,
				if (!input.empty())
					hndl.parse(input);
			)
			input.clear();
		}
		catch (error err)
		{
			CLROUT (errorClr,
				switch (err.code)
				{
				case 0: // No Error, another way to exit a function
					exit(0);
					break;

				case 1: // Empty input
					err.pms("Error: Empty input.");
					if (!err.src.empty())
						err.getHelp(hndl.hText);
					break;

				case 2: // Incorrect command syntax
					err.pms("Error: Incorrect command syntax.");
					if (!err.src.empty())
						err.getHelp(hndl.hText);
					break;

				case 3: // File could not be oppened
					err.pms("Error: File could not be oppened.");
					if (!err.src.empty())
						err.getHelp(hndl.hText);
					break;

				case 4: // Invalid function
					err.pms("Error: Invalid function.");
					if (!err.src.empty())
						err.getHelp(hndl.hText);
					break;

				case 5: // Incomplete command
					break;

				case 6: // Incomplete command
					break;

				case 7: // Incomplete command
					break;

				case 8: // Incomplete command
					break;
				default:
					break;
				}
			)
		}
		catch (...)
		{
			CLROUT(errorClr,
			std::cerr << "Unspecified Error!";
			)
		}
	} 
}