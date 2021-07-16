#include <thread>

#include "stdlib.h"

#include "AppHandler.h"

using namespace std;

#define CASE(value, trigger, action)  if (value == trigger) { action; }
#define CASEr(value, trigger, action)  if (value == trigger) { action; return; }
#define CASEb(value, trigger, action)  if (value == trigger) { action; break; }
#define CASEc(value, trigger, action)  if (value == trigger) { action; continue; }
#define CASEe(value, trigger, action)  if (value == trigger) { action; exit(0); }
#define DEFAULT(action) action;

helpText::helpText()
{
	keyword = "";
	description = "";
	extraHelp = "";
}

helpText::helpText(string newKw, string newDs, string newEh)
{
	keyword = newKw;
	description = newDs;
	extraHelp = newEh;
}

AppHandler::AppHandler()
{
//	string a =
//"\n\
//help   - Shows all system commands\n\
//list   - Shows all available apps\n\
//add    - Add a new app\n\
//    add \"keyword1,keyword2,keyword3|path/command#1/0(isProgram)\"\n\
//edit   - Edit an app\n\
//    edit \"keywordOfAppForEdit newKeyword1,newKeyword2,newKeyword3|newPath/newCommand#1/0(isProgram)\" leave a value as * to keep it unchanged\n\
//remove - Remove the app from the list\n\
//    remove \"keywordOfAppToRemove\"\n\
//save   - Save apps to external file\n\
//    save [\"filepath\"]\n\
//load   - Load apps from external file\n\
//    load [\"filepath\"]\n\
//file   - Open save file\n\
//    file [\"filepath\"]\n\
//exit   - Go back\n\
//";

	hText.push_back(helpText(
		"help",
		"Shows all system commands. Write another keyword after for specific help.",
		"help [\"keyword\"]"));
	hText.push_back(helpText(
		"list",
		"Shows all available apps/packs.",
		"list [app/pack]"));
	hText.push_back(helpText(
		"add",
		"Add a new app/pack.",
		"add \"keyword1,keyword2,keyword3|path/command[#1/0(isProgram)]\"\n\
		add \"packName|keyword1,keyword2,keyword3\""));
	// add app kw1,kw2|path_cmd[#1_0]
	// add pack name|kw1,kw2
	hText.push_back(helpText(
		"edit",
		"Edit an existing app/pack.",
		"edit \"app/pack\" \"keywordOfAppForEdit newKeyword1,newKeyword2,newKeyword3|newPath/newCommand#1/0(isProgram)\""));
	hText.push_back(helpText(
		"remove",
		"Remove an app/pack from the list.",
		"remove \"app/pack\" \"keywordOfItemToRemove\""));
	hText.push_back(helpText(
		"save",
		"Save apps and packs to external file.",
		"save [\"filepath\"]"));
	hText.push_back(helpText(
		"load",
		"Load apps and packs from external file.",
		"load [\"filepath\"]"));
	hText.push_back(helpText(
		"file",
		"Open save file.",
		"file"));
	hText.push_back(helpText(
		"exit",
		"Go back.",
		"exit"));

}

string getFirstWord(static string& input)
{
	string out = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] != ' ')
			out.push_back(input[i]);
		else
			return out;
	}
	return input;
}

string getCommand(string input, string keyword)
{
	if (keyword.length() + 1 > input.length())
		return "";
	string command = input.substr(keyword.length() + 1);
	if (command.empty())
		return "";
	return command;
}

