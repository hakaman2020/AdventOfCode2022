#include <iostream>
#include <fstream>

int determine_prio(char c)
{
	if(islower(c))
		return c - 96;
	else
		return c - 38;
}

int main()
{
	std::ifstream myfile("input.txt");

	std::string line;
	int strsize =0;
	int total = 0;

	while(std::getline(myfile, line))
	{
		int strsize = line.size();
		std::string secondpart = line.substr(strsize/2,strsize/2);
		for(int i = 0 ; i < strsize/2; ++i)
		{
			if (secondpart.find(line[i],0) != std::string::npos)
			{
				total += determine_prio(line[i]);
				break;
			}
		}
	}
	std::cout << total << std::endl;
	return (0);
}