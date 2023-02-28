#include <iostream>
#include <fstream>

int determine_prio(char c)
{
	if (islower(c))
		return c - 96;
	else
		return c - 38;
}

char find_badge(std::string group[3])
{
	for (int i = 0; i < group[0].size(); ++i)
	{
		if (group[1].find(group[0][i]) != std::string::npos && group[2].find(group[0][i]) != std::string::npos)
			return group[0][i];
	}
}

int main()
{
	std::string line;
	int strsize = 0;
	int total = 0;
	int count = 0;
	std::string group[3];
	
	std::ifstream myfile("input.txt");

	while (std::getline(myfile, line))
	{
		group[count] = line;
		if (count == 2)
			total += determine_prio(find_badge(group));
		count = (count + 1) % 3;
	}

	std::cout << total << std::endl;
	return (0);
}