void AppHandler::parse(string input)
{
	cout << '\n';
	for (size_t i = 0; i < apps.size(); i++)
		for (size_t j = 0; j < apps[i].size(); j++)
			CASEr(input, apps[i][j], !apps[i])
	for (size_t i = 0; i < packs.size(); i++)
		for (size_t j = 0; j < packs[i].size(); j++)
			CASEr(input, packs[i].getName(), packOpen(packs[i]))
	CASEr(getFirstWord(input), "help",   this->Help  (getCommand(input, "help"  )); cout << '\n';)
	CASEr(getFirstWord(input), "list",   this->List  (getCommand(input, "list"  )); cout << '\n';)
	CASEr(getFirstWord(input), "add",    this->Add   (getCommand(input, "add"   )); cout << '\n';)
	CASEr(getFirstWord(input), "edit",   this->Edit  (getCommand(input, "edit"  )); cout << '\n';)
	CASEr(getFirstWord(input), "remove", this->Remove(getCommand(input, "remove")); cout << '\n';)
	CASEr(getFirstWord(input), "save",   this->Save  (getCommand(input, "save"  )); cout << '\n';)
	CASEr(getFirstWord(input), "load",   this->Load  (getCommand(input, "load"  )); cout << '\n';)
	CASEr(getFirstWord(input), "file",   this->File  (getCommand(input, "file"  )); cout << '\n';)
	CASEr(input, "exit", cout << "\n\nBye~";   exit(0))
	DEFAULT(cout << "Error! " << input << " is not a valid function\n")
	cout << '\n';
}

//DWORD sleeplen = 50;
//vector<char> sprites = { '-','\\','|','/' };
//void loadingScreen()
//{
//	cout << '#' << flush;
//	while (true)
//	{
//		for (size_t i = 0; i < sprites.size(); i++)
//		{
//			Sleep(sleeplen);
//			cout << '\b' << sprites[i] << flush;
//		}
//	}
//}

void AppHandler::packOpen(Pack pack)
{
	for (size_t i = 0; i < pack.size(); i++)
		parse(pack[i]);
}

size_t AppHandler::findAppPosByKeyword(static string keyword)
{
	for (size_t i = 0; i < this->apps.size(); i++)
		for (size_t j = 0; j < this->apps[i].size(); j++)
			if (keyword == this->apps[i][j])
				return i;
	return string::npos;
}

size_t AppHandler::findPackPosByKeyword(std::string keyword)
{
	for (size_t i = 0; i < this->packs.size(); i++)
		for (size_t j = 0; j < this->packs[i].size(); j++)
			if (keyword == this->packs[i].getName())
				return i;
	return string::npos;
}

void AppHandler::Help(static string input)
{
	if (input.empty())
		for (size_t i = 0; i < this->hText.size(); i++)
			cout << this->hText[i].keyword << " -\t-\t- " << this->hText[i].description << '\n';
	else
		for (size_t i = 0; i < this->hText.size(); i++)
			CASE(input, this->hText[i].keyword,
				cout << this->hText[i].keyword << " -\t-\t- " << this->hText[i].description << "\n\n\t" << this->hText[i].extraHelp << '\n')
	cout << '\n';
}

void AppHandler::List(static string input)
{
	if (input == "apps" or input.empty())
	{
		cout << "Apps [" << apps.size() << "]:\n";
		for (size_t i = 0; i < apps.size(); i++)
			~apps[i];
	}
	if (input == "packs" or input.empty())
	{
		cout << "Packs [" << packs.size() << "]:\n";
		for (size_t i = 0; i < packs.size(); i++)
			~packs[i];
	}
}

//void AppHandler::Add(std::string input)
//{
//	string command = getCommand(input, "add");
//	if (command.empty())
//	{
//		cout << "Creation failed!\n";
//		return;
//	}
//	apps.push_back(App(command));
//	cout << "Created app:\n\t";
//	~apps[apps.size() - 1];
//}

// add app kw1,kw2|path_cmd[#1_0]
// add pack name|kw1,kw2
void AppHandler::Add(std::string input)
{
	if (getFirstWord(input) == "app")
	{
		input = getCommand(input, "app");
		if (input.empty())
		{
			cout << "Creation failed!\n";
			return;
		}
		apps.push_back(App(input));
		cout << "Created app:\n\t";
		~apps[apps.size() - 1];
	}
	else if (getFirstWord(input) == "pack")
	{
		input = getCommand(input, "pack");
		if (input.empty())
		{
			cout << "Creation failed!\n";
			return;
		}
		packs.push_back(Pack(input));
		cout << "Created pack:\n\t";
		~packs[packs.size() - 1];
	}
}

//	######## ########### ###     ###
//	######## ###########  ###   ###
//	###	         ###	   ### ###
//	#######      ###	    #####
//	#######      ###	    #####
//	###	         ###	   ### ###
//	###	     ###########  ###   ###
//  ###	     ########### ###     ###  the edit function

