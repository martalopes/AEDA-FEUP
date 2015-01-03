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
	///@brief constroi a data a partir do numero de segundos a partir de 1/1/1970
	///@param seconds numero de segundos a partir do qual deve ser construida a data
	Date(time_t seconds);
	///@brief construtor com a data a partir do dia, mes, ano, horas, minutos, segundos
	///@param day dia
	///@param month mes
	///@param year ano
	///@param hours horas
	///@param minutes minutos
	///@param seconds segundos
	Date(int day, int month, int year, int hours, int minutes, int seconds);
	///@brief construtor com a data a partir do dia, mes, ano
	///@param day dia
	///@param month mes
	///@param year ano
	Date(int day, int month, int year);
	///@ brief constroi uma data a partir de uma string
	///@param format string contendo a data a construir
	Date(string format);
	///classe de excepcoes associada a data
	class DateExcept
	{
		///descricao da excecao
		string description;
	public:
		///@brief construtor da class DateExcept
		///@param description descricao
		DateExcept(string description);
		///@brief retorna descricao da excepcao
		///@return descricao
		string operator()();
	};
	Date& Date::operator=(const Date& d2);
	///@brief converte a data a segundos
	///@param day dia
	///@param month mes
	///@param year ano
	///@param hours horas
	///@param minutes minutos
	///@param seconds segundos
	///@return numero de segundos correspondente aos parametros
	static int toSeconds(int day, int month, int year, int hours, int minutes, int seconds);
	///@brief retorna numero de segundos desde 1 de janeiro de 1970 ate a data
	///@return numero de segundos desde 1 de janeiro de 1970 ate a data
	time_t getTotalSeconds() const;
	///@brief retorna dia da data
	///@return dia da data
	int getDay() const;
	///@brief retorna mes da data 
	///@return mes da data
	int getMonth() const;
	///@brief retorna ano da data
	///@return ano da data
	int getYear() const	;
	///@brief retorna horas da data
	///@return horas da data
	int getHours() const;
	///@brief retorna minutos da data
	///@return minutos da data
	int getMinutes() const;
	///@brief retorna segundos da data
	///@return segundos da data
	int getSeconds() const;
	///@brief retorna dia da semana da data
	///@return dia da semana da data
	int getWeekDay() const;
	///@brief retorna dia do ano da data
	///@return dia do ano da data
	int getYearDay() const;
	///@brief retorna data em forma de string
	///@return data em forma de string
	string printDate() const;
	///@brief data em forma de string, sem horas, minutos nem segundos
	///@return data em forma de string, sem horas, minutos nem segundos
	string printDate2() const;
	///@brief overload do operador menor
	friend bool operator<(const Date& d1, const Date& d2);
	///@brief overload do operador de igualdade
	friend bool operator==(const Date& d1, const Date& d2);
	///@brief overload do operador desigualdade 
	friend bool operator!=(const Date& d1, const Date& d2);
	///@brief overload do operador de adicao
	friend Date operator+(const Date& d1, const Date& d2);
	///@brief overload do operador de subtraccao
	friend Date operator-(const Date& d1, const Date& d2);
	///@brief overload do operador soma 
	friend Date& operator+=(Date& d1, const Date& d2);
	///@brief overload do operador diferenca
	friend Date& operator-=(Date& d1, const Date& d2);
	///@brief overload do operador adicao de inteiro
	friend Date operator+(const Date& d1, const int& i);
	///@brief overload do operador subtraccao de inteiro
	friend Date operator-(const Date& d1, const int& i);
	///@brief overload do operador soma de inteiro
	friend Date& operator+=(Date& d1, const int& i);
	///@brief overload do operador diferenca de inteiro
	friend Date& operator-=(Date& d1, const int& i);

private:
	time_t totalseconds;
};


#endif
