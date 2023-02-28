#include <iostream>
#include <fstream>
#include <string>

# define ERROR -1
# define NOT_FOUND -2

bool	is_unique(std::string line, size_t pos, size_t amount_unique)
{
	if (pos + amount_unique > line.size())
		return false;
	for(int i = 0; i < amount_unique; ++i)
	{
		for(int j = 1; j < amount_unique - i; ++j)
		{
			if(line[pos + i] == line [pos + i + j])
				return false;
		}
	}
	return true;
}	

int determine_buffersize(std::string line, size_t amount_unique)
{
	if(line.size()< amount_unique)
		return ERROR;
	for(int i = 0; i <= line.size() - amount_unique; ++i)
	{
		if(is_unique(line, i, amount_unique))
			return (i + amount_unique); 
	}
	return NOT_FOUND;
}

int main()
{
	std::ifstream myfile("example.txt");

	std::string line;
	std:getline(myfile, line);
	std::cout << determine_buffersize(line, 4) << std::endl;
	myfile.close();
	return (0);
}