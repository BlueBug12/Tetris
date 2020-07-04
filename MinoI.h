#ifndef MINO_I_H
#define MINO_I_H

#include "Mino.h"

using namespace std;
class MinoI :public Mino{
public:
	MinoI();
	virtual int mode(int);
	virtual int turn(int m);

};
#endif
