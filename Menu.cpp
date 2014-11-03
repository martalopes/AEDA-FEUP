#include "Menu.h"
#include <iostream>
#include <ctime>
#include <assert.h>
#include <windows.h>
#include <conio.h>


vector<Menu*> Menu::menus;

Menu* Menu::execute()
{
	cout << name << endl;
	cout << description << endl;
	for (size_t i = 0; i < next.size(); ++i)
		cout << i + 1 << ". " << getMenuPtr(next.at(i))->name << endl;
	int response=-1;
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
//		cout << "MENU:" << endl;
//		cout << "[1] Client " << endl;
//		cout << "[2] Colaborator " << endl;
//		cout << "[3] Manager " << endl;
//		cout << "[4] Admin " << endl;
//		cout << "[5] Go Back " << endl;
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
//usado em vez de endl de modo a contabilizar o numero de '\n' ate ao fim do ecra atual
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

void genericmenu(int &state, Application &app, string name, string text, vector<string> options, vector<int> results)
{
	bool more = true;//falso termina a funcao
	bool change = false; //indica se é preciso voltar imprimir o ecra
	Cursor cursor1(results.size());
	while (more)
	{
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
		cout >> app.getDate().printDate() << "                             ";
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
enum states
{
	EXIT = -1, ESCAPEMENU, MAINMENU1, CLIENTMENU, COLLABORATORMENU, MANAGERMENU,ADMINMENU
};

//void menuProject(int& state, Application& app){
//
//	char c;
//	string nome;
//	do{
//		system("CLS");
//		cout << "View more information? Y-yes, N-no" << endl;
//		c = getch();
//	} while (c != 'Y' && c != 'N');
//	if (c == 'Y')
//	{
//		system("CLS");
//		cout << "\nProject's name? " << endl;
//		cin >> nome;
//		for (size_t i = 0; i < app.getProjects().size(); i++)
//		{
//			if (nome == app.getProjects().at(i)->getName())
//			{
//				cout << "\n" << app.getProjects().at(i)->getName() << endl;
//				cout << " - " << app.getProjects().at(i)->getType();
//				cout << " - " << app.getProjects().at(i)->getClient();
//				cout << " - " << app.getProjects().at(i)->getCost();
//				cout << " - " << app.getProjects().at(i)->getDeadline().printDate();
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
//		cout << "MENU:" << endl;
//		cout << "ID: ";
//		cin >> id;
//		cout << "Password: " << endl;
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
//						cout << "MENU:" << endl;
//						cout << "[1] Creat a new project " << endl;
//						cout << "[2] List of created projects " << endl;
//						cout << "[3] Go Back " << endl;
//						c = getch();
//					} while (c != '1' && c != '2' && c != '3');
//				}
//				else {
//					system("CLS");
//					cout << "Wrong password... " << endl;
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
//						cout << "\n" << Application::projects.at(i)->getName() << endl;
//						cout << " - " << Application::projects.at(i)->getType() << endl;
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
//		cout << "MENU:" << endl;
//		cout << "[1] Client " << endl;
//		cout << "[2] Colaborator " << endl;
//		cout << "[3] Manager " << endl;
//		cout << "[4] Admin " << endl;
//		cout << "[5] Go Back " << endl;
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


void menus(int& state, Application& app)
{
	while (state != EXIT)
	{
		switch (state)
		{
		case MAINMENU1:
			genericmenu(state, app, "", "Please select an Option:", { "Client", "Collaborator", "Manager", "Admin", "Quit" }, { CLIENTMENU, COLLABORATORMENU, MANAGERMENU, ADMINMENU, ESCAPEMENU });
			break;
		case ESCAPEMENU:
			genericmenu(state, app, "", "Are you sure you want to Exit this Application?", { "No", "Yes" }, { MAINMENU, EXIT });
			break;
		case CLIENTMENU:
			
			break;
		case COLLABORATORMENU:

			break;
		default:
			state = EXIT;
			break;
		}
	}
}