#ifndef DATE_H
#define DATE_H
#include <string>
#include <sstream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>

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

	Date() :totalseconds(time(NULL))/*,datetime(localtime(&totalseconds))*/{ if (totalseconds == -1) throw DateExcept("Invalid Date"); };
	Date(time_t seconds) :totalseconds(seconds)/*, datetime(localtime(&totalseconds))*/{ if (totalseconds == -1) throw DateExcept("Invalid Date"); };
	Date(int day,int month, int year, int hours, int minutes, int seconds)
	{
		time_t t = time(NULL);
		tm* datetime = localtime(&t);
		datetime->tm_mday = day;
		datetime->tm_mon = month - 1;
		datetime->tm_year= year - 1900;
		datetime->tm_hour = hours;
		datetime->tm_min = minutes;
		datetime->tm_sec = seconds;
		totalseconds = mktime(datetime);
		if (totalseconds == -1) throw DateExcept("Invalid Date");
	};
	Date(int day, int month, int year) : Date(day, month, year, 0, 0, 0)
	{};
	Date(string format)
	{ 
		int notdigitcount = 0;
		for (size_t n = 0; n < format.length(); n++)
		{
			if (!isdigit(format[n]))
				notdigitcount++;
		}
		if(notdigitcount< 2)
			throw DateExcept("Invalid Date");
		int day, month, year;
		string sday, smonth, syear;
		size_t i = 0;
		while (isdigit(format[i]))
		{
			sday += format[i];
			i++;
		}
		while (!isdigit(format[i]))
		{
			i++;
		}
		while (isdigit(format[i]))
		{
			smonth += format[i];
			i++;
		}
		while (!isdigit(format[i]))
		{
			i++;
		}
		while (isdigit(format[i]))
		{
			syear += format[i];
			i++;
		}
		stringstream s(sday);
		stringstream s2(smonth);
		stringstream s3(syear);
		s >> day;
		s2 >> month;
		s3 >> year;
		*this = Date(day, month, year); 
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
		/*time_t seconds = d2.totalseconds;
		datetime = localtime(&this->totalseconds);*/
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
	int getDay() const		{ tm* datetime = localtime(&totalseconds); return datetime->tm_mday; };
	int getMonth() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_mon + 1; };
	int getYear() const		{ tm* datetime = localtime(&totalseconds); return datetime->tm_year + 1900; };
	int getHours() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_hour; };
	int getMinutes() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_min; };
	int getSeconds() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_sec; };
	int getWeekDay() const  { tm* datetime = localtime(&totalseconds); return datetime->tm_wday + 1; };
	int getYearDay() const  { tm* datetime = localtime(&totalseconds); return datetime->tm_yday; };
	string printDate() const
	{
		stringstream s;
		s << std::setfill('0') << std::setw(2) << getDay() << "/" << std::setfill('0') << std::setw(2) << getMonth() << "/" << std::setfill('0') << std::setw(4) << getYear() << " " << std::setfill('0') << std::setw(2) << getHours() << ":" << std::setfill('0') << std::setw(2) << getMinutes() << ":" << std::setfill('0') << std::setw(2) << getSeconds();
		return s.str();
	};
	string printDate2() const
	{
		stringstream s;
		s << std::setfill('0') << std::setw(2) << getDay() << "/" << std::setfill('0') << std::setw(2) << getMonth() << "/" << std::setfill('0') << std::setw(2) << getYear();
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
};


#endif
