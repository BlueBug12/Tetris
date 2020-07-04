#include "interface.h"
using namespace std;
Interface::Interface(int h, int w){

	height = h/10;
	width = w / 2;
	score = 0;
	combo = 0;
	//initialize map with 0
	for (int i = 0; i < 21; ++i){
		for (int j = 0; j < 10; ++j){
			map[i][j] = 0;
		}
	}

	//B1 of map
	for (int i = 0; i < 10; ++i){
		map[21][i] = 9;
	}

	Coordinate temp;
	temp.X = -1;
	temp.Y = -1;

	pre.assign(4,temp);


	
}
void Interface::test(){
	for (int i = 0; i < 22; ++i){
		//mvprintw(i, 0, "%d", i);
		for (int j = 0; j < 10; ++j){
			//mvprintw(i, j + 3, "%d", map[i][j]);
		}
	}
	
}
void Interface::ground(){
	
	for (int i = 1; i < 21;++i){
		mvaddch(height + i, width + 5, '|');
		mvaddch(height + i, width - 6, '|');
	}
	
	for (int i = 0; i < 12; ++i){
		mvaddch(height + 21, width - 6 + i,'-');
	}
	
	mvaddstr(height + 1, width + 6, "NEXT");
	mvaddstr(height + 2, width + 6, "----");
	for (int i = 2; i < 8; ++i){
		mvaddch(height + i, width + 10, '|');
	}
	mvaddstr(height + 7, width + 6, "----");
	mvaddstr(height + 8, width + 6, "time:");
	mvaddch(height + 8, width + 13, 'm');
	mvaddch(height + 8, width + 16, 's');

	mvaddstr(height + 10, width + 6, "score:");
	mvprintw(height + 10, width + 13, "%d", score);
}


//46~55  bottom 22
bool Interface::touch_ground(vector<Coordinate>p){
	for (int i = 0; i < 4; ++i){
		if (map[p.at(i).Y][p.at(i).X] != 0){
			return 1;
		}
	}

	return 0;
}
	
void Interface::record(vector < Coordinate > p,int color){
	for (int i = 0; i < 4; ++i){
		map[p.at(i).Y][p.at(i).X] = color;
	}
}

void Interface::show_hill(){
	for (int i = 20; i >0; --i){
		int counter = 0;
		for (int j = 9; j >=0; --j){
			if (map[i][j] != 0){
				attron(COLOR_PAIR(map[i][j]));		
				mvaddch(i + height, j + width - 5, '0');
				attroff(COLOR_PAIR(map[i][j]));
				++counter;
			}
		}
		if (counter == 0){ break; }
	}

	
	mvprintw(height + 10, width + 13, "%d", score);
	
}

int Interface::full_row(int row){
	int counter = 0;
	for (int i = 0; i < 10; ++i){
		if (map[row][i] != 0){
			++counter;
		}
	}
	if (counter == 10){ return 1; }
	else if (counter == 0){ return 2; }
	else{ return 0; }
}

void Interface::delete_row(int row){
	for (int i = row; i > 0; --i){
		for (int j = 0; j < 10; ++j){
			map[i][j] = map[i - 1][j];
		}
	}
}

void Interface::erase_hill(){
	for (int i = 20; i > 0; --i){
		int counter = 0;
		for (int j = 9; j >= 0; --j){
			if (map[i][j] != 0){
				mvaddch(i + height, j + width - 5, ' ');
				++counter;
			}
		}
		if (counter == 0){ break; }
	}
}

bool Interface::hit_top(){
	for (int i = 0; i < 10; ++i){
		if (map[0][i]!=0){
			return 1;
		}
	}
	return 0;
}

int Interface::pre_down(vector<Coordinate> p){
	int counter = -1;
	for (int i = 1; i < 22; ++i){
	
		for (int k = 0; k < 4; ++k){
			if (map[p.at(k).Y][p.at(k).X]!=0){
				return counter;
			}
		}

		for (int j = 0; j < 4; ++j){
			++p.at(j).Y;
		}
		++counter;
		
	}

}

void Interface::pre_see(vector<Coordinate> p){
	//init_pair(0, COLOR_WHITE, COLOR_BLACK);
	for (int i = 0; i < 4; ++i){
		mvaddch(pre.at(i).Y + height, pre.at(i).X + width - 5, ' ');
	}

	int steps = pre_down(p);
	attrset(A_NORMAL);
	//attron(COLOR_PAIR(0));
	for (int i = 0; i < 4; ++i){
		p.at(i).Y += steps;
		
		mvaddch(p.at(i).Y + height, p.at(i).X + width - 5, '@');
		
	}
	//attroff(COLOR_PAIR(0));
	pre = p;
	
}

void Interface::reinitial(){
	for (int i = 0; i < 4; ++i){
		pre.at(i).X = -1;
		pre.at(i).Y = -1;
	}
}

void Interface::line_for_one(int& line,const int high_s){
	++combo;

	switch (line){
	case 1:
		score += 10;
		break;
	case 2:
		mvaddstr(9, 37, "2 lines");
		score += 20;
		break;

	case 3:
		mvaddstr(9, 37, "3 lines");
		score += 30;
		break;

	case 4:
		mvaddstr(9, 37, "4 lines");
		score += 40;
		break;

	default:
		mvaddstr(9, 37, "       ");
		combo = 0;
		break;
	}
	
	if (score>high_s){
		mvaddstr(height + 11, width + 6, "New Record");
	}
	line = 0;

}

bool Interface::if_combo(int line){
	if (combo > 1){
		score += line*combo;
		mvaddstr(10, 37, "combo");
		mvprintw(10, 43, "%d", combo);
		return 1;
	}
	else{
		mvaddstr(10, 37, "       ");
		return 0;
	}
	
}

void Interface::show_time(int&m,int&s){
	attrset(A_NORMAL);
	mvaddstr(height + 8, width + 11, "  ");
	mvprintw(height + 8, width + 11, "%d", m);
	mvaddstr(height + 8, width + 14, "  ");
	mvprintw(height + 8, width + 14, "%d", s);
}

void Interface::show_highest_score(int s,string n,int t)const{

	mvaddstr(height + 1, width - 20, "Highest Score:");
	mvprintw(height + 2, width - 15, "%d", s);
//	mvaddstr(height + 3, width - 20, "By:");
	for (int i = 0; i < n.size(); ++i){
		mvaddch(height + 3, width - 21 + i, n.at(i));//recorder's name
	}

	mvprintw(height + 4, width - 18, "%d", t / 60);
	mvaddch(height + 4, width - 16, 'm');
	mvprintw(height + 4, width - 15, "%d", t % 60);
	mvaddch(height + 4, width - 13, 's');
	
	
	
}

int Interface::get_score()const{
	return score;
}