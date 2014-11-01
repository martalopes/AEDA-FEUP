#ifndef MENU_H
#define MENU_H


#include <vector>
#include <string>
#include <iostream>

#include "Cursor.h"
#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"

using namespace std;

//#define UP = 72;
//#define DOWN = 80;
//#define LEFT = 75;
//#define RIGHT = 77;
//#define ENTER = 13;
//#define SPACE = 32;
//#define BACKSPACE = 8;
//#define ESCAPE = 27;
//
////largura do ecra
//const int WIDTH = 80;
//
////usado para guardar o numero de '\n' ate ao fim do ecra atual
//int end_of_screen = 24;
//int current_color = 7;

enum ids {MAINMENU=1, CLIENTLOGIN, COLLABORATORLOGIN, ADMINLOGIN};

class Menu
{
private:
	int id;
	int previous;
	string name;
	string description;
	vector<int> next;
	vector<string> options;
	Cursor cursor;
	static vector<Menu*> menus;

public:
	bool operator==(const Menu& m2)const{ return id == m2.id; };
	//int getID()const { return id; };
	//Menu(int id, string name) : previous(0){ menus.push_back(this); };
	Menu(int id, string name, string description, int previous, vector<int> next) : id(id), name(name), description(description), previous(previous), next(next){ next.push_back(previous);  menus.push_back(this); };
	//Menu(int previous) : previous(previous){};
	virtual Menu* execute();
	static Menu* getMenuPtr(int id)
	{
		for (size_t i = 0; i < menus.size(); i++)
		if (menus.at(i)->id == id)
			return menus.at(i);
		return NULL;
	};
};


#endif