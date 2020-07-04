#ifndef MINO_O_H
#define MINO_O_H

#include "Mino.h"

using namespace std;
class MinoO :public Mino{
public:
	MinoO();
	virtual int mode(int);
	virtual int turn(int m);

};
#endif







