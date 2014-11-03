#include "Menu.h"
#include <iostream>
#include <ctime>
#include <assert.h>
#include <windows.h>
#include <conio.h>
#include <algorithm>


vector<Menu*> Menu::menus;

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int ENTER = 13;
const int SPACE = 32;
const int BACKSPACE = 8;
const int ESCAPE = 27;

//largura do ecra
const int WIDTH = 80;

//usado para guardar o numero de '\n' ate ao fim do ecra atual
int end_of_screen = 24;
int current_color = 7;



void ClearScreen() /* http://www.cplusplus.com/articles/4z18T05o/ */
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}/* http://www.cplusplus.com/articles/4z18T05o/ */

//centra uma string
ostream& operator>>(ostream& out, string s)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	int num = (WIDTH - s.length()) / 2;
	for (int i = num; i > 0; i--)
	{
		out << ' ';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current_color);
	out << s;
	return out;
}
//usado em vez de el de modo a contabilizar o numero de '\n' ate ao fim do ecra atual
ostream& el(ostream& out)
{
	end_of_screen--;
	return out << endl;
}
//move o cursor ate ao fim do ecra e restaura end_of_screen
void go_end_of_screen()
{
	while (end_of_screen > 0)
	{
		cout << el;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	end_of_screen = 24;
}
void changecolor(string color)
{
	if (color == "white")
		current_color = 7;
	else if (color == "black")
		current_color = 112;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), current_color);
}

Menu* Menu::execute()
{
	cout << name << el;
	cout << description << el;
	for (size_t i = 0; i < next.size(); ++i)
		cout << i + 1 << ". " << getMenuPtr(next.at(i))->name << el;
	int response = -1;
	do
	{
		while (!(cin >> response))
		{
			cin.clear();
			cin.ignore();
		}
	} while (response < 0 || response >= next.size());
	return getMenuPtr(next.at(response));
}

//void menu(){
//	
//	char c;
//	do {
//		system("CLS");
//		
//		cout << "MENU:" << el;
//		cout << "[1] Client " << el;
//		cout << "[2] Colaborator " << el;
//		cout << "[3] Manager " << el;
//		cout << "[4] Admin " << el;
//		cout << "[5] Go Back " << el;
//		cin >> c;
//	} while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5');
//
//	if (c == '1')
//		
//	if (c == '2')
//
//	if (c == '3')
//
//	if (c == '4')
//
//	if (c == '5')
//		menu();
//}

//


//void genericmenu(int &state, Application &app, string name, string text, vector<string> options, vector<int> results)
//{
//	bool more = true;//falso termina a funcao
//	cout >> app.getDate().printDate2() << el;
//	int input;
//	while (more)
//	{
//		system("CLS");
//		cout <<  app.getDate().printDate2()<<el;
//		cout <<  name << el  << text << el;
//		for (int i = 0; i < options.size(); i++)
//		 cout << "["<< i+1 << "] - " << options[i] << el;
//		do
//		{
//
//		} while ()
//	}
//}
void genericmenu(int &state, Application &app, string name, string text, vector<string> options, vector<int> results)
{
	bool more = true;//falso termina a funcao
	bool change = false; //indica se é preciso voltar imprimir o ecra
	Cursor cursor1(results.size() - 1);
	while (more)
	{
		go_end_of_screen();
		ClearScreen();
		change = false;
		cout << el >> name << el << el >> text << el << el << el << el;
		if (options.size() < 5)
			cout << el;
		if (options.size() < 4)
			cout << el;
		if (options.size() < 3)
			cout << el << el;
		for (int i = 0; i < options.size(); i++)
		if (cursor1.getPosition() == i)
		{
			changecolor("black");
			cout >> "> " + options[i] << el << el << el;
			changecolor("white");
		}
		else cout >> options[i] << el << el << el;
		go_end_of_screen();
		cout >> app.getDate().printDate2() << "                                  ";
		while (!change)
		{
			char input = _getch();
			if (input == UP || input == LEFT)
				change = cursor1.dec();
			else if (input == DOWN || input == RIGHT)
				change = cursor1.inc();
			else if (input == ESCAPE || input == BACKSPACE)
			{
				change = true;
				more = false;
				state = results[results.size() - 1];
			}
			else if (input == ENTER || input == SPACE)
			{
				change = true;
				more = false;
				state = results[cursor1.getPosition()];
			}
		}
		ClearScreen();
	}
}


