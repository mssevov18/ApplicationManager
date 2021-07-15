#pragma once

#include "App.h"

class AppHandler
{
public:
	AppHandler();
private:
public:
	std::vector<App> apps;

	void parse(static std::string& input);

	void print();
	void load(static std::string filepath);
	void save(static std::string filepath);
};

