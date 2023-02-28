#include <iostream>
#include <fstream>
#include <vector>

enum OP
{
	FAILURE,
	SUCCESS
};

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

void	print_stack(std::vector<char> stacks[], int amount_stacks)
{
	for (int i = 0; i < amount_stacks; ++i)
	{
		std::cout << "stack " << i +1 << " : ";
		for(int j = 0; j < stacks[i].size(); ++j)
		{
			std::cout << stacks[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void	create_stacks(std::ifstream & inputfile, std::vector<char> stacks[], int amount_stacks, int height)
{
	std::string line;

	for (int i = 0; i < height; ++i)
	{
		std::getline(inputfile, line);
		int line_size = line.size();

		for(int j = 0; j < amount_stacks; ++j)
		{
			int pos = j * 4 + 1;
			if(pos < line_size)
			{
				if(line[pos] != ' ')
					stacks[j].insert(stacks[j].begin(),line[pos]);
			}
		}
	}
}

OP move_crates(int amount, int srcstack,int deststack, std::vector<char> stacks[], int amount_stacks)
{

	int srcstack_size = stacks[srcstack -1].size();
	if(stacks[srcstack-1].empty())
		return (FAILURE);
	for(int i =0 ; i < amount; ++i)
	{
		stacks[deststack -1].push_back(stacks[srcstack -1][srcstack_size - amount + i]);
	}
	for (int i = 0; i < amount; ++i)
		stacks[srcstack - 1].pop_back();
	return SUCCESS;
}

void	print_answer(std::vector<char> stacks[], int amount_stacks)
{
	for(int i = 0; i < amount_stacks; ++i)
	{
		if(stacks[i].empty())
			std::cout << " ";
		else
			std::cout << stacks[i].back();
	}
	std::cout << std::endl;
}

int main()
{
	// std::ifstream myfile("example.txt");
	// int amount_of_stacks = 3;
	// std::vector<char> stacks[3]{{'Z','N'},{'M','C','D'},{'P'}};
	
	// std::ifstream myfile("input.txt");
	// int amount_of_stacks = 9;
	// std::vector<char> stacks[9]{
	// 	{'S','M','R','N','W','J','V','T'},
	// 	{'B','W','D','J','Q','P','C','V'},
	// 	{'B','J','F','H','D','R','P'},
	// 	{'F','R','P','B','M','N','D'},
	// 	{'H','V','R','P','T','B'},
	// 	{'C','B','P','T'},
	// 	{'B','J','R','P','L'},
	// 	{'N','C','S','L','T','Z','B','W'},
	// 	{'L','S','G'}
	// };

	std::ifstream myfile("input.txt");
	int amount_of_stacks = 9;
	int initial_max_height_stack = 8;
	std::vector<char> stacks[9];
	create_stacks(myfile, stacks, amount_of_stacks, initial_max_height_stack);

	print_stack(stacks, amount_of_stacks);

	std::string line;
	getline(myfile, line);
	getline(myfile, line);

	while(std::getline(myfile, line))
	{
		std::vector<std::string> input = strsplit(line, " ");
		if(move_crates(std::stoi(input[1]), std::stoi(input[3]), std::stoi(input[5]), stacks, amount_of_stacks ) == FAILURE)
		{
			std::cout << "moving crates has gone wrong" << std::endl;
			myfile.close();
			return (1);
		}
	}

	print_answer(stacks, amount_of_stacks);
	myfile.close();
	return (0);
}