#include <iostream>
#include <string>

using namespace std;
int main(){
	string name;
	cout << "Qual é o teu nome? ";
	getline(cin,name);
	cout << "ola ..." << name << endl;
	system("pause");
	return 0;
}