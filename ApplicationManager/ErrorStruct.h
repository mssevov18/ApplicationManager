#pragma once

#include <iostream>

#include "AppHandler.h"

struct error
{
	error();
	error(int code, std::string msg = "", std::string src = "", std::string uin = "");

	static void trw(int code, std::string msg = "", std::string src = "", std::string uin = "");
	static void trw(error err);

	int code;
	std::string msg;
	std::string src;
	std::string uin;

	void pms(std::string header = "");

	void getHelp(std::vector<helpText>& hText);
};


void checkPath(std::string& path);

std::string checkKey(std::string key);