#ifndef DATE_H
#define DATE_H
#include <string>
#include <sstream>

using namespace std;

class Date
{
public:
	Date(){};
	Date(int day, int month, int year, int hours = 0, int minutes = 0, int seconds = 0) :day(day), month(month), year(year), hours(hours), minutes(minutes), seconds(seconds){};
	bool operator<(const Date& d2) const;
	int getDay() const		{ return this->day; };
	int getMonth() const	{ return this->month; };
	int getYear() const		{ return this->year; };
	int getHours() const	{ return this->hours; };
	int getMinutes() const	{ return this->minutes; };
	int getSeconds() const	{ return this->seconds; };
	string printDate() const;
	string printTime() const;
	void setDay(int day) { this->day = day; };
	void setMonth(int month) { this->month= month; };
	void setYear(int year) { this->year = year; };
	void setHours(int hours) { this->hours = hours; };
	void setMinutes(int minutes) { this->minutes = minutes; };
	void setSeconds(int seconds) { this->seconds = seconds; };

private:
	static bool isLeapYear(int year) 
	{ 
		if (year % 4 != 0)
			return false; 
		if (year % 100 != 0)
			return true; 
		if (year % 400 != 0)
			return false; 
		return true; 
	};
	static int daysInaMonth(int month, int year) 
	{
		if (month < 0 || month >12)
			throw 1; //mudar para Dateexception
		if (month == 2)
		if (isLeapYear(year))
			return 29;
		else return 28;
		if (month < 8){
		if (month % 2 == 0)
			return 30;
		else return 31;
		}
		else if (month % 2 == 0)
				return 31;
		else return 30;
	};
	int day, month, year;
	int hours, minutes, seconds;
};

#endif
