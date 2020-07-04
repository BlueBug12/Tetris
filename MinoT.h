#ifndef MINO_T_H
#define MINO_T_H

#include "Mino.h"

using namespace std;
class MinoT :public Mino{
public:
	MinoT();
	virtual int mode(int);
	virtual int turn(int m);

};
#endif

