#include <iomanip>

#include "Pack.h"
#include "ErrorStruct.h"

using namespace std;

Pack::Pack()
{
	name = "pack";
}

Pack::Pack(string input)
{
	bool pushToKey = false;
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '|')
			pushToKey = true;
		else if (input[i] == ',')
		{
			if (!temp.empty())
				appKeys.push_back(checkKey(temp));
			temp.clear();
		}
		else
		{
			if (pushToKey)
				temp.push_back(input[i]);
			else
				this->name.push_back(input[i]);
		}
	}
	if (!temp.empty())
		appKeys.push_back(temp);
}

Pack::Pack(string input, Pack oldPack)
{
	bool pushToKey = false, skipLast = false;
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '*')
		{
			if (pushToKey)
			{
				skipLast = true;
				for (size_t i = 0; i < oldPack.size(); i++)
					this->appKeys.push_back(oldPack[i]);
				break;
			}
			else
				this->name = oldPack.getName();
		}
		else if (input[i] == '|')
			pushToKey = true;
		else if (input[i] == ',')
		{
			if (!temp.empty())
				appKeys.push_back(checkKey(temp));
			temp.clear();
		}
		else
		{
			if (pushToKey)
				temp.push_back(input[i]);
			else
				this->name.push_back(input[i]);
		}
	}
	if (!skipLast and !temp.empty())
		appKeys.push_back(temp);
}

size_t Pack::size()
{
	return appKeys.size();
}

std::string Pack::getName()
{
	return name;
}

std::vector<std::string> Pack::getKeys()
{
	return appKeys;
}

void Pack::operator()(int width)
{
	cout.fill(' ');
	cout << name << setw(width) << " | ";
	for (size_t i = 0; i < appKeys.size(); i++)
		cout << appKeys[i] << ", ";
	cout << "\b\b \n";
}

void Pack::operator~()
{
	cout << name << " | ";
	for (size_t i = 0; i < appKeys.size(); i++)
		cout << appKeys[i] << ", ";
	cout << "\b\b \n";
}

std::string Pack::operator[](size_t index)
{
	return appKeys[index];
}