
#include "Date.h"


using namespace std;
bool operator<(const Date& d1, const Date& d2){ return d1.totalseconds < d2.totalseconds; }
bool operator==(const Date& d1, const Date& d2) { return d1.totalseconds == d2.totalseconds; }
bool operator!=(const Date& d1, const Date& d2){ return !(d1 == d2); }
Date operator+(const Date& d1, const Date& d2){ return Date(d1.totalseconds + d2.totalseconds); }
Date operator-(const Date& d1, const Date& d2){ if (d1.totalseconds < d2.totalseconds)throw Date::DateExcept("Invalid Date subtraction"); return Date(d1.totalseconds - d2.totalseconds); }
Date& operator+=(Date& d1, const Date& d2) { d1 = d1 + d2; return d1; }
Date& operator-=(Date& d1, const Date& d2) { d1 = d1 - d2; return d1; }

Date operator+(const Date& d1, const int& i)
{
	return Date(d1.totalseconds + i);
}
Date operator-(const Date& d1, const int& i){ if (d1.totalseconds < i) throw Date::DateExcept("Invalid Date subtraction"); return Date(d1.totalseconds - i); }
Date& operator+=(Date& d1, const int& i) { d1 = d1 + i; return d1; }
Date& operator-=(Date& d1, const int& i) { d1 = d1 - i; return d1; }

Date::Date() :totalseconds(time(NULL)){ if (totalseconds == -1) throw DateExcept("Invalid Date"); }
Date::Date(time_t seconds) :totalseconds(seconds){ if (totalseconds == -1) throw DateExcept("Invalid Date"); }
Date::Date(int day, int month, int year, int hours, int minutes, int seconds)
{
	time_t t = time(NULL);
	tm* datetime = localtime(&t);
	datetime->tm_mday = day;
	datetime->tm_mon = month - 1;
	datetime->tm_year = year - 1900;
	datetime->tm_hour = hours;
	datetime->tm_min = minutes;
	datetime->tm_sec = seconds;
	totalseconds = mktime(datetime);
	if (totalseconds == -1) throw DateExcept("Invalid Date");
}
Date::Date(int day, int month, int year) : Date(day, month, year, 0, 0, 0)
{}
Date::Date(string format)
{
	int notdigitcount = 0;
	for (size_t n = 0; n < format.length(); n++)
	{
		if (!isdigit(format[n]) && !iswspace(format[n]))
			notdigitcount++;
	}
	if (notdigitcount != 2)
		throw DateExcept("Invalid Date");
	int day, month, year;
	string sday, smonth, syear;
	size_t i = 0;
	while (isdigit(format[i]) && i < format.length())
	{
		sday += format[i];
		i++;
	}
	while (!isdigit(format[i]) && i < format.length())
	{
		i++;
	}
	while (isdigit(format[i]) && i < format.length())
	{
		smonth += format[i];
		i++;
	}
	while (!isdigit(format[i]) && i < format.length())
	{
		i++;
	}
	while (isdigit(format[i]) && i < format.length())
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
	if (day > 31 || month > 12 || day <= 0 || month <= 0)
		throw DateExcept("Invalid Date");
	*this = Date(day, month, year);
	if (getDay() != day || getYear() != year || getMonth() != month)
		throw DateExcept("Invalid Date");
}

Date::DateExcept::DateExcept(string description) :description(description){}
string Date::DateExcept::operator()(){ return description; }

Date& Date::operator=(const Date& d2)
{
	this->totalseconds = d2.totalseconds;
	return *this;
}

 int Date::toSeconds(int day, int month, int year, int hours, int minutes, int seconds)
{
	day += 1;
	month += 1;
	year += 1970;
	Date d = Date(day, month, year, hours, minutes, seconds);
	return (int)(d.totalseconds);
}

 time_t Date::getTotalSeconds() const { return this->totalseconds; }
 int Date::getDay() const		{ tm* datetime = localtime(&totalseconds); return datetime->tm_mday; }
 int Date::getMonth() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_mon + 1; }
 int Date::getYear() const		{ tm* datetime = localtime(&totalseconds); return datetime->tm_year + 1900; }
 int Date::getHours() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_hour; }
 int Date::getMinutes() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_min; }
 int Date::getSeconds() const	{ tm* datetime = localtime(&totalseconds); return datetime->tm_sec; }
 int Date::getWeekDay() const  { tm* datetime = localtime(&totalseconds); return datetime->tm_wday + 1; }
 int Date::getYearDay() const  { tm* datetime = localtime(&totalseconds); return datetime->tm_yday; }
 string Date::printDate() const
 {
	 stringstream s;
	 s << std::setfill('0') << std::setw(2) << getDay() << "/" << std::setfill('0') << std::setw(2) << getMonth() << "/" << std::setfill('0') << std::setw(4) << getYear() << " " << std::setfill('0') << std::setw(2) << getHours() << ":" << std::setfill('0') << std::setw(2) << getMinutes() << ":" << std::setfill('0') << std::setw(2) << getSeconds();
	 return s.str();
 }
 string Date::printDate2() const
 {
	 stringstream s;
	 s << std::setfill('0') << std::setw(2) << getDay() << "/" << std::setfill('0') << std::setw(2) << getMonth() << "/" << std::setfill('0') << std::setw(2) << getYear();
	 return s.str();
 }