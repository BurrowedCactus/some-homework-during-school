// this is refines the code in term 1175.
// last edited on date October 05th, 2017.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Options{
	bool all;
	bool chars;
	bool words;
	bool lines;
	int num_files;
	string* files;
	Options(): all(true), chars(false), words(false), lines(false), num_files(0), files(nullptr) {}
	~Options(){
		delete [] files;
	}
};

struct Counts{
	string name; 
	int chars;
	int words;
	int lines;
};


// prints the counted result according to the option flags
void printCounts(Counts& count, Options& ops){
	if ((ops.lines == true && ops.words == true && ops.chars == true) || ops.all == true){
		cout << count.lines << " " << count.words << " " << count.chars;
	} else if (ops.lines == true && ops.words == true){
		cout << count.lines << " " << count.words;
	} else if (ops.lines == true && ops.chars == true){
		cout << count.lines << " " << count.chars;
	} else if (ops.words == true && ops.chars == true){
		cout << count.words << " " << count.chars;
	} else if (ops.lines == true){
		cout << count.lines;
	} else if (ops.words == true){
		cout << count.words;
	} else if (ops.chars == true){
		cout << count.chars;
	} else {
		cout << "printCounts failed" << endl;
	}
	
}


// sets c to represent the contents of input
void fillCounts(Counts& c, string input = "" ){
	c.chars = input.length();
	int word_count = 0;
	int line_count = 0;
	bool ready = true;
	for (int i = 0; i < c.chars; i++){
		if (input[i] == '\n'){
			++line_count;
			ready = true;
		} else if (input[i] != ' ' && ready == true){
			++word_count;
			ready = false;
		} else if (input[i] == ' ' && ready == false){
			ready = true;
		}
	}
	if (c.chars == 0){
		c.words = 0;
		c.lines = 0;
	} else {
		c.words = word_count;
		c.lines = line_count;
	}
}

// interpret command line arguments and set variables of Options
void handleArgs(int argc, char* argv[], Options& ops){
	int num_files = 0;
	bool has_file = false;
	int capacity = 5;
	string line = "-l";
	string word = "-w";
	string chars = "-c"; 
	string * lst = new string [5];
  // determine which flags are present and the number of files read
  // note, the first argument is the name of the program and should 
  // be ignore -> start at 1
	for (int i = 1; i < argc; ++i ){
		if (argv[i] == line){
			ops.lines = true;
		} else if (argv[i] == word){
		ops.words = true;
		} else if (argv[i] == chars){
		ops.chars = true;
		} else if (!has_file){
			lst[0] = argv[i];
			ops.files = lst;
			has_file = true;
			num_files = 1;			
		} else {
			if (capacity <= num_files){
				string temp [capacity];
				for(int i = 0; i < capacity; ++i){
					temp[i] = lst[i];	
				}
				delete [] lst;
				lst = new string [capacity * 2];
				for(int i = 0; i < capacity; ++i){
					lst[i] = temp[i];
				}
				capacity *= 2;
				ops.files = lst;
			}
			lst[num_files] = argv[i];
			++num_files;
		} 
		ops.files = lst; 
		ops.num_files = num_files;
	}	
	if (!ops.lines && !ops.words && !ops.chars){
		ops.all = true;
	}	else {
		ops.all = false;
	}
	if (num_files == 0){
		delete [] lst;
	}
	ops.num_files = num_files;
	
}


// argc is the number of command line arguments read
// argv is an array of c-style strings, i.e. char*'s where each element of
//    argv is a null-terminated, whitespace delimited, command-line argument
int main(int argc, char* argv[]){
	Options ops;
	handleArgs(argc, argv, ops);
	
	if (argc == 1){
		Counts count;
		string s = "";
		getline(cin,s);
		if (s.length() != 0){
			s += '\n';
		}
		string s2 = "";
		while (getline(cin,s2)){
			s += (s2 + '\n');
		}
		fillCounts(count, s);
		printCounts(count, ops);
		cout << endl;
	} else if (ops.num_files == 0){
		Counts count;
		string s = "";
		getline(cin,s);
		if (s.length() != 0){
			s += '\n';
		}
		string s2 = "";
		while (getline(cin,s2)){
			s += (s2 + '\n');
		}
		fillCounts(count, s);
		printCounts(count, ops);
		cout << endl;
	}else if (ops.num_files == 1){
		Counts count;
		ifstream file{ops.files[0]};
		string s;
		string line;
		while(getline(file, line)){
			s += (line + '\n') ;
		}
		fillCounts(count, s);
		printCounts(count, ops);
		s = ops.files[0];
		cout << " " << s << endl;
	}else{
		int t_l = 0;
		int t_w = 0;
		int t_c = 0;
		int num = ops.num_files;
		Counts count[num];
		for (int i = 0; i < num; ++i){
			ifstream file{ops.files[i]};
			string s;
			string line;
			while(getline(file, line)){
				s += (line + '\n') ;
			}
			fillCounts(count[i], s);
			printCounts(count[i], ops);
			s = ops.files[i];
			cout << " " << s << endl;
			t_l += count[i].lines;
			t_w += count[i].words;
			t_c += count[i].chars;
		}
		Counts t_count{"total", t_c, t_w, t_l};
		printCounts(t_count, ops);
		cout << " total"<< endl;
	}
}
