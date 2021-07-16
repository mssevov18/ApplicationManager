#include "App.h"

using namespace std;

void checkPath(string& path)
{
	for (int i = path.length() - 1; i >= 0; i--)
	{
		if (path[i] == ' ')
		{
			path.insert(path.begin() + i + 1, '\"');
			path.insert(path.begin() + i, '\"');
		}
	}
}

App::App()
{
	keywords.push_back("cmd");
	path = "cmd.exe";
	isProgram = true;
}

App::App(std::string input, std::string path, bool isProgram, bool ignoreCheck)
{
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ',')
		{
			keywords.push_back(temp);
			temp.clear();
		}
		else
			temp.push_back(input[i]);
	}
	keywords.push_back(temp);
	this->path = path;
	if (!ignoreCheck)
		checkPath(this->path);
	this->isProgram = isProgram;
}

//"trigger1,trigger2|pathOrCommand-isfile(1/0)"
App::App(std::string input, bool ignoreCheck)
{
	isProgram = true;
	bool pushToKey = true;
	std::string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ',')
		{
			keywords.push_back(temp);
			temp.clear();
		}
		else if (input[i] == '|')
		{
			keywords.push_back(temp);
			pushToKey = false;
		}
		else if (input[i] == '#')
		{
			isProgram = input[i + 1] - '0';
			break;
		}
		else
		{
			if (pushToKey)
				temp.push_back(input[i]);
			else
				this->path.push_back(input[i]);
		}
	}
	if (!ignoreCheck)
		checkPath(this->path);
}

//Change data
void App::operator() (std::string input, std::string path, bool isProgram, bool ignoreCheck)
{
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ',')
		{
			keywords.push_back(temp);
			temp.clear();
		}
		else
			temp.push_back(input[i]);
	}
	keywords.push_back(temp);
	this->path = path;
	if (!ignoreCheck)
		checkPath(this->path);
	this->isProgram = isProgram;
}

//Change data
//"trigger1,trigger2|pathOrCommand-isfile(1/0)"
void App::operator() (std::string input, bool ignoreCheck)
{
	isProgram = true;
	bool pushToKey = true;
	std::string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ',')
		{
			keywords.push_back(temp);
			temp.clear();
		}
		else if (input[i] == '|')
		{
			keywords.push_back(temp);
			pushToKey = false;
		}
		else if (input[i] == '#')
		{
			isProgram = input[i + 1] - '0';
			break;
		}
		else
		{
			if (pushToKey)
				temp.push_back(input[i]);
			else
				this->path.push_back(input[i]);
		}
	}
	if (!ignoreCheck)
		checkPath(this->path);
}

//Print
void App::operator~()
{
	for (size_t i = 0; i < keywords.size(); i++)
		cout << keywords[i] << ", ";
	cout << "\b\b ";
	cout << "| " << path << " # " << isProgram << '\n';
}

//Use
void App::operator! ()
{
	//system(std::string(isProgram ? "start " : "" + path).c_str());
	if (isProgram)
		system(std::string("\"start " + path + "\"").c_str());
	else
		system(path.c_str());
}

//Get keyword by indedx
string App::operator[] (size_t index)
{
	return this->keywords[index];
}

//Get keyword vector size
size_t App::size()
{
	return this->keywords.size();
}

//Get the application path
string App::getPath()
{
	return this->path;
}
//Get the application type
bool App::getType()
{
	return isProgram;
}
