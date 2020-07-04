#include "Mino.h"

Mino::Mino(){
	getmaxyx(stdscr, h, w);
	h = h / 10;
	w = w / 2 - 5;
	r_index = 0;
	Coordinate temp;
	temp.X = 0;
	temp.Y = 0;
	position.assign(4, temp);
}

void Mino::move(int direction){
	
	
	if (direction == RIGHT&&position.at(3).X<9){
		for (int i = 0; i < 4; ++i){
			++position.at(i).X;
		}
	}
	else if (direction == LEFT&&position.at(0).X>0){

		for (int i = 0; i < 4; ++i){
			--position.at(i).X;
		}
	}

	else if (direction == DOWN){

		for (int i = 0; i < 4; ++i){
			++position.at(i).Y;
		}
	}

	else if (direction == UP){

		for (int i = 0; i < 4; ++i){
			--position.at(i).Y;
		}
	}
}

void Mino::paint(){
	for (int i = 0; i < 4; ++i){
		mvaddch(position.at(i).Y + h, position.at(i).X + w, '0');
	}
}

void Mino::recover(){
	for (int i = 0; i < 4; ++i){
		mvaddch(position.at(i).Y + h, position.at(i).X + w , ' ');
	}
}

vector<Coordinate> Mino::get_position()const{
	return position;
}

void Mino::straight_down(int d){
	for (; d > 0; --d){
		move(DOWN);
	}
}

void Mino::pre_paint(int color){
	attrset(A_NORMAL);
	int d = 11;
	int ht = 0;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			mvaddch(h + 3 + i, w + d + j, ' ');
		}
	}
	attron(COLOR_PAIR(color));
	for (int i = 0; i < 4; ++i){
		if (position.at(i).Y>h){
			ht = -1;
			break;
		}
	}
	d -= position.at(0).X;
	for (int i = 0; i < 4; ++i){
		mvaddch(position.at(i).Y + h + 3 + ht, position.at(i).X + w + d, '0');
	}
	attroff(COLOR_PAIR(color));
}

void Mino::str_paint(int color){
	attrset(A_NORMAL);
	int d = -8;
	int ht = 0;
	
	attron(COLOR_PAIR(color));
	for (int i = 0; i < 4; ++i){
		if (position.at(i).Y>h){
			ht = -1;
			break;
		}
	}
	//d -= position.at(0).X;
	for (int i = 0; i < 4; ++i){
		mvaddch(position.at(i).Y + h + 3 + ht, position.at(i).X + w + d, '0');
	}
	attroff(COLOR_PAIR(color));
}

void Mino::rec_str()const{
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			mvaddch(h + 3 + i, w -5 + j, ' ');
		}
	}
}