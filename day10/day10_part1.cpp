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

void read_file(std::ifstream & inputfile, std::vector<std::string> & lines)
{
	std::string line;
	while(std::getline(inputfile, line))
	{
		lines.push_back(line);
	}
}

pair<int,int> get_next_command(vector<string> lines, int i)
{
	pair<int,int> command;
	vector<string> line = strsplit(lines[i], " ");
	if(line[0].compare("noop") == 0)
	{
		command.first = 1;
		command.second = 0;
	}
	else
	{
		command.first = 2;
		command.second = stoi(line[1],NULL);
	}
	return command;
}

int get_signal_strenght(int cycle, int x)
{
	if(cycle == 20 || cycle == 60 || cycle == 100 || cycle == 140 || cycle == 180 || cycle == 220)
	{
		return (cycle * x);
	}
	return 0;
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
	
	int cycle = 0;
	int x = 1;
	int command_line = 0;
	int commmandcycles = 0;
	int deltax = 0;
	int signal_strenght = 0;

	pair<int,int> command;

	while(1)
	{
		cycle++;
		if (commmandcycles == 0)
		{
			x += deltax;
			if (command_line == lines.size())
				break;
			command = get_next_command(lines, command_line);
			commmandcycles = command.first;
			deltax = command.second;
			command_line++;
		}
		cout << "start cycle " << cycle << " value x " << x << endl;
		signal_strenght += get_signal_strenght(cycle,x);
		commmandcycles--;
	}
	cout << "start cycle " << cycle << " value x " << x << endl;
	cout << "total signal strength " << signal_strenght << endl;
	inputfile.close();
	return (0);
}