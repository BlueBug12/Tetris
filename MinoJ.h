
#ifndef MINO_J_H
#define MINO_J_H

#include "Mino.h"

using namespace std;
class MinoJ :public Mino{
public:
	MinoJ();
	virtual int mode(int);
	virtual int turn(int m);

};
#endif

