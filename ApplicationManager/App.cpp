#include "App.h"
#include "ErrorStruct.h"

using namespace std;

void checkPath(string& path)
{
	size_t start = path.find(' ');
	if (start == string::npos)
		return;
	for (size_t i = start; i < path.length(); i++)
	{
		if (path[i] == ' ')
		{
			path.insert(path.begin() + i + 1, '\"');
			path.insert(path.begin() + (i++), '\"');
			if (path.find(' ') == string::npos)
				return;
		}
	}
}

string checkKey(string key)
{
	string out = key;
	size_t start = out.find(' ');
	if (start == string::npos)
		return out;
	for (size_t i = start; i < out.length(); i++)
	{
		if (out[i] == ' ')
		{
			out[i] = '-';
			if (key.find(' ') == string::npos)
				return out;
		}
	}
	return out;
}

App::App()
{
	keywords.push_back("cmd");
	path = "cmd.exe";
	isProgram = true;
}

App::App(string input, string path, bool isProgram, bool ignoreCheck)
{
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ',')
		{
			keywords.push_back(checkKey(temp));
			temp.clear();
		}
		else
			temp.push_back(input[i]);
	}
	keywords.push_back(checkKey(temp));
	this->path = path;
	if (!ignoreCheck)
		checkPath(this->path);
	this->isProgram = isProgram;
}

//"trigger1,trigger2|pathOrCommand-isfile(1/0)"
App::App(string input, bool ignoreCheck)
{
	this->isProgram = true;
	bool pushToKey = true;
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == ',')
		{
			keywords.push_back(checkKey(temp));
			temp.clear();
		}
		else if (input[i] == '|')
		{
			keywords.push_back(checkKey(temp));
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

App::App(std::string input, App oldApp, bool ignoreCheck)
{
	this->isProgram = true;
	bool pushToKey = true;
	bool takenPath = false;
	string temp = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] == '*')
		{
			if (pushToKey)
				this->keywords = oldApp.getKeys();
			else
			{
				this->path = oldApp.getPath();
				takenPath = true;
			}
		}
		else if (input[i] == ',')
		{
			keywords.push_back(checkKey(temp));
			temp.clear();
		}
		else if (input[i] == '|')
		{
			keywords.push_back(checkKey(temp));
			pushToKey = false;
		}
		else if (input[i] == '#')
		{
			if (i + 1 == input.length())
			{
				isProgram = true;
				break;
			}
			if (input[i + 1] == '*')
				isProgram = oldApp.getType();
			else
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
	if (!ignoreCheck and !takenPath)
		checkPath(this->path);
}

////Change data
//void App::operator() (string input, string path, bool isProgram, bool ignoreCheck)
//{
//	string temp = "";
//	for (size_t i = 0; i < input.length(); i++)
//	{
//		if (input[i] == ',')
//		{
//			keywords.push_back(temp);
//			temp.clear();
//		}
//		else
//			temp.push_back(input[i]);
//	}
//	keywords.push_back(temp);
//	this->path = path;
//	if (!ignoreCheck)
//		checkPath(this->path);
//	this->isProgram = isProgram;
//}
//
////Change data
////"trigger1,trigger2|pathOrCommand-isfile(1/0)"
//void App::operator() (string input, bool ignoreCheck)
//{
//	isProgram = true;
//	bool pushToKey = true;
//	string temp = "";
//	for (size_t i = 0; i < input.length(); i++)
//	{
//		if (input[i] == ',')
//		{
//			keywords.push_back(temp);
//			temp.clear();
//		}
//		else if (input[i] == '|')
//		{
//			keywords.push_back(temp);
//			pushToKey = false;
//		}
//		else if (input[i] == '#')
//		{
//			isProgram = input[i + 1] - '0';
//			break;
//		}
//		else
//		{
//			if (pushToKey)
//				temp.push_back(input[i]);
//			else
//				this->path.push_back(input[i]);
//		}
//	}
//	if (!ignoreCheck)
//		checkPath(this->path);
//}
//
//void App::operator()(std::string input, App oldApp, bool ignoreCheck)
//{
//	this->isProgram = true;
//	bool pushToKey = true;
//	bool takenPath = false;
//	string temp = "";
//	for (size_t i = 0; i < input.length(); i++)
//	{
//		if (input[i] == '*')
//		{
//			if (pushToKey)
//				this->keywords = oldApp.getKeys();
//			else
//			{
//				this->path = oldApp.getPath();
//				takenPath = true;
//			}
//		}
//		else if (input[i] == ',')
//		{
//			keywords.push_back(checkKey(temp));
//			temp.clear();
//		}
//		else if (input[i] == '|')
//		{
//			keywords.push_back(checkKey(temp));
//			pushToKey = false;
//		}
//		else if (input[i] == '#')
//		{
//			if (i + 1 == input.length())
//			{
//				isProgram = true;
//				break;
//			}
//			if (input[i + 1] == '*')
//				isProgram = oldApp.getType();
//			else
//				isProgram = input[i + 1] - '0';
//			break;
//		}
//		else
//		{
//			if (pushToKey)
//				temp.push_back(input[i]);
//			else
//				this->path.push_back(input[i]);
//		}
//	}
//	if (!ignoreCheck and !takenPath)
//		checkPath(this->path);
//}

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

vector<string> App::getKeys()
{
	return this->keywords;
}
