#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>
#include <cmath>

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

void read_file(std::ifstream & inputfile, std::vector<std::string> & lines)
{
	std::string line;
	while(std::getline(inputfile, line))
	{
		lines.push_back(line);
	}
}


void move_tail(pair<int,int> &head, pair<int,int> &tail, map<pair<int,int>, int> &tailtrail)
{
	int dx = head.first - tail.first;
	int dy = head.second - tail.second;

	if((dy == 0 && dx != 0) || (dy != 0 && dx == 0))
	{
		tail.first = (head.first + tail.first) / 2;
		tail.second = (head.second + tail.second) / 2;
	}
	else
	{
		if(dx > 0)
			tail.first += 1;
		else
			tail.first += -1;
		if(dy > 0)
			tail.second += 1;
		else
			tail.second += -1;
	}
	map<pair<int,int>,int>::iterator itr;
	itr = tailtrail.find(tail);
	if( itr != tailtrail.end())
		tailtrail[tail] += 1;
	else
		tailtrail[tail] = 1;
}

void execute_move(int steps, int dx, int dy, pair<int,int> &head, pair<int,int> &tail, map<pair<int,int>,int> &tailtrail)
{
	for( int i = 0; i < steps; i++)
	{
		head.first += dx;
		head.second += dy;
		if( tail.first - head.first == 2 || tail.first - head.first == -2 || tail.second - head.second == 2 || tail.second - head.second == -2)
			move_tail(head, tail, tailtrail);
	}
}

void process_moves(vector<string> &lines, pair<int,int> &head, pair<int,int> &tail, map<pair<int,int>, int> &tailtrail)
{

	for(int i = 0; i < lines.size(); i++)
	{
		vector<string> split = strsplit(lines[i]," ");
		if(split[0].compare("U") == 0)
			execute_move(stoi(split[1],0), 0, 1,head, tail, tailtrail);
		else if(split[0].compare("D") == 0)
			execute_move(stoi(split[1],0), 0, -1,head, tail, tailtrail);
		else if(split[0].compare("L") == 0)
			execute_move(stoi(split[1],0), -1, 0,head, tail, tailtrail);
		else if(split[0].compare("R") == 0)
			execute_move(stoi(split[1],0), 1, 0,head, tail, tailtrail);
	}
}

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		std::cout << "Program must have one argument." << std::endl;
		return (1);
	}
	std::ifstream inputfile(argv[1]);
	if(!inputfile.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return (1);
	}
	std::vector<std::string> lines;
	read_file(inputfile, lines);
	
	pair<int, int> head{0,0};
	pair<int, int> tail{0,0};
	map<pair<int,int>, int> tailtrail;
	tailtrail[tail] = 1;
	process_moves(lines, head, tail,tailtrail);

	map<pair<int,int>,int>::iterator itr;
	for(itr = tailtrail.begin(); itr != tailtrail.end(); itr++)
		cout << "[" <<itr->first.first <<","<< itr->first.second << "] :" << itr->second;
	cout << endl;
	cout << "count = " << tailtrail.size() << endl;

	inputfile.close();
	return (0);
}