//void menuProject(int& state, Application& app){
//
//	char c;
//	string nome;
//	do{
//		system("CLS");
//		cout << "View more information? Y-yes, N-no" << el;
//		c = getch();
//	} while (c != 'Y' && c != 'N');
//	if (c == 'Y')
//	{
//		system("CLS");
//		cout << "\nProject's name? " << el;
//		cin >> nome;
//		for (size_t i = 0; i < app.getProjects().size(); i++)
//		{
//			if (nome == app.getProjects().at(i)->getName())
//			{
//				cout << "\n" << app.getProjects().at(i)->getName() << el;
//				cout << " - " << app.getProjects().at(i)->getType();
//				cout << " - " << app.getProjects().at(i)->getClient();
//				cout << " - " << app.getProjects().at(i)->getCost();
//				cout << " - " << app.getProjects().at(i)->getDeadline().printDate2();
//
//			}
//		}
//
//	}
//	if (c == 'N')
//		return;
//
//}
//
//void menuClient(){
//	int id;
//	string password;
//	char c;
//
//	while (true){
//		system("CLS");
//		cout << "MENU:" << el;
//		cout << "ID: ";
//		cin >> id;
//		cout << "Password: " << el;
//		cin >> password;
//
//
//		for (size_t i = 0; i < Application::clients.size(); i++)
//		{
//			if (id == Application::clients.at(i)->getID())
//			{
//				if (password == Application::clients.at(i)->getPassword()){
//					do{
//						system("CLS");
//						cout << "MENU:" << el;
//						cout << "[1] Creat a new project " << el;
//						cout << "[2] List of created projects " << el;
//						cout << "[3] Go Back " << el;
//						c = getch();
//					} while (c != '1' && c != '2' && c != '3');
//				}
//				else {
//					system("CLS");
//					cout << "Wrong password... " << el;
//					return;
//				}
//			}
//
//		}
//
//		if (c == '1')
//		{
//			string name;
//			string type;
//			int day, month, year, hours, minutes, seconds;
//
//			system("CLS");
//			cout << "\nName: ";
//			cin >> name;
//			cout << "\nType: ";
//			cin >> type;
//			cout << "\nDeadline: \nDay ";
//			cin >> day;
//			cout << "\nMonth ";
//			cin >> month;
//			cout << "\nYear ";
//			cin >> year;
//			cout << "\nHours ";
//			cin >> hours;
//			cout << "\nMinutes ";
//			cin >> minutes;
//			cout << "\nSeconds ";
//			cin >> seconds;
//
//			Date deadline(day, month, year, hours, minutes, seconds);
//			Project* p = new Project(name, type, deadline, 0);
//			Application::addProject(p);
//
//			return;
//		}
//		if (c == '2')
//		{
//			system("CLS");
//			for (size_t i = 0; i < Application::clients.size(); i++)
//			{
//				if (id == Application::clients.at(i)->getID())
//				{
//					for (size_t i = 0; i < projects.size(); i++)
//					{
//						cout << "\n" << Application::projects.at(i)->getName() << el;
//						cout << " - " << Application::projects.at(i)->getType() << el;
//					}
//				}
//			}
//
//			return;
//		}
//		if (c == '3')
//			menu();
//	}
//}
//
//void menu(){
//	system("CLS");
//	char c;
//	do {
//		//gotoXY("MENU:", 1);
//		cout << "MENU:" << el;
//		cout << "[1] Client " << el;
//		cout << "[2] Colaborator " << el;
//		cout << "[3] Manager " << el;
//		cout << "[4] Admin " << el;
//		cout << "[5] Go Back " << el;
//
//	} while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5');
//
//	if (c == '1')
//
//	if (c == '2')
//
//	if (c == '3')
//
//	if (c == '4')
//
//	if (c == '5')
//		menu();
//
//}
enum states
{
	EXIT = -1, ESCAPEMENU, MAINMENU1, CLIENTLOGINMENU, COLPROJBYDATE, COLPROJBYTYPE, COLPROJBYNAME, VIEWPROJECTINFO, COLLABORATORLOGINMENU, PERSONALINFOMENU, COLLABORATORMENU, MANAGERLOGINMENU, ADMINLOGINMENU, CLIENTMENU, NEWPROJECTMENU, PROJECTLISTMENU
};
static Client* currentclient = NULL;
static Project* currentproject = NULL;
static Task* currenttask = NULL;
static Collaborator* currentcollaborator = NULL;

