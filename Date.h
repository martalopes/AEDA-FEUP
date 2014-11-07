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
	///data atual
	Date();
	///constroi a data a partir do numero de segundos a partir de 1/1/1970
<<<<<<< HEAD
	///@param seconds numero de segundos a partir do qual deve ser construida a data
	Date(time_t seconds);
	///construtor com a data a partir do dia, mes, ano, horas, minutos, segundos
	///@param day dia
	///@param month mes
	///@param year ano
	///@param hours horas
	///@param minutes minutos
	///@param seconds segundos
	Date(int day, int month, int year, int hours, int minutes, int seconds);
	///construtor com a data a partir do dia, mes, ano
	///@param day dia
	///@param month mes
	///@param year ano
	Date(int day, int month, int year);
	///constroi uma data a partir de uma string
	///@param format string contendo a data a construir
=======
	///@param numero de segundos a partir do qual deve ser construida a data
	Date(time_t seconds);
	///construtor com a data a partir do dia, mes, ano, horas, minutos, segundos
	///@param dia, mes, ano, horas, minutos, segundos
	Date(int day, int month, int year, int hours, int minutes, int seconds);
	///construtor com a data a partir do dia, mes, ano
	///@param dia, mes, ano, horas
	Date(int day, int month, int year);
	///constroi uma data a partir de uma string
	///@param string contendo a data a construir
>>>>>>> origin/master
	Date(string format);
	///classe de excepcoes associada a data
	class DateExcept
	{
		///descricao da excecao
		string description;
	public:
		///construtor
<<<<<<< HEAD
		///@param description descricao
=======
		///@param descricao
>>>>>>> origin/master
		DateExcept(string description);
		///@return descricao
		string operator()();
	};
	Date& Date::operator=(const Date& d2);
<<<<<<< HEAD
	///@param day dia
	///@param month mes
	///@param year ano
	///@param hours horas
	///@param minutes minutos
	///@param seconds segundos
=======
	///@param data
>>>>>>> origin/master
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
