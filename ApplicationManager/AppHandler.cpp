#include <fstream>

#include "stdlib.h"

#include "AppHandler.h"
#include "ErrorStruct.h"

using namespace std;

#define version    "1.2.3"
#define lastupdate "18.7.2021 06:20"

#define CASE(value, trigger, action)  if (value == trigger) { action; }
#define CASEr(value, trigger, action)  if (value == trigger) { action; return; }
#define CASEb(value, trigger, action)  if (value == trigger) { action; break; }
#define CASEc(value, trigger, action)  if (value == trigger) { action; continue; }
#define CASEe(value, trigger, action)  if (value == trigger) { action; exit(0); }
#define CASEt(value, trigger, action, tval)  if (value == trigger) { action; throw tval; }
#define DEFAULT(action) action;

string getFirstWord(string input, char delim = ' ')
{
	string out = "";
	for (size_t i = 0; i < input.length(); i++)
	{
		if (input[i] != delim)
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

helpText::helpText(std::string input)
{
	keyword = getFirstWord(input, '|');
	description = getFirstWord(getCommand(input, keyword), '|');
	extraHelp = getCommand(input, keyword + '|' + description);
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
"info",
"Shows the project info.",
"info"));
	hText.push_back(helpText(
"list",
"Shows all available apps/packs.",
"list \"app/pack\""));
	hText.push_back(helpText(
"add",
"Add a new app/pack.",
"add \"app\" \"keyword1,keyword2,keyword3|path/command[#1/0(isProgram)]\"\n\
	add \"pack\" \"packName|keyword1,keyword2,keyword3\""));
	// add app kw1,kw2|path_cmd[#1_0]
	// add pack name|kw1,kw2
	hText.push_back(helpText(
"edit",
"Edit an existing app/pack.",
"edit \"app/pack\" \"keywordOfAppForEdit newKeyword1,newKeyword2,newKeyword3|newPath/newCommand#1/0(isProgram)\"\n\
		Enter \'*\' to load the previous data, can be put at the end of a section to add more data\n\
		example: edit app key key1,*|*"));
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
"Exit from the program.",
"exit"));
	hText.push_back(helpText(
"cls",
"Clears the screen.",
"cls"));

	char dec = 'n';
	CLROUT(listClr,
	cout << "Load elements? y/n\n";
	cin >> dec;
	cout << '\n';
	if (dec == 'y' or dec == 'Y')
	{
		CLROUTD(successClr, listClr, this->Load();)
	}
	else
	{
		CLROUTD(successClr, listClr, cout << "No elements loaded";)
	}
	cout << '\n';
	cin.ignore(CHAR_MAX, '\n');
	cin.clear();
	)
}

void AppHandler::Destructor()
{
	char dec = 'n';
	CLROUT(listClr,
		cout << "Save elements? y/n\n";
	cin >> dec;
	cout << '\n';
	if (dec == 'y' or dec == 'Y')
	{
		CLROUTD(successClr, listClr, this->Save();)
	}
	else
	{
		CLROUTD(successClr, listClr, cout << "No elements saved";)
	}
	cout << '\n';
	cin.ignore(CHAR_MAX, '\n');
	cin.clear();
	)
}

void AppHandler::parse(string input, bool comment)
{
	cout << '\n';
	for (size_t i = 0; i < apps.size(); i++)
		for (size_t j = 0; j < apps[i].size(); j++)
			CASEr(input, apps[i][j], !apps[i]; if (comment) cout << "Successfully " << (apps[i].getType() ? "started " : "ran ") << apps[i].getPath() << "\n\n";)
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
	CASEr(getFirstWord(input), "info",   this->Info  ();                            cout << '\n';)
	CASEr(getFirstWord(input), "cls",    system("cls");)
	CASEr(getFirstWord(input), "exit",   exit(0))
	//DEFAULT(cout << "Error! " << input << " is not a valid function\n")
	DEFAULT(error::trw(4, input + " is not a valid function", "", input))
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
	cout << "Successfully started pack\n" << pack.getName() << " {";
	for (size_t i = 0; i < pack.size(); i++)
	{
		parse(pack[i], false);
		cout << "  " << pack[i] << (i + 1 < pack.size() ? ", " : "");
	}
	cout << "\n};\n\n";
}

size_t AppHandler::findAppPosByKeyword(string keyword)
{
	for (size_t i = 0; i < this->apps.size(); i++)
		for (size_t j = 0; j < this->apps[i].size(); j++)
			if (keyword == this->apps[i][j])
				return i;
	return string::npos;
}

size_t AppHandler::findPackPosByKeyword(string keyword)
{
	for (size_t i = 0; i < this->packs.size(); i++)
		if (keyword == this->packs[i].getName())
			return i;
	return string::npos;
}

void AppHandler::Help(string input)
{
	CLROUT(listClr,
		if (input.empty())
			for (size_t i = 0; i < this->hText.size(); i++)
				cout << this->hText[i].keyword << " -\t-\t- " << this->hText[i].description << '\n';
		else
		{
			bool temp = false;
			for (size_t i = 0; i < this->hText.size(); i++)
			{
				if (input == this->hText[i].keyword)
				{
					cout << this->hText[i].keyword << " -\t-\t- " << this->hText[i].description << "\n\n\t" << this->hText[i].extraHelp << '\n';
					temp = true;
					break;
				}
			}
			if (!temp)
				error::trw(2, "Command has no help text!", "help", input);
		}
	)
}

