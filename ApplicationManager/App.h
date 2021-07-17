#pragma once

#include <iostream>
#include <vector>
#include <string>

void checkPath(std::string& path);

std::string checkKey(std::string key);

class App
{
public:
	App();
	App(std::string input, std::string path, bool isProgram, bool ignoreCheck = false);
	App(std::string input, bool ignoreCheck = false);
	App(std::string input, App oldApp, bool ignoreCheck = false);

private:
	std::vector<std::string> keywords;
	std::string path;
	bool isProgram;

public:
	//void		operator() (std::string input, std::string path, bool isProgram, bool ignoreCheck = false);		// + Change data
	//void		operator() (std::string input, bool ignoreCheck = false);	// -  -  -  -  -  -  -  -  -  -  -  // |
	//void		operator() (std::string input, App oldApp, bool ignoreCheck = false);	// -  -  -  -  -  -  -  // /
	void		operator~();	//-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // - Print
	void		operator! ();	//-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // - Use
	std::string operator[] (size_t index);	//-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // - Get keyword by indedx
	size_t		size();		// -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // - Get keyword vector size
	std::string getPath();	// -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // - Get the application path
	bool		getType();	// -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  // - Get the application type
	std::vector<std::string> getKeys();
};