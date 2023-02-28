#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <set>
#include <utility>

using namespace std;

typedef struct data{
	pair<int, int> coor;
	int steps;
} 				data_t;

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

bool find_coor(pair<int, int> target, vector<pair<int, int> > & alreadychecked){
	for(int i = 0; i < alreadychecked.size(); ++i)
	{
		if (target == alreadychecked[i])
			return true;
	}
	return false;
}

bool find_in_queue(pair<int, int> target, deque<data_t> to_examine){
	for(int i = 0; i < to_examine.size(); ++i)
	{
		if (target == to_examine[i].coor)
			return true;
	}
	return false;
}

vector<pair<int, int> > check_list_creation(vector<string> & lines, vector<pair<int, int> > & alreadychecked, pair<int,int> & current_coor, int width, int height)
{
	pair<int, int> directions[4]={{1,0},{-1,0},{0,1},{0,-1}};
	vector<pair<int, int>> check_list;

	for (int i = 0; i < 4; ++i){
		pair<int,int> coor {current_coor.first + directions[i].first, current_coor.second + directions[i].second};
		if (coor.first < 0 || coor.second < 0 || coor.first > width - 1 || coor.second > height - 1){
			continue;
		}
		char current_char = lines[current_coor.second][current_coor.first];
		char neighbour_char = lines[coor.second][coor.first];
		if (neighbour_char == 'E')
			neighbour_char = 123;
		
		if(current_char == 'S'){
			alreadychecked.push_back(coor);
			check_list.push_back(coor);
		}
		else if(neighbour_char != 'S' && !find_coor(coor, alreadychecked) && ((current_char + 1) >= neighbour_char)){
			check_list.push_back(coor);
		}

	}
	return (check_list);
}

void print_queue(deque<data_t> to_examine){
	for(int i = 0; i < to_examine.size(); ++i){
		cout << "[" << to_examine[i].coor.first << "," << to_examine[i].coor.second << ", "<< to_examine[i].steps <<"] ";
	}
	cout << endl;
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
	
	int width = lines[0].size();
	int height = lines.size();

	deque<data_t> to_examine;
	vector<pair<int,int> > alreadychecked;
	bool found = false;

	data_t start {.coor={0,0},.steps = 0};
	to_examine.push_back(start);

	while (!found){
		
		if(to_examine.empty()){
			cout << "Endpoint has not been found" << endl;
			break;
		}
		data_t exam = to_examine[0];
		to_examine.pop_front();
		alreadychecked.push_back(exam.coor);
		if (lines[exam.coor.second][exam.coor.first] == 'E'){
			cout << "found at x: " << exam.coor.first << "y: "<< exam.coor.second << "steps: "<< exam.steps << endl; 
			found = true;
			break;
		}
		vector<pair<int, int>> check_list = check_list_creation(lines, alreadychecked, exam.coor, width, height);
		for(int i = 0; i < check_list.size(); ++i){
			if (!find_in_queue(check_list[i], to_examine)){
				data_t to_examine_coor{.coor = check_list[i], .steps = exam.steps + 1};
				to_examine.push_back(to_examine_coor);
			}
		}
	}

	inputfile.close();
	return (0);
}