#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

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

void sieveleft(vector<string> & copy)
{
	for(int y = 1; y < copy.size() -1; y++)
	{
		char max = '0';
		for(int x = 0; x < copy[0].size() -1 ;x++)
		{
			if(copy[y][x] > max)
				max = copy[y][x];
			else
				copy[y][x] = '0';
		}
	}
}
void sieveright(vector<string> & copy)
{
	for(int y = 1; y < copy.size() -1; y++)
	{
		char max = '0';
		for(int x = copy[0].size() - 1; x > 0 ;x--)
		{
			if(copy[y][x] > max)
				max = copy[y][x];
			else
				copy[y][x] = '0';
		}
	}
}

void sievetop(vector<string> & copy)
{
	for(int x = 1; x < copy[0].size() -1; x++)
	{
		char max = '0';
		for(int y = 0; y < copy.size() -1 ;y++)
		{
			if(copy[y][x] > max)
				max = copy[y][x];
			else
				copy[y][x] = '0';
		}
	}
}

void sievebottom(vector<string> & copy)
{
	for(int x = 1; x < copy[0].size() -1; x++)
	{
		char max = '0';
		for(int y = copy.size() -1; y >0 ;--y)
		{
			if(copy[y][x] > max)
				max = copy[y][x];
			else
				copy[y][x] = '0';
		}
	}
}

void combine(vector<string> & result, vector<string> sieve)
{
	for(int y = 0 ; y < result.size(); y++)
	{
		for(int x = 0; x < result[0].size(); x++)
		{
			if(result[y][x] == '0' && sieve[y][x] != '0')
				result[y][x] = sieve[y][x];
		}
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

	vector<string> result = lines;
	sieveleft(result);
	vector<string> sieve = lines;
	sieveright(sieve);
	combine(result, sieve);
	sieve = lines;
	sievetop(sieve);
	combine(result, sieve);
	sieve = lines;
	sievebottom(sieve);
	combine(result, sieve);

	int count =0;
	for(int y = 1 ; y < result.size() - 1; y++)
	{
		for(int x = 1; x < result[0].size() -1 ; x++)
		{
			if(result[y][x] != '0')
				count ++;
		}
	}
	int width = lines[0].size();
	int height = lines.size();
	count =  count + 2 * width + (2 * height) -4;

	cout << count<< endl;
	inputfile.close();
	return (0);
}