void createprojectmenu(int& state, Application& app)
{
	string name;
	string type;
	string deadline;
	go_end_of_screen();
	ClearScreen();
	//system("CLS");
	cout << el << el >> "Please enter Project name" << el << el << el;
	cout << "                   >  ";
	getline(cin, name);
	if (name == "")
	{
		state = CLIENTMENU; return;
	}
	cout << el << el;
	cout >> "Please enter Project type" << el << el << el;
	cout << "                   >  ";
	getline(cin, type);
	if (type == "")
	{
		state = CLIENTMENU; return;
	}
	cout << el << el;
	cout >> "Please enter the deadline of the project (dd/mm/yyyy)" << el << el << el;
	cout << "                   >  ";
	getline(cin, deadline);
	if (type == "")
	{
		state = CLIENTMENU; return;
	}
	Date d1;
	try{ d1 = Date(deadline); }
	catch (Date::DateExcept& e)
	{
		cout << el << el >> "Invalid Date";
		cin.get();
		return;
	}
	Project* p = new Project(name, type, d1, 0);
	app.addProject(p);
	p->setClient(currentclient);
	state = CLIENTMENU;
}

void clientlogin(int& state, Application& app)
{
	string ID;
	string password;
	int id;
	do
	{
		system("CLS");
		cout << el << el >> "Please enter Client ID" << el << el << el;
		cout << "                   >  ";
		getline(cin, ID);
		if (ID == "")
		{
			state = MAINMENU1; return;
		}
		stringstream s;
		s << ID;
		s >> id;
	} while ((currentclient = Application::getClientPtr(id)) == NULL);
	do
	{
		system("CLS");
		cout << el << el >> "Please enter Client ID" << el << el << el;
		cout << "                   >  " << currentclient->getID();
		cout << el << el >> "Please enter password" << el << el << el;
		cout << "                   >  ";
		getline(cin, password);
		if (password == "")
			return;
	} while (!currentclient->verifyPassword(password));
	state = CLIENTMENU;
}

void collaboratorlogin(int& state, Application& app)
{
	string ID;
	string password;
	int id;
	do
	{
		system("CLS");
		cout << el << el >> "Please enter Collaborator ID" << el << el << el;
		cout << "                   >  ";
		getline(cin, ID);
		if (ID == "")
		{
			state = MAINMENU1; return;
		}
		stringstream s;
		s << ID;
		s >> id;
	} while ((currentcollaborator = Application::getCollaboratorPtr(id)) == NULL);
	do
	{
		system("CLS");
		cout << el << el >> "Please enter Collaborator ID" << el << el << el;
		cout << "                   >  " << currentcollaborator->getID();
		cout << el << el >> "Please enter password" << el << el << el;
		cout << "                   >  ";
		getline(cin, password);
		if (password == "")
			return;
	} while (!currentcollaborator->verifyPassword(password));
	state = COLLABORATORMENU;
}

void personalinfo(int& state, Application& app)
{
	system("CLS");
	cout << el << el;
	cout << el << el >> "Max Weekly Hours: " + to_string(currentcollaborator->getMaxWeeklyHours())<< el;
	cout << el << el >> "Working Hours: " + to_string(currentcollaborator->getWorkingHours()) << el;
	cout << el << el >> "Cost: " + to_string(currentcollaborator->getCost()) << el;
	cin.get();
	state = COLLABORATORMENU;
}

