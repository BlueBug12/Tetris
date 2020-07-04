#ifndef MINO_L_H
#define MINO_L_H

#include "Mino.h"

using namespace std;
class MinoL :public Mino{
public:
	MinoL();
	virtual int mode(int);
	virtual int turn(int m);

};
#endif
