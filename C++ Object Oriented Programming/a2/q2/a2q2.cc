#include <iostream>
#include <string>
#include <sstream>
using namespace std;

string cypher(string s, int num){
	int current = 0;
	int length = s.length();
	if (num < 0){
		num += 26;
	}
	while ( current < length ){
		if (s[current] >= 'a' && s[current] <= 'z'){
			if (s[current] + num > 'z'){
				s[current] = s[current] + num - 26;
			} else{
				s[current] = s[current] + num;
			}
		} else if (s[current] >= 'A' && s[current] <= 'Z'){
			if (s[current] + num > 'Z'){
        		s[current] = s[current] + num - 26;
			} else{
				s[current] = s[current] + num;
			}
		}
 		++current; 	
	}
	return s;
}

int check_arg (const int argc, const char *argv[]){
	int num;
	string left = "left";
	string right = "right";
	istringstream iss1{argv[0]};
	iss1 >> num;
	if ( argc - 1 == 1 && (num > 25 || num < 0)){
		cerr << "ERROR" << endl;
		return 1;
	} 
	if ( argc - 1 == 2 && ( argv[2] != left && argv[2] != right)){
		cout << argv[2];
		cerr << "ERROR" << endl;
		return 2;
	}
	return 0;
}

void manage_arg (const int argc, const char *argv[], int& shift){
	int num;
	string left = "left";
	if (argc - 1 == 0){	
		shift = 3;
	} else {
		istringstream iss1{argv[1]};
		iss1 >> num;
		if (argc - 1 == 1){
			shift = num;
		} else if (argv[2] == left){
			shift = - num;
		} else {
			shift = num;
		}
	}
}

int main(const int argc, const char *argv[]) {
	if (argc == 0 || argc > 3 ) {
		exit(EXIT_FAILURE);
	}
	int error_code = check_arg(argc,argv);
	if (error_code == 1 || error_code == 2){
		cout << error_code;
	}
	int shift;
	manage_arg(argc, argv, shift);
	std::string line;
	while (std::getline(std::cin, line)) {
		if (line[0] == 'e'){
			line = cypher(line.substr(1), shift);
			cout << line << endl;
		}else if (line[0] == 'd'){
			line = cypher(line.substr(1), -shift);
			cout << line << endl;
		}else if (line[0] == 'q'){
			break;
		}
	}
	return 0;
}
