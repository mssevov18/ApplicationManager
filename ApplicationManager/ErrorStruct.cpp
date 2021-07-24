#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "TextStyles.h"
#include "ErrorStruct.h"

error::error()
{
	this->code = 0;
	this->msg = "";
	this->src = "";
	this->uin = "";
}

error::error(int code, string msg, string src, string uin)
	{
		this->code = code;
		this->msg = msg;
		this->src = src;
		this->uin = uin;
	}

void error::trw(int code, string msg, string src, string uin)
{
	throw error(code, msg, src, uin);
}

void error::trw(error err)
{
	throw err;
}

void error::pms(string header)
{
	//cout << '\a';
	if (!header.empty())
		cout << header << '\n';
	if (!msg.empty())
		cout << msg << '\n';
	cout << '\n';
}

void error::getHelp(vector<helpText>& hText)
{
	cout << "Input: " << uin;
	for (size_t i = 0; i < hText.size(); i++)
		if (src == hText[i].keyword)
			cout << '\n' << hText[i].keyword << " - " << hText[i].description << "\n\n\t" << hText[i].extraHelp << "\n\n";
}


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