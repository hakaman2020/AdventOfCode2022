#include <iostream>
#include <vector>

std::vector<std::string> strsplit(std::string str, std::string delimiter)
{
	std::vector<std::string> result;
	size_t index = 0;
	size_t lenght = str.size();
	while(index < lenght)
	{
		std::string token;

		size_t pos = str.find(delimiter, index);
		if (pos != std::string::npos)
			token = str.substr(index, pos - index);
		else
			token = str.substr(index, lenght - 1);
		result.push_back(token);
		if (pos == std::string::npos)
			break;
		index = pos + 1;
	}
	return (result);
}


int main()
{
	std::string test = "";
	std::vector<std::string> split = strsplit(test,",");
	if (split.empty())
	{
		std::cout << "vector empty" << std::endl;
		return (0);
	}
	for(std::string i: split)
		std::cout << i << std::endl;
	std::cout << std::endl;
}