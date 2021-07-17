#pragma once

#include <iostream>
#include <vector>

#include "AppHandler.h"
#include "TextStyles.h"

struct error
{
	error()
	{
		this->code = 0;
		this->msg  = "";
		this->src  = "";
		this->uin = "";
	}
	error(int code, std::string msg = "", std::string src = "", std::string uin = "")
	{
		this->code = code;
		this->msg  = msg;
		this->src  = src;
		this->uin = uin;
	}

	static void trw(int code, std::string msg = "", std::string src = "", std::string uin = "")
	{
		throw error(code, msg, src, uin);
	}
	static void trw(error err)
	{
		throw err;
	}

	int code;
	std::string msg;
	std::string src;
	std::string uin;

	void pms(std::string header = "")
	{
		//std::cout << '\a';
		if (!header.empty())
			std::cout << header << '\n';
		if (!msg.empty())
			std::cout << msg << '\n';
		std::cout << '\n';
	}

	void getHelp(std::vector<helpText>& hText)
	{
		std::cout << "Input: " << uin;
		for (size_t i = 0; i < hText.size(); i++)
			if (src == hText[i].keyword)
				std::cout << '\n' << hText[i].keyword << " - " << hText[i].description << "\n\n\t" << hText[i].extraHelp << "\n\n";
	}
};