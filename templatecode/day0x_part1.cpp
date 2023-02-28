#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> strsplit(string str, string delimiter){
	vector<string> result;
	size_t length = str.size();
	size_t next_pos = 0;
	size_t index = str.find_first_not_of(delimiter, 0);
	
	while(index < length){
		string token;
		next_pos = str.find(delimiter, index);
		if (next_pos != string::npos)
			token = str.substr(index, next_pos - index);
		else
			token = str.substr(index, length - index);
		result.push_back(token);
		index = str.find_first_not_of(delimiter, next_pos);
	}
	return (result);
}

void read_file(ifstream & inputfile, vector<string> & lines){
	string line;
	while(getline(inputfile, line))
		lines.push_back(line);
}

int main(int argc, char ** argv){
	if(argc != 2){
		cout << "Program must have one argument." << endl;
		return (1);
	}
	
	ifstream inputfile(argv[1]);
	if(!inputfile.is_open()){
		cout << "Error opening file" << endl;
		return (1);
	}
	vector<string> lines;
	read_file(inputfile, lines);
	
	//implementation here

	inputfile.close();
	return (0);
}