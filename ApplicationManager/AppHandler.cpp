#include "AppHandler.h"

using namespace std;

AppHandler::AppHandler()
{
}

#define CASE(value, trigger, action)  if (value == trigger) { action; return; }
#define DEFAULT(action) action;

void AppHandler::parse(std::string& input)
{
	CASE(input, "list", this->print());
	CASE(input, "print", this->print());
	CASE(input, "show", this->print());
	CASE(input, "load", this->load("functions.txt"));
	CASE(input, "save", this->save("functions.txt"));
	for (size_t i = 0; i < apps.size(); i++)
	{
		for (size_t j = 0; j < apps[i].size(); j++)
			CASE(input, apps[i][j], !apps[i])
	}
	DEFAULT(cout << "Error! " << input << " is not a valid function\n")
}

void AppHandler::print()
{
	for (size_t i = 0; i < apps.size(); i++)
		~apps[i];
}

void AppHandler::load(static string filepath)
{
	ifstream file;
	file.open(filepath, ios::in);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
			apps.push_back(App(line, true));
		file.close();
		cout << "Successfully loaded " << apps.size() + 1 << " Apps" << filepath << "!\n";
	}
}

void AppHandler::save(static string filepath)
{
	ofstream file;
	file.open(filepath, ios::out | ios::trunc);
	if (file.is_open())
	{
		for (size_t i = 0; i < apps.size(); i++)
		{
			size_t keySize = apps[i].size();
			for (size_t j = 0; j < keySize; j++)
			{
				file << apps[i][j];
				if (j + 1 < keySize)
					file << ',';
			}
			file << '|' << apps[i].getPath() << '#' << apps[i].getType() << '\n';
		}
		file.close();
		cout << "Successfully saved " << apps.size() + 1 << " Apps in " << filepath << "!\n";
	}
}