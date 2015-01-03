#ifndef MENU_H
#define MENU_H


#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "Cursor.h"
#include "Project.h"
#include "Client.h"
#include "Collaborator.h"
#include "Task.h"
#include "Date.h"
#include "Application.h"
#include "insertionSort.h"

using namespace std;

class Application;

///@brief 
void menus(int& state, Application& app);

string normalize(const string& s1, const string& s2, int n);

#endif