void colprojdate(int& state, Application& app)
{
	vector <Project *> pdate;

	for (size_t i = 0; i < currentcollaborator->getProjects().size(); i++)
	{
		pdate.push_back(currentcollaborator->getProjects()[i]);
	}

	sort(pdate.begin(), pdate.end(), Project::ProjectComparatorDeadline());

	for (size_t i = 0; i < pdate.size(); i++)
	{
		cout << i + 1 << " - " << "Nome: " << pdate[i]->getName() << " | " << "Tipo: " << pdate[i]->getType() << " | " << "Prazo: " << pdate[i]->getDeadline().printDate2() << el;
	}
	cin.get();
	state = COLLABORATORMENU;
}

void colprojtype(int& state, Application& app)
{
	vector <Project *> ptype;

	for (size_t i = 0; i < currentcollaborator->getProjects().size(); i++)
	{
		ptype.push_back(currentcollaborator->getProjects()[i]);
	}

	sort(ptype.begin(), ptype.end(), Project::ProjectComparatorType());

	for (size_t i = 0; i < ptype.size(); i++)
	{
		cout << i + 1 << " - " << "Nome: " << ptype[i]->getName() << " | " << "Tipo: " << ptype[i]->getType() << " | " << "Prazo: " << ptype[i]->getDeadline().printDate2() << el;
	}
	cin.get();
	state = COLLABORATORMENU;
}

void colprojname(int& state, Application& app)
{
	system("CLS");
	vector <Project *> pname;

	for (size_t i = 0; i < currentcollaborator->getProjects().size(); i++)
	{
		pname.push_back(currentcollaborator->getProjects()[i]);
	}

	sort(pname.begin(), pname.end(), Project::ProjectComparatorAlphabetic());

	for (size_t i = 0; i < pname.size(); i++)
	{
		cout << i + 1 << " - " << "Nome: " << pname[i]->getName() << " | " << "Tipo: " << pname[i]->getType() << " | " << "Prazo: " << pname[i]->getDeadline().printDate2()<< el;
	}
	cin.get();
	state = COLLABORATORMENU; 
}


void menus(int& state, Application& app)
{
	while (state != EXIT)
	{
		switch (state)
		{
		case MAINMENU1:
			genericmenu(state, app, "", "Please select an Option:", { "Client Login", "Collaborator Login", "Manager Login", "Admin Login", "Quit" }, { CLIENTLOGINMENU, COLLABORATORLOGINMENU, MANAGERLOGINMENU, ADMINLOGINMENU, ESCAPEMENU });
			break;
		case ESCAPEMENU:
			genericmenu(state, app, "", "Are you sure you want to Exit this Application?", { "No", "Yes" }, { MAINMENU1, EXIT });
			break;
		case CLIENTLOGINMENU:
			clientlogin(state, app);
			break;
		case CLIENTMENU:
			genericmenu(state, app, "", "Please select an option:", { "Create new Project", "List of Projects", "Go Back" }, { NEWPROJECTMENU, PROJECTLISTMENU, MAINMENU1 });
			break;
		case COLLABORATORLOGINMENU:
			collaboratorlogin(state, app);
			break;
		case COLLABORATORMENU:
			genericmenu(state, app, "", "Please select an option:", { "View personal information", "View Project information", "Go Back" }, {PERSONALINFOMENU, VIEWPROJECTINFO, MAINMENU1 });
			break;		
		case PERSONALINFOMENU:
			personalinfo(state, app);
			break;
		case VIEWPROJECTINFO:
			genericmenu(state, app, "", "Please select an option:", { "List of projects by date", "List of projects by type", "List of projects by name", "Go Back" }, { COLPROJBYDATE, COLPROJBYTYPE, COLPROJBYNAME, MAINMENU1 });
			break;
		case COLPROJBYDATE:
			colprojdate(state, app);
			break;
		case COLPROJBYTYPE:
			colprojtype(state, app);
			break;
		case COLPROJBYNAME:
			colprojname(state, app);
			break;
		case NEWPROJECTMENU:
			createprojectmenu(state, app);
			break;		
		default:
			state = EXIT;
			break;
		}
	}
}