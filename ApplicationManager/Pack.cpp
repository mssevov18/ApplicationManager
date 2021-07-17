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
	std::string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '|')
			pushToKey = true;
		else if (input[i] == ',')
		{
			appKeys.push_back(temp);
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
	appKeys.push_back(temp);
}

size_t Pack::size()
{
	return appKeys.size();
}

void Pack::remove(size_t index)
{
	this->appKeys.erase(this->appKeys.begin() + index);
}

void Pack::list()
{
	for (size_t i = 0; i < appKeys.size(); i++)
		std::cout << appKeys[i] << ' ';
	std::cout << '\n';
}

std::string Pack::getName()
{
	return name;
}

void Pack::operator()(string input)
{
	bool pushToKey = false;
	std::string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '|')
			pushToKey = true;
		else if (input[i] == ',')
		{
			appKeys.push_back(temp);
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
	appKeys.push_back(temp);
}

void Pack::operator~()
{
	std::cout << name << " | ";
	for (size_t i = 0; i < appKeys.size(); i++)
		std::cout << appKeys[i] << ", ";
	std::cout << "\b\b \n";
}

std::string Pack::operator[](size_t index)
{
	return appKeys[index];
}
