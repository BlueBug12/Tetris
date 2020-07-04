#include "generator.h"
Mino* Generator::genMino(int n){
	Mino* ptr;
	try{
		switch (n){
		case 1:
			ptr = new MinoI;
			break;

		case 2:
			ptr = new MinoT;
			break;

		case 3:
			ptr = new MinoJ;
			break;

		case 4:
			ptr = new MinoS;
			break;

		case 5:
			ptr = new MinoN;
			break;

		case 6:
			ptr = new MinoO;
			break;

		case 7:
			ptr = new MinoL;
			break;

		}
	}catch (bad_alloc &memoryAlloc){
		cerr << "new fail" << memoryAlloc.what() << endl;
	}
	return ptr;
}
