#pragma once

#include "App.h"

class Pack
{
public:
	Pack();
	Pack(std::string input);

private:
	std::vector<std::string> appKeys;
	std::string name;

public:
	size_t size();
	void remove(size_t index);
	void list();
	std::string getName();
	void erase(size_t index);
	

	void operator() (std::string input);
	void operator~ ();
	std::string operator[] (size_t index);
};

