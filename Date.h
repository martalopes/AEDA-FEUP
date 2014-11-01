#ifndef DATE_H
#define DATE_H
#include <string>
#include <sstream>
#include <ctime>
#include <stdlib.h>

/*
Class Date é composta:
day, month, year;
hours, minutes, seconds;
A data é das classes mais importantes a ser utilizada pois todas dependem desta
já que tanto tarefas como os projectos estao definidos de acordo com datas.
Para facilitar as comparações de datas definimos o operador menor.
*/

using namespace std;

class Date
{
public:

	Date():totalseconds(time(NULL)),datetime(localtime(&totalseconds)){};
	Date(time_t seconds) :totalseconds(seconds), datetime(localtime(&totalseconds)){};
	Date(int day,int month, int year, int hours, int minutes, int seconds)
	{
		time_t t = time(NULL);
		datetime = localtime(&t);
		datetime->tm_mday = day;
		datetime->tm_mon = month - 1;
		datetime->tm_year= year - 1900;
		datetime->tm_hour = hours;
		datetime->tm_min = minutes;
		datetime->tm_sec = seconds;
		totalseconds = mktime(datetime);
	};
	class DateExcept
	{
		string description;
	public:
		DateExcept(string description) :description(description){};
		string operator()(){ return description; };
	};
	/*static Date AbsoluteDate(int day,int month, int year, int hours, int minutes, int seconds)
	{return Date(day,month, year,hours,minutes, seconds);};*/
	Date& Date::operator=(const Date& d2)
	{
		this->totalseconds = d2.totalseconds;
		time_t seconds = d2.totalseconds;
		datetime = localtime(&this->totalseconds);
		return *this;
	}
	static int toSeconds(int day,int month, int year, int hours, int minutes, int seconds)
	{
		day += 1;
		month += 1;
		year += 1970;
		Date d = Date(day,month, year,hours,minutes, seconds);
		return (int) (d.totalseconds);
	};
	time_t getTotalSeconds() const {return this->totalseconds;};
	int getDay() const		{ return datetime->tm_mday; };
	int getMonth() const	{ return datetime->tm_mon+1; };
	int getYear() const		{ return datetime->tm_year+1900; };
	int getHours() const	{ return datetime->tm_hour; };
	int getMinutes() const	{ return datetime->tm_min; };
	int getSeconds() const	{ return datetime->tm_sec; };
	int getWeekDay() const  { return datetime->tm_wday+1;};
	int getYearDay() const  { return datetime->tm_yday;};
	string printDate() const
	{
		stringstream s;
		s << getDay() << "/" << getMonth()<< "/" << getYear() << " " << getHours() << ":" << getMinutes() << ":" <<getSeconds();
		return s.str();
	};
	//~Date(){free(datetime);};
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
	tm* datetime;
};


#endif
