#include <iostream>
#include <fstream>
#include <sstream>

void find_ranges(std::string input, int range[4])
{
	std::istringstream inputline;
	std::string line;
	inputline.str(input.c_str());
	std::getline(inputline, line, '-');
	range[0] = std::stoi(line);
	std::getline(inputline, line, ',');
	range[1] = std::stoi(line);
	std::getline(inputline, line, '-');
	range[2] = std::stoi(line);
	std::getline(inputline, line);
	range[3] = std::stoi(line);
}

int main()
{
	// std::ifstream myfile("example.txt");
	std::ifstream myfile("input.txt");

	std::string line;
	int range[4];
	int count = 0;

	while (std::getline(myfile, line))
	{
		count++;
		find_ranges(line, range);
		if (range[1] < range[2] || range[0] > range[3])
			count--;
	}
	myfile.close();
	std::cout << count << std::endl;
	return (0);
}