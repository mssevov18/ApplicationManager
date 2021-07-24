#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "App.h"
#include "Pack.h"

struct helpText
{
	helpText();
	helpText(std::string newKw, std::string newDs, std::string newEh);
	helpText(std::string input);

	std::string keyword;
	std::string description;
	std::string extraHelp;
};

//TODO Modify command arguments, so they are used in a cmd/ps style
//instead of: add pack packName|keyword1,keyword2...
//         -> add -p packName|keyword1,keyword2...
//instead of: list pack/app/""
//         -> list -p/-a/-g
//instead of: help list
//         -> list -?


//TODO
//Check if add app input has '|' -> err if not
//
//Add remove all apps / packs

class AppHandler
{
public:
	AppHandler();
	AppHandler(int argc = 1);
	~AppHandler();

private:
	std::vector<int> aPathWidth;
	std::vector<int> aKeyWidth;
	std::vector<int> pNameWidth;
	std::vector<App> apps;
	std::vector<Pack> packs;
public:
	std::vector<helpText> hText;

	void parse(std::string input, bool comment = true);

	void packOpen(Pack pack);

	size_t findAppPosByKeyword(std::string keyword);
	size_t findPackPosByKeyword(std::string keyword);

	void Help  (std::string input);
	void List  (std::string input);
	void Add   (std::string input);
	void Edit  (std::string input);
	void Remove(std::string input);
	void Save  (std::string input = "");
	void Load  (std::string input = "");
	void File  (std::string input);
	void Info  ();

	void push_back(App newApp);
	void push_back(Pack newPack);

private:
	void generateHelpText();
	void updateAppW();
	void updatePackW();
};