void AppHandler::List(string input)
{
	CLROUT(listClr,
		if (input != "app" and input != "pack" and !input.empty())
			error::trw(2, "Command has no such specifier!", "list", input);
		if (input == "app" or input.empty())
		{
			CLROUTD(listheadClr, listClr,
			cout << "Apps [" << apps.size() << "]:\n";
			)
			for (size_t i = 0; i < apps.size(); i++)
				~apps[i];
		}
		if (input.empty())
			cout << '\n';
		if (input == "pack" or input.empty())
		{
			CLROUTD(listheadClr, listClr,
			cout << "Packs [" << packs.size() << "]:\n";
			)
			for (size_t i = 0; i < packs.size(); i++)
				~packs[i];
		}
	)
}

// add app kw1,kw2|path_cmd[#1_0]
// add pack name|kw1,kw2
void AppHandler::Add(string input)
{
	if (getFirstWord(input) == "app")
	{
		input = getCommand(input, "app");
		if (input.empty())
			error::trw(2, "Command does not take such arguments", "add", "add app " + input);
		apps.push_back(App(input));
			cout << "Created app:\n\t";
			~apps[apps.size() - 1];
	}
	else if (getFirstWord(input) == "pack")
	{
		input = getCommand(input, "pack");
		if (input.empty())
			error::trw(2, "Command does not take such arguments", "add", "add pack " + input);
		packs.push_back(Pack(input));
			cout << "Created pack:\n\t";
			~packs[packs.size() - 1];
	}
	else
		error::trw(2, "Command has no such specifier", "add", "add " + input);
}

void AppHandler::Edit(string input)
{
	if (getFirstWord(input) == "app")
	{
		string newApp = getCommand(input, getFirstWord(input));
		if (newApp.empty())
			error::trw(2, "Command does not take such arguments", "edit", "edit app " + input);
		size_t position = this->findAppPosByKeyword(getFirstWord(newApp));
		if (position == string::npos)
			error::trw(2, "Keyboard position out of range.\nKeyword could not be found.\nKeyword is invalid or there is no such app", "edit", "edit app " + input);
		App oldApp = this->apps[position];
		this->apps[position] = App(getCommand(newApp, getFirstWord(newApp)), oldApp);
			cout << "Edited app.\nFrom -  ";
			~oldApp;
			cout << "To -  ";
			~this->apps[position];
	}
	else if (getFirstWord(input) == "pack")
	{
		string newPack = getCommand(input, getFirstWord(input));
		if (newPack.empty())
			error::trw(2, "Command does not take such arguments", "edit", "edit pack" + input);
		size_t position = this->findPackPosByKeyword(getFirstWord(newPack));
		if (position == string::npos)
			error::trw(2, "Keyboard position out of range.\nKeyword could not be found.\nKeyword is invalid or there is no such pack", "edit", "edit pack " + input);
		Pack oldPack = this->packs[position];
		this->packs[position] = Pack(getCommand(newPack, getFirstWord(newPack)), oldPack);
		cout << "Edited pack.\nFrom -  ";
		~oldPack;
		cout << "To -  ";
		~this->packs[position];
	}
	else
		error::trw(2, "Command has no such specifier", "edit", "edit " + input);
}

void AppHandler::Remove(string input)
{
	if (getFirstWord(input) == "app")
	{
		size_t position = this->findAppPosByKeyword(getCommand(input, getFirstWord(input)));
		if (position == string::npos)
			error::trw(2, "Keyboard position out of range.\nKeyword could not be found.\nKeyword is invalid or there is no such app", "remove", "remove app " + input);
		cout << "Removed app\n\t";
		~this->apps[position];
		this->apps.erase(this->apps.begin() + position);
		//this->apps.erase(this->apps.begin() + this->findPosByKeyword(getCommand(input, "remove")));
	}
	else if (getFirstWord(input) == "pack")
	{
		size_t position = this->findPackPosByKeyword(getCommand(input, getFirstWord(input)));
		if (position == string::npos)
			error::trw(2, "Keyboard position out of range.\nKeyword could not be found.\nKeyword is invalid or there is no such app", "remove", "remove pack " + input);
		cout << "Removed pack\n\t";
		~this->packs[position];
		this->packs.erase(this->packs.begin() + position);
		//this->apps.erase(this->apps.begin() + this->findPosByKeyword(getCommand(input, "remove")));
	}
	else
		error::trw(2, "Command has no such specifier", "remove", "remove " + input);
}

void AppHandler::Save(string input)
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
	else
		error::trw(2, "filepath: " + input, "save", "save " + input);
}

void AppHandler::Load(string input)
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
	else
		error::trw(2, "filepath: " + input, "load", "load " + input);
}

void AppHandler::File(string input)
{
	if (input.empty())
		system(string("start functions.txt").c_str());
	else
		system(string("start " + input).c_str());
}

void AppHandler::Info()
{
	CLROUT(CLR(6),
		cout << "Version: " << version;
		cout << "\nLast update: " << lastupdate;
		cout << "\nMade by: mssevov18\n";
	)

// #########  #########
// #########  #########
// #########  #########
// #########  #########
// 			 
// #########  #########
// #########  #########
// #########  #########
// #########  #########

}
