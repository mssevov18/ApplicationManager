#pragma once

#include "App.h"
#include "Pack.h"

struct helpText
{
	helpText();
	helpText(std::string newKw, std::string newDs, std::string newEh);

	std::string keyword;
	std::string description;
	std::string extraHelp;
};

//packStart|edge,spotify,explorer
/*open() {
* for(appkey in appkeys)
*	parse(appkey);
* }
*/


struct Package
{
	Package()
	{

	}
	Package(std::string input)
	{

	}

	std::vector<std::string> appKeys;
	std::string name;

	void remove(size_t index)
	{

	}
	void list()
	{
		for (size_t i = 0; i < appKeys.size(); i++)
			std::cout << appKeys[i] << ' ';
		std::cout << '\n';
	}
	void operator() (std::string input)
	{

	}
	void operator~ ()
	{
		std::cout << name << " | ";
		for (size_t i = 0; i < appKeys.size(); i++)
			std::cout << appKeys[i] << ", ";
		std::cout << "\b\b \n";
	}
	void operator! ()
	{

	}
};

//Todo implement packs!

class AppHandler
{
public:
	AppHandler();
private:
	std::vector<helpText> hText;
public:
	std::vector<App> apps;
	std::vector<Pack> packs;

	void parse(static std::string input);

	void packOpen(Pack pack);

	size_t findAppPosByKeyword(static std::string keyword);
	size_t findPackPosByKeyword(static std::string keyword);

	void Help(static std::string input);
	void List(static std::string input);
	void Add(static std::string input);
	void Edit(static std::string input);
	void Remove(static std::string input);
	void Save(static std::string input);
	void Load(static std::string input);
	void File(static std::string input);
};

