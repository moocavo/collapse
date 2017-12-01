#include<iostream>
#include<fstream>
#include<getopt.h>
#include<string>
#include<algorithm>
#include<stdlib.h>

bool checkArgs(int, char **, std::string &, std::string &, bool &, int &);
std::string parseLine(std::string &, int);

int main(int argc, char **argv){

	std::string in_file, out_file;
	bool sub;
	int col = 1;

	if (checkArgs(argc,argv,in_file,out_file,sub,col)){
		std::cerr << "exited with error; invalid command line arguments" << std::endl;
		std::cerr << "usage: ./collapse -i [input file] -o [output file]" << std::endl;
		std::cerr << "optional flags:\n\t-s (substrings are considered matches)\n\t-c [column to collapse by (1 indexed)]" << std::endl;
		return 1;
	}

	std::ifstream in;
	std::ofstream out;
	in.open(in_file.c_str());
	out.open(out_file.c_str());

	std::string prev_line, curr_line;
	std::string	prev, curr; 
	int counter = 1;

	std::getline(in,prev_line);

	if (!sub){ // substr not specified
		while (std::getline(in,curr_line)){
			prev = parseLine(prev_line,col);
			curr = parseLine(curr_line,col);	
			if (prev != curr){
				out << prev_line << '\t' << counter << '\n';
				counter = 1;
			}
			else ++counter;

			prev_line = curr_line;	
		}	
	}
	else { // substr specified
		while (std::getline(in,curr_line)){
			prev = parseLine(prev_line,col);
			curr = parseLine(curr_line,col);	
			if (prev.find(curr) == std::string::npos && curr.find(prev) == std::string::npos){
				out << prev_line << '\t' << counter << '\n';
				counter = 1;
			}
			else ++counter;

			prev_line = curr_line;	
		}	
	}

	out << prev_line << '\t' << counter << '\n';

	in.close();
	out.close();

	return 0;

}

bool checkArgs(int argc, char **argv, std::string &in_file, std::string &out_file, bool &sub, int &col){ // returns true if there was a command line argument error, otherwise return false
	
	bool gotin = 0, gotout = 0;
	int gotopt;
	int option_index = 0;
	option long_opts[] = {
		{ "input", required_argument, nullptr, 'i' },
		{ "substr", no_argument, nullptr, 's' },
		{ "output", required_argument, nullptr, 'o' },
		{ "column", required_argument, nullptr, 'c' },
		{ nullptr, 0, nullptr, '\0' },
	};

	while ((gotopt = getopt_long(argc, argv, "i:so:c:", long_opts, &option_index)) != -1) {
		if (gotopt == 'i'){
			in_file = optarg;
			gotin = 1;
		}
		else if (gotopt == 's') {
			sub = 1;
		}
		else if (gotopt == 'o') { 
			out_file = optarg;
			gotout = 1;
		}
		else if (gotopt == 'c') {
			col = atoi(optarg);	
		}
		else return 1;
	}

	if (!gotin || !gotout) {
		std::cerr << "error: Did not recieve a valid input or output argmuent" << std::endl;
		return 1;
	}

	return 0;
}

// returns the field of the specified column
std::string parseLine(std::string &line, int col){

	int field = 0;		
	std::string copy;

	int prev = 0;
	unsigned int counter = 0;

	while (field != col){
		if (counter == line.size()) {
			copy = line.substr(prev,counter-prev);
			break;
		}
		if (line[counter] != ' ' && line[counter] != '\t'){
			++counter;
		}
		else if (line[counter] == ' ' || line[counter] == '\t'){
			++field;
			copy = line.substr(prev,counter-prev);
			prev = ++counter;
		}
	}

	return copy;
}
