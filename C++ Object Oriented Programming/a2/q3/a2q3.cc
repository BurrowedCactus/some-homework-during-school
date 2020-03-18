#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//manage_arg handles the invlalid inputs, and set "max_length" , "where" according
//to the arguments
void manage_arg (const int argc, const char *argv[], int& max_length, string& where, int& error){
	string left = "-l";
	string mid = "-c";
	string right = "-r";
	string width = "-w";
	//default case
	if (argc == 1){	
		max_length = 25;
	        where = "-l";
	//with argument -l, -c or -r.
	} else if (argc == 2){
		if (argv[1] == left || argv[1] == mid || argv[1] == right){
			max_length = 25;
			where = argv[1];
		} else {
			cerr << "wordWrap: invalid usage" << endl;
			cerr << "Usage: wordWrap [-w textWidth] [-l|-c|-r]" << endl;
			error = 2;
		}
	// with argument -w num , and optional (-r||-c||-l)
	} else if (argc == 3 || argc == 4){
		//set up max_length according to -w num
		istringstream iss1{argv[2]};
		if (!(iss1 >> max_length) || (argv[1] != width) || max_length <= 0){
			cerr << "wordWrap: invalid usage" << endl;
			cerr << "Usage: wordWrap [-w textWidth] [-l|-c|-r]" << endl;
			error = 2;
		}
		//set up where according to the optional (-l||-c||-r)
		if (argc == 3){
		        where = "-l";
		} else {
			if (argv[3] == left || argv[3] == mid || argv[3] == right){
				where = argv[3];
			} else {
				cerr << "wordWrap: invalid usage" << endl;
				cerr << "Usage: wordWrap [-w textWidth] [-l|-c|-r]" << endl;
				error = 2;
			}
		}
	// invalid number of arguments
	} else {
		cerr << "wordWrap: invalid usage" << endl;
		cerr << "Usage: wordWrap [-w textWidth] [-l|-c|-r]" << endl;
		error = 2;
	}
}

//f_print prints the line according to format where and max_length
void f_print(const string line, const string where, const int max_length){
	if (where == "-l"){
		cout << line << endl;
	} else if (where == "-r"){
		int length = max_length - line.length();
		while (length > 0){
			cout << " ";
			--length;
		}
		cout << line << endl;
	} else {
		int length = (max_length - line.length()) / 2;
		while (length > 0){
			cout << " ";
			--length;
		}
		cout << line << endl;
	}
}

int main(const int argc, const char *argv[]){
	int length = -1;
	int max_length;
	int error = 0;
	string where;
	manage_arg (argc, argv, max_length, where, error);
	if (error != 0){
		return error;
	}
	string word;
	string line;
	bool full = false;
	while(true){
		if(!full){
			cin >> word;
		}
		if(cin.eof()){
			break;
		}
		int temp = 1 + length + word.length();
		//line is full
		if(temp > max_length){
			//first word exceed max length
			if(line.empty()){
				line = word.substr(0,max_length);
				f_print(line, where, max_length);
				line = "";
				word = word.substr(max_length);
				full = true;
				length = -1;
			//too much word in a line
			} else {
				f_print(line, where, max_length);
				line = "";
				length = -1;
				full = true;
			}
		//line is not full; add the word to the end of the line
		} else {
			if (line.empty()){
				line += word;
			} else {
				line += (" " + word);
			}
			length += (1 + word.length());
			full = false;
		}
	}
	//clean up
	if (!line.empty()){
		f_print(line, where, max_length);	
	}
}
