#include "timer.h"

Timer::Timer(){
	second = 0;
	minute = 0;
	start_time = 0;
	current_time = 0;
	set_time();
}

void Timer::set_time(){
	start_time = time(NULL);
}

int Timer::get_time(int&m,int&s){
	current_time = time(NULL) - start_time;
	minute = current_time / 60;
	second = current_time % 60;
	m = minute;
	s = second;
	return current_time;
}