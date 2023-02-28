#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

vector<string> strsplit(string str, string delimiter){
	vector<string> result;
	size_t length = str.size();
	size_t next_pos = 0;
	size_t index = str.find_first_not_of(delimiter, 0);
	
	while(index < length){
		string token;
		next_pos = str.find(delimiter, index);
		if (next_pos != string::npos)
			token = str.substr(index, next_pos - index);
		else
			token = str.substr(index, length - index);
		result.push_back(token);
		index = str.find_first_not_of(delimiter, next_pos);
	}
	return (result);
}

void read_file(std::ifstream & inputfile, std::vector<std::string> & lines)
{
	std::string line;

	while(std::getline(inputfile, line))
		lines.push_back(line);
}

void add_filesize_to_dirs(vector<string> & current_path, map<string,long> &dirsize, long filesize)
{
	map<string, long>::iterator itr;
	for(size_t i = 0; i < current_path.size(); ++i)
	{
		string path = "/";
		for(size_t j = 1; j < (current_path.size() - i); ++j)
			path = path + current_path[j] + "/";
		itr = dirsize.find(path);
		if (itr != dirsize.end())
			dirsize[path] += filesize;
		else
			dirsize[path] = filesize;
	}
}

long count_total_size(map<string, long> dirsize)
{
	long total = 0;
	map<string, long>::iterator itr;

	for(itr = dirsize.begin(); itr != dirsize.end(); itr++)
	{
		if(itr->second <= 100000)
			total += itr->second;
	}
	return (total);
}

int main(int argc, char ** argv)
{
	if(argc != 2)
	{
		std::cout << "Program will only accept one argument" << endl;
		return (1);
	}

	ifstream inputfile(argv[1]);
	if(!inputfile.is_open())
	{
		std::cout << "Error opening file" << endl;
		return (1);
	}
	vector<string> lines;
	read_file(inputfile, lines);

	map<string, long> dirsize;
	vector<string> current_path;

	for(int i = 0; i < lines.size(); ++i)
	{
		vector<string> split = strsplit(lines[i], " ");
		if(split[0].compare("$") == 0)
		{
			if (split[1].compare("cd") == 0 && split[2].compare("..") == 0)
				current_path.pop_back();
			else if (split[1].compare("cd") == 0)
				current_path.push_back(split[2]);
			else if (split[1].compare("ls") == 0)
			{
				i++;
				while(lines[i][0] != '$')
				{
					vector<string> tmpsplit = strsplit(lines[i]," ");
					if(tmpsplit[0].compare("dir") != 0)
					{
						long filesize = stol(tmpsplit[0], NULL);
						add_filesize_to_dirs(current_path, dirsize, filesize);
					}
					++i;
					if(i >= lines.size())
						break;
				}
				--i;
			}
		}
		
	}
	long total = count_total_size(dirsize);
	std::cout << total << endl;
	inputfile.close();
	return (0);
}