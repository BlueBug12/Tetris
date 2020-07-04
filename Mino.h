#ifndef MINO_H
#define MINO_H

#include "coordinate.h"
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cmath>
#include <ctime>

#define RIGHT 1
#define LEFT 2
#define DOWN 3
#define UP 4
#define TURN_R 1
#define TURN_L 2
using namespace std;

class Mino{
public:
	Mino();
	virtual int turn(int m) = 0;
	virtual int mode(int) = 0;
	virtual void paint();
	virtual void move(int direction);
	virtual void recover();
	virtual vector<Coordinate> get_position()const;
	virtual void straight_down(int d);
	virtual void pre_paint(int color);
	virtual void str_paint(int color);
	virtual void rec_str()const;
protected:
	int h, w;
	int r_index;
	vector<Coordinate>position;//x- 0,x + 3
};
#endif
