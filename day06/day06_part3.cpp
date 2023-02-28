#include <iostream>
#include <fstream>
#include <set>

int main()
{
	// std::ifstream myfile("example.txt");
	std::ifstream myfile("input.txt");
	std::string line;
	std:getline(myfile, line);

	int amount = 4;
	for(int i = 0; i <= line.size() - amount; ++i)
	{
		std::set<char>str(&line[i], &line[i + amount]);
		if(str.size() == amount)
		{
			std::cout << i + amount << std::endl;
			break;
		}
	}
	myfile.close();
	return (0);
}