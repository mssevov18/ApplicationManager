#pragma once

#include "App.h"

class Pack
{
public:
	Pack();
	Pack(std::string input);
	Pack(std::string input, Pack oldPack);

private:
	std::vector<std::string> appKeys;
	std::string name;

public:
	size_t size();
	std::string getName();
	std::vector<std::string> getKeys();
	

	void operator() (int width = 1);
	void operator~ ();
	std::string operator[] (size_t index);
};

