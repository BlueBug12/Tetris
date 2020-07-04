#ifndef MINO_S_H
#define MINO_S_H

#include "Mino.h"

using namespace std;
class MinoS :public Mino{
public:
	MinoS();
	virtual int mode(int);
	virtual int turn(int m);

};
#endif

