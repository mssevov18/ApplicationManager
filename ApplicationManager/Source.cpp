#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "windows.h"

#include "App.h"
#include "AppHandler.h"

using namespace std;

int main()
{
	//vector<APP> apps;
	//apps.push_back(APP("cmd|cmd.exe"));
	//~apps[0];
	//!apps[0];
	//save(apps, "test.txt");
	AppHandler hndl;
	//hndl.apps.push_back(App("cls,CLS|cls#0"));
	//hndl.apps.push_back(App("exit,Exit|exit#0"));
	//hndl.apps.push_back(App("help,Help|help#0"));
	//hndl.apps.push_back(App("cmd,CMD|cmd#1"));
	//hndl.apps.push_back(App("powershell,POWERSHELL,PowerShell,Powershell,ps,PS|powershell#1"));
	//hndl.apps.push_back(App("explorer,Explorer,ii .,II .,Invoke-Item .,invoke-item .|explorer#1"));
	//hndl.apps.push_back(App("edge,Edge,msedge,msEdge|C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe#1"));
	//hndl.apps.push_back(App("chrome,Chrome|C:/Program Files (x86)/Google/Chrome/Application/chrome.exe#1"));
	string input = "";
	while (input != "exit")
	{
		cout << "AppManager> ";
		getline(cin, input);
		hndl.parse(input);
	}
}