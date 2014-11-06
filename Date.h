#ifndef DATE_H
#define DATE_H
#include <string>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>

using namespace std;
///interface para funcoes definidas em ctime
class Date
{
public:

	Date();
	Date(time_t seconds);
	Date(int day, int month, int year, int hours, int minutes, int seconds);
	Date(int day, int month, int year);
	///constroi uma data a partir de uma string
	Date(string format);
	///classe de excepcoes associada a data
	class DateExcept
	{
		string description;
	public:
		DateExcept(string description);
		string operator()();
	};
	Date& Date::operator=(const Date& d2);
	///@param data
	///@return numero de segundos correspondente aos parametros
	static int toSeconds(int day, int month, int year, int hours, int minutes, int seconds);
	///@return numero de segundos desde 1 de janeiro de 1970 ate a data
	time_t getTotalSeconds() const;
	///@return dia da data
	int getDay() const;
	///@return mes da data
	int getMonth() const;
	///@return ano da data
	int getYear() const	;
	///@return horas da data
	int getHours() const;
	///@return minutos da data
	int getMinutes() const;
	///@return segundos da data
	int getSeconds() const;
	///@return dia da semana da data
	int getWeekDay() const;
	///@return dia do ano da data
	int getYearDay() const;
	///@return data em forma de string
	string printDate() const;
	///@return data em forma de string, sem horas, minutos nem segundos
	string printDate2() const;
	friend bool operator<(const Date& d1, const Date& d2);
	friend bool operator==(const Date& d1, const Date& d2);
	friend bool operator!=(const Date& d1, const Date& d2);
	friend Date operator+(const Date& d1, const Date& d2);
	friend Date operator-(const Date& d1, const Date& d2);
	friend Date& operator+=(Date& d1, const Date& d2);
	friend Date& operator-=(Date& d1, const Date& d2);
	friend Date operator+(const Date& d1, const int& i);
	friend Date operator-(const Date& d1, const int& i);
	friend Date& operator+=(Date& d1, const int& i);
	friend Date& operator-=(Date& d1, const int& i);

private:
	time_t totalseconds;
};


#endif
