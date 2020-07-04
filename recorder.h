#ifndef RECORDER_H
#define RECORDER_H
#include <iostream>
#include <fstream>
#include <vector>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Recorder{
public:
	Recorder(string filename);
	void readFile(string file);
	bool get_record(string& n,int& s,int& t);
	bool on_record(const int s,const int t);
	void leaderBoard(bool on, const int s = 0, const int t = 0);
	void writeFile();
	
private:
	int amount;
	int position;
	ifstream inFile;
	ofstream outFile;
	string filename;
	vector<string>name;
	vector<int>score;
	vector<int>time;
};
#endif