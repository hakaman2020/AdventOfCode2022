#include <iostream>
#include <fstream>


int	get_lowest_top3(int max[3], int elfnumber_max[3])
{
	int lowest_index 	= 0;

	for(int i = 1; i < 3; ++i)
	{
		if(max[i] < max[lowest_index])
			lowest_index = i;
	}
	return lowest_index;
}





int main()
{
	std::ifstream myfile("input.txt");

	std::string line;
	int total				= 0;
	int current_elf_number	= 1;
	int max[3]{0,0,0};
	int elfnumber_max[3]{0,0,0};	

	while(std::getline(myfile, line))
	{
		if (line.empty())
		{
			int lowest_index = get_lowest_top3(max, elfnumber_max);
			if(total > max[lowest_index])
				max[lowest_index] = total;
				elfnumber_max[lowest_index] = current_elf_number;
			current_elf_number++;
			total = 0;
		}
		else
		{
			total += std::stoi(line);
		}
	}
	total = 0;
	for(int i = 0; i < 3 ; ++i)
	{
		total += max[i];
	}
	std::cout << "\ntotal calorie top 3:" << total<< std::endl;
	return (0);
}