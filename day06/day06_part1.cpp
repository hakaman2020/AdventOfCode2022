#include <iostream>
#include <fstream>
#include <vector>

unsigned int determine_buffersize(std::string line)
{
	for (unsigned int j = 3; j < line.size(); ++j)
	{
		if(line[j] != line[j - 1] && line[j] != line[j -2] && line[j] != line[j -3]
		&& line[j- 1] != line[j -2] && line[j -1] != line[j -3] && line[j -2] != line[j -3])
			return j + 1;
		
	}
	return 0;
}

int main()
{
	// std::ifstream myfile("example.txt");
	std::ifstream myfile("input.txt");

	std::string line;
	std:getline(myfile, line);
	std::cout << determine_buffersize(line) << std::endl;

	myfile.close();
	return (0);
}