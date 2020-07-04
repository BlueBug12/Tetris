#include <iostream>
#include <ctime>
using namespace std;

class Timer{
public:
	Timer();
	void set_time();
	int get_time(int&,int&);
	
private:
	unsigned int start_time;
	unsigned int current_time;
	int second;
	int minute;
};
