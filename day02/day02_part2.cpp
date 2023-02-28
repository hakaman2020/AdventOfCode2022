#include <iostream>
#include <fstream>

int points(char opponent, char you)
{
	int score = 0;
	if (you == 'Z')
	{
		score += 6;
		if(opponent == 'A')
			score +=2;
		else if(opponent == 'B')
			score +=3;
		else if(opponent == 'C')
			score +=1;
	}
	else if(you == 'Y')
	{
		score += 3;
		if(opponent == 'A')
			score +=1;
		else if(opponent == 'B')
			score +=2;
		else if(opponent == 'C')
			score +=3;
	}
	else if (you == 'X')
	 {
		score += 0;
	
		if(opponent == 'A')
			score +=3;
		else if(opponent == 'B')
			score +=1;
		else if(opponent == 'C')
			score +=2;
	 }
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