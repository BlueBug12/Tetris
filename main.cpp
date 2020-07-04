#include <iostream>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#include "interface.h"
#include "generator.h"
#include "timer.h"
#include "Mino.h"
#include "recorder.h"

#define COLOR_ORANGE 7

using namespace std;
//10*20

int main(){
	srand(time(NULL));

	int end = 0;
	int temp = 0;
	int height = 0;
	int width = 0;
	int minute = 0;
	int second = 0;
	int number = rand() % 7 + 1;
	int next_number = rand() % 7 + 1;
	int store_number = 0;
	int input;
	int line = 0;
	int highest_score = 0;
	int highest_time = 0;
	string h_name="   ";
	double speed = 0.00003;
	double clock = 0.0;
	
	
	initscr();
	start_color();
	cbreak(); noecho();	keypad(stdscr, TRUE); nodelay(stdscr, TRUE);
	getmaxyx(stdscr, height, width);//height 30  width 103

	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_RED, COLOR_BLACK);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_ORANGE, COLOR_BLACK);


	Interface interf(height, width);
	interf.ground();

	Timer timer;
	Recorder recorder("minoFile.txt");//process file
	if (recorder.get_record(h_name, highest_score,highest_time)){
		interf.show_highest_score(highest_score, h_name,highest_time);
	}


	Generator generator;

	Mino *M_ptr;
	Mino *NEXT_ptr;
	
	M_ptr = generator.genMino(number);
	NEXT_ptr = generator.genMino(next_number);

	NEXT_ptr->pre_paint(next_number);
	interf.pre_see(M_ptr->get_position());

	attron(COLOR_PAIR(number));
	
	
	while (!end){
		M_ptr->paint();
		
		while ((input = getch()) == ERR){
			
			M_ptr->paint();
			timer.get_time(minute, second);
			interf.show_time(minute,second);
			attron(COLOR_PAIR(number));

			//clock edge
			if ((int)clock == temp + 1){
				M_ptr->recover();
				M_ptr->move(DOWN);
				if (speed <= 0.0001&&temp % 20 == 0){
					speed += 0.000005;
				}

				//touch ground
				if (interf.touch_ground(M_ptr->get_position())){
					
					attroff(COLOR_PAIR(number));
				
					M_ptr->move(UP);
					interf.erase_hill();
					interf.record(M_ptr->get_position(), number);
					
					//check if has any full row
					for (int a = 20; a > 0; --a){
							
						if (interf.full_row(a) == 2){
							break;
						}
						else if (interf.full_row(a) == 1){
							interf.delete_row(a);
							++a;
							++line;
						}
					}
					interf.line_for_one(line,highest_score);
					interf.if_combo(line);
					interf.show_hill();


					delete M_ptr;

					//game over
					if (interf.hit_top()){
						end = 1;
						refresh();
						break;
					}
					
					interf.reinitial();
					number = next_number;
					next_number = rand() % 7 + 1;
				
					//new Mino
					M_ptr = NEXT_ptr;
					NEXT_ptr = generator.genMino(next_number);
					NEXT_ptr->pre_paint(next_number);

					interf.pre_see(M_ptr->get_position());
					attron(COLOR_PAIR(number));
				}
				else{
					M_ptr->paint();
				}
				
				interf.test();
				++temp;
				refresh();
			}//end edge

			//counting
			clock += speed;
		}//end no key in

		switch (input){
		
			//move right
			case KEY_RIGHT:
				M_ptr->recover();
				M_ptr->move(RIGHT);
				
				if (interf.touch_ground(M_ptr->get_position())){
					M_ptr->move(LEFT);
				}
				
				M_ptr->paint();
				interf.pre_see(M_ptr->get_position());
				attron(COLOR_PAIR(number));
				break;

			//move left
			case KEY_LEFT:
				M_ptr->recover();
				M_ptr->move(LEFT);

				if (interf.touch_ground(M_ptr->get_position())){
					M_ptr->move(RIGHT);
				}
					
				M_ptr->paint();
				interf.pre_see(M_ptr->get_position());
				attron(COLOR_PAIR(number));
				break;

			//turn clockwise

			case 'R':
			case 'r':
			case KEY_UP:
			{
				M_ptr->recover();
				int steps = M_ptr->turn(TURN_R);

				if (interf.touch_ground(M_ptr->get_position())){
					M_ptr->turn(TURN_L);
					if (steps > 0){
						for (; steps > 0; --steps){
							M_ptr->move(LEFT);
						}
					}
					else if (steps < 0){
						for (; steps < 0; ++steps){
							M_ptr->move(RIGHT);
						}
					}
				}

				M_ptr->paint();
				interf.pre_see(M_ptr->get_position());
				attron(COLOR_PAIR(number));
				break;
			}

			case KEY_DOWN:
				clock += 0.7;
				break;
			//turn counterclockwise
			case 'L':
			case'l':
			{
					   
				M_ptr->recover();
				int steps = M_ptr->turn(TURN_L);

				if (interf.touch_ground(M_ptr->get_position())){
					M_ptr->turn(TURN_R);
					if (steps > 0){
						for (; steps > 0; --steps){
							M_ptr->move(LEFT);
						}
					}
					else if (steps < 0){
						for (; steps < 0; ++steps){
							M_ptr->move(RIGHT);
						}
					}
				}

				M_ptr->paint();
				interf.pre_see(M_ptr->get_position());
				attron(COLOR_PAIR(number));
				break;
			}
				
			case '\t':
			case 'D':
			case 'd'://tab
				M_ptr->recover();
				M_ptr->straight_down(interf.pre_down(M_ptr->get_position()));
				clock = temp + 1;
				break;

			case 'E':
			case 'e':
				delete M_ptr;
				end = 1;
				break;

			default:
				break;
		}//end switch

		//counting
		clock += speed;
		timer.get_time(minute, second);
		interf.show_time(minute, second);
		attron(COLOR_PAIR(number));
	}//end outer while

	if (recorder.on_record(interf.get_score(), timer.get_time(minute, second))){
		
		recorder.leaderBoard(1, interf.get_score(), timer.get_time(minute, second));
		recorder.writeFile();
	
	}
	
	else{
		recorder.leaderBoard(0);
	}
	endwin();
	return 0;
}