void AppHandler::Edit(std::string input)
{
	//ADD VVV
	//this->findAppPosByKeyword(input);
	//this->findPackPosByKeyword(input);
	if (getFirstWord(input) == "app")
	{
		//string type = getCommand(input, "app");
		//if (type.empty())
		//{
		//	cout << "Edit failed!\n";
		//	return;
		//}
		string newApp = getCommand(input, getFirstWord(input));
		if (newApp.empty())
		{
			cout << "Edit failed!\n";
			return;
		}
		input = (getFirstWord(input));
		size_t position = this->findAppPosByKeyword(input);
		App oldApp = this->apps[position];
		this->apps[position] = App(newApp);
		cout << "Edited app, from \n\t";
		~oldApp;
		cout << "to \n\t";
		~this->apps[position];
	}
	else if (getFirstWord(input) == "pack")
	{
		//string type = getCommand(input, "pack");
		//if (type.empty())
		//{
		//	cout << "Edit failed!\n";
		//	return;
		//}
		string temp = getCommand(input, getFirstWord(input));
		if (temp.empty())
		{
			cout << "Edit failed!\n";
			return;
		}
		input = getFirstWord(temp);
		string newPack = getCommand(temp, input);
		size_t position = this->findAppPosByKeyword(input);
		Pack oldPack = this->packs[position];
		this->packs[position] = Pack(newPack);
		cout << "Edited app, from \n\t";
		~oldPack;
		cout << "to \n\t";
		~this->packs[position];
	}
	else
		cout << "Edit failed!\n";
}

//	######## ########### ###     ###
//	######## ###########  ###   ###
//	###	         ###	   ### ###
//	#######      ###	    #####
//	#######      ###	    #####
//	###	         ###	   ### ###
//	###	     ###########  ###   ###
//  ###	     ########### ###     ###  the remove - pack function

void AppHandler::Remove(std::string input)
{
	if (getFirstWord(input) == "app")
	{
		size_t position = this->findAppPosByKeyword(getCommand(input, getFirstWord(input)));
		cout << "Removed app\n\t";
		~this->apps[position];
		this->apps.erase(this->apps.begin() + position);
		//this->apps.erase(this->apps.begin() + this->findPosByKeyword(getCommand(input, "remove")));
	}
	else if (getFirstWord(input) == "pack")
	{
		size_t position = this->findPackPosByKeyword(getCommand(input, getFirstWord(input)));
		cout << "Removed pack\n\t";
		~this->packs[position];
		this->packs[position].erase(position);
		//this->apps.erase(this->apps.begin() + this->findPosByKeyword(getCommand(input, "remove")));
	}
	else
		cout << "Removal failed!\n";
}

void AppHandler::Save(static string input)
{
	if (input.empty())
		input = "functions.txt";
	ofstream file;
	file.open(input, ios::out | ios::trunc);
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
		file << "~Packs~\n";
		for (size_t i = 0; i < packs.size(); i++)
		{
			file << packs[i].getName() << '|';
			size_t keySize = packs[i].size();
			for (size_t j = 0; j < packs[i].size(); j++)
			{
				file << packs[i][j];
				if (j + 1 < keySize)
					file << ',';
			}
			file << '\n';
		}
		file.close();
		cout << "Successfully saved " << apps.size() << " Apps and " << packs.size() << " Packs in " << input << "!\n";
	}
}

void AppHandler::Load(static string input)
{
	if (input.empty())
		input = "functions.txt";
	ifstream file;
	file.open(input, ios::in);
	if (file.is_open())
	{
		string line;
		bool readApps = true;
		while (getline(file, line))
		{
			if (line == "~Packs~")
			{
				readApps = false;
				continue;
			}

			if (readApps)
				apps.push_back(App(line, true));
			else
				packs.push_back(Pack(line));
		}
		file.close();
		cout << "Successfully loaded " << apps.size() << " Apps and " << packs.size() << " Packs from " << input << "!\n";
	}
}

void AppHandler::File(static string input)
{
	if (input.empty())
		system(string("start functions.txt").c_str());
	else
		system(string("start " + input).c_str());
}