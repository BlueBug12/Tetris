#include "recorder.h"
Recorder::Recorder(string filename){
	amount = 0;
	position = -1;
	readFile(filename);
}

void Recorder::readFile(string file){
	attrset(A_NORMAL);
	filename = file;
	inFile.open(filename, ios::in);
	if (!inFile){
		cerr << "Failed opening input file" << endl;
		exit(1);
	}
	else{
		inFile >> amount;
		
		int counter = amount;
		for (; counter > 0;--counter){
	
			
			string n;
			int s;
			int t;

			inFile >> n;
			name.push_back(n);
			
			inFile >> s;	
			score.push_back(s); 
			
			inFile >> t;
			time.push_back(t);
			
		} 
	}
	inFile.close();
}

bool Recorder::get_record(string& n ,int& s,int& t){
	if (amount != 0){
		n = name.at(0);
		s = score.at(0);
		t = time.at(0);
		return 1;
	}

	else{
		n = "  ";
		s = 0;
		t = 0;
		return 0;
	}
	
}

bool Recorder::on_record(const int s,const int t){
	
	if (s <= 0){return 0; }//0 score can't be the rank
	if (amount < 5){
		score.push_back(0);
		name.push_back("noname");
		time.push_back(0);
		++amount;
		
	}
	
	//if the score is bigger than any in leaderboard, record it's position
	for (int i = 0; i < score.size(); ++i){
		if (s > score.at(i)){
			position = i;
			return 1;
		}

		//if score is the same, compare the time
		else if (s == score.at(i)){
			if (t<=time.at(i)){
				position = i;
				return 1;
			}
			else{continue;}
		}
	}
	return 0;
}

void Recorder::writeFile(){
	
	outFile.open(filename, ios::out);
	if (!outFile){
		cerr << "Failed opening input file" << endl;
		exit(1);
	}

	else{
		outFile << amount;
		outFile << "\r\n";
		for (int i = 0; i<name.size(); ++i){
			outFile << name.at(i);
			outFile << "\r\n";
			outFile << score.at(i);
			outFile << "\r\n";
			outFile << time.at(i);
			outFile << "\r\n";
			
		}
	}	
	outFile.close();
}

void Recorder::leaderBoard(bool on,const int s,const int t){
	if (on){
		int counter = amount - 2;
	
		//change loop
		while (counter >= position){
			score.at(counter + 1) = score.at(counter);
			name.at(counter + 1) = name.at(counter);
			time.at(counter + 1) = time.at(counter);
			--counter;
		}
		score.at(position) = s;
		time.at(position) = t;
	}

	echo();
	attrset(A_NORMAL);
	WINDOW *win;
	
	win = newwin(6+score.size()*1, 40, LINES / 2 - 3, COLS / 2 - 20);
	box(win, '|', '-');
	
	//background
	mvaddstr(LINES / 2-4, COLS / 2 - 5, "LEARDBOARD");
	mvwaddstr(win, 2, 6, "Name:");
	mvwaddstr(win, 2, 21, "Score:");
	mvwaddstr(win, 2, 29, "Time:");

	for (int i = 0; i < score.size(); ++i){
		//number
		mvwaddstr(win, i+3, 1, "No.");
		mvwprintw(win, i + 3, 4,"%d",i+1);

		//name
		if (i != position){
			for (int j = 0; j < name.at(i).size(); ++j){
				mvwaddch(win, i + 3, 6 + j, name.at(i).at(j));
			}
		}
		mvwprintw(win, i + 3, 21, "%d", score.at(i));//score
		mvwprintw(win, i + 3, 29, "%d", time.at(i) / 60);//time
		mvwaddch(win, i + 3, 31, 'm');
		mvwprintw(win, i + 3, 33, "%d", time.at(i) % 60);
		mvwaddch(win, i + 3, 35, 's');
	}
	
	
	if (on){
		mvwprintw(win, 1, 10, "You are on the top 5 !");
		touchwin(win);
		wrefresh(win);
		char *n = new char[14];
		nodelay(stdscr, 0);
		move(LINES / 2 + position, COLS / 2 - 14);
		getstr(n);
		name.at(position) = n;
		sleep(3);
		delete n;
	
	}
	else{
		
		mvwprintw(win, 1, 10, "Push any key to leave.");
		touchwin(win);
		wrefresh(win);
		nodelay(stdscr, 0);
		getch();
	}
	touchwin(stdscr);
}