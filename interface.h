#ifndef INTERFACE_H
#define INTERFACE_H
#include <ncurses.h>
#include <iostream>
#include <vector>
#include "coordinate.h"

using namespace std;
class Interface{
public:
	Interface(int h, int w);
	void ground();
	void test();
	bool touch_ground(vector<Coordinate>);
	void record(vector<Coordinate>,int);
	void show_hill();
	int full_row(int row);
	void delete_row(int row);
	void erase_hill();
	bool hit_top();
	int pre_down(vector<Coordinate>);
	void pre_see(vector<Coordinate>);
	void reinitial();
	void line_for_one(int&,const int);
	bool if_combo(int);
	void show_time(int&,int&);
	void show_highest_score(int,string,int)const;
	int get_score()const;
private:
	int width;
	int height;
	int score;
	
	unsigned int combo;
	int map[22][10];//1~20
	vector<Coordinate>pre;
};

#endif
