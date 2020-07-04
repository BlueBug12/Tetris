#include  "MinoI.h"

//x+boundary top.x + 5  x-boundary top.x - 6
MinoI::MinoI() :Mino(){
	srand(time(NULL));
	position.at(2).X = 4;
	position.at(2).Y = 2;
	
	//r_index = 0;
	r_index = rand() % 4;
	mode(r_index);
}

int MinoI::mode(int m){
	int steps = 0;
	int centerX = position.at(2).X;
	int centerY = position.at(2).Y;
	if (m == 0){
		position.at(0).X = centerX;
		position.at(0).Y = centerY - 2;
		position.at(1).X = centerX;
		position.at(1).Y = centerY - 1;
		position.at(3).X = centerX;
		position.at(3).Y = centerY + 1;
		r_index = 0;
	}

	else if(m == 1){
		position.at(0).X = centerX - 1;
		position.at(0).Y = centerY;
		position.at(1).X = centerX + 1;
		position.at(1).Y = centerY;
		position.at(3).X = centerX + 2;
		position.at(3).Y = centerY;
		r_index = 1;
	}

	else if (m == 2){
		position.at(0).X = centerX;
		position.at(0).Y = centerY - 1;
		position.at(1).X = centerX;
		position.at(1).Y = centerY + 1;
		position.at(3).X = centerX;
		position.at(3).Y = centerY + 2;
		r_index = 2;
	}

	else if (m == 3){
		position.at(0).X = centerX - 2;
		position.at(0).Y = centerY;
		position.at(1).X = centerX - 1;
		position.at(1).Y = centerY;
		position.at(3).X = centerX + 1;
		position.at(3).Y = centerY;
		r_index = 3;
	}

	while (position.at(0).X < 0){
		for (int i = 0; i < 4; ++i){
			++position.at(i).X;
		}
		++steps;
	}

	//right boundary
	while (position.at(3).X>9){
		for (int i = 0; i < 4; ++i){
			--position.at(i).X;
		}
		--steps;
	}
	return steps;
}


int MinoI::turn(int wise){
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

