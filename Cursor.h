#ifndef _CURSOR
#define _CURSOR

#include <iostream>
#include <string>
#include <utility>

class Cursor
{
	int pos;
	int pos_max;
public:
	Cursor();
	Cursor(int pos_max);
	Cursor(int pos, int pos_max);
	int getPosition() const;
	bool dec();
	bool inc();
	bool setPosition(int position);
	bool changeMax(int max);
};
inline int Cursor::getPosition() const
{
	return this->pos;
}

class TwoCursor: public Cursor
{
	int pos2;
	int pos_max2;
public:
	TwoCursor();
	TwoCursor(int pos_max, int pos_max2);
	TwoCursor(int pos, int pos_max, int pos2, int pos_max2);
	int getPosition2() const;
	bool dec2();
	bool inc2();
	bool setPosition2(int position);
	bool changeMax2(int max);
};


#endif