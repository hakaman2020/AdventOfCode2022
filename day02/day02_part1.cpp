#include <iostream>
#include <fstream>

int points(char opponent, char you)
{
	int score = 0;
	if (you == 'X')
		score +=1;
	else if (you == 'Y')
		score +=2;
	else if (you == 'Z')
		score +=3;
	you -= 23;

	if(opponent == you)
		score += 3;
	else if (opponent - you == 1 || opponent - you == -2)
		score += 0;
	else
		score += 6;
	return (score);
}

int main()
{
	std::ifstream myfile("input.txt");

	std::string line;
	int totalscore = 0;

	while(std::getline(myfile, line))
	{
		totalscore += points(line[0], line[2]);
	}
	std::cout << totalscore << std::endl;
	return (0);
}