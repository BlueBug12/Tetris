
#include  "MinoO.h"

//x+boundary top.x + 5  x-boundary top.x - 6
MinoO::MinoO() :Mino(){
	position.at(0).X = 4;
	position.at(0).Y = 0;
	position.at(1).X = 5;
	position.at(1).Y = 0;
	position.at(2).X = 4;
	position.at(2).Y = 1;
	position.at(3).X = 5;
	position.at(3).Y = 1;
	mode(0);
}

int MinoO::mode(int m){
	
	return 0;
}


int MinoO::turn(int wise){
	int steps = 0;
	if (wise == TURN_R){
		++r_index;
		steps = mode(r_index % 4);
	}
	else if (wise == TURN_L){
		--r_index;
		if (r_index == -1){
			r_index = 3;
		}
		steps = mode(r_index % 4);
	}

	return steps;
}

