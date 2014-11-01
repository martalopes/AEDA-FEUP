#include "Menu.h"

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