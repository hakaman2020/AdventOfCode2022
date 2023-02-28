#include <iostream>
#include <fstream>

int main()
{
	std::ifstream myfile("examplep.txt");

	std::string line;
	int total				= 0;
	int max 				= 0;
	int current_elf_number	= 1;
	int elfnumber_max 		= 0;

	while(std::getline(myfile, line))
	{
		if (line.empty())
		{
			if (total > max)
			{
				elfnumber_max = current_elf_number;
				max = total;
			}
			current_elf_number++;
			total = 0;
		}
		else
		{
			total += std::stoi(line);
		}
	}
	
	std::cout << std::getline(myfile, line) << std::endl;
	if (total > max)
		max = total;
	
	std::cout	<< "elfnumber :" << elfnumber_max 
				<< "\ntotal calorie :" << max<< std::endl;
	return (0);
}