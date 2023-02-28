#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

typedef enum direction_e{
	DOWN,
	LEFT,
	RIGHT,
	STOP,
	ABYSS,
	OUTBOUND

} direction_t;

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

void	read_file(ifstream & inputfile, vector<string> & lines){
	string line;
	while(getline(inputfile, line))
		lines.push_back(line);
}

void	determine_limits(int & max_x, int & min_x, int & max_y, int & min_y, vector<string>lines){
	max_x = 0;
	min_x = 999;
	max_y = 0;
	min_y = 999;

	for(int i = 0; i < lines.size(); ++i){
		vector<string> split = strsplit(lines[i], " ");
		for(int j = 0; j < split.size(); j = j + 2){
			vector<string>split2 = strsplit(split[j],",");
			int x = stoi(split2[0]);
			int y = stoi(split2[1]);
			if(x < min_x)
				min_x = x;
			if(x > max_x)
				max_x = x;
			if(y < min_y)
				min_y = y;
			if(y > max_y)
				max_y = y;
		}
	}
}

char**	init_map(int width, int height){
	char** map = new char*[height];
	for(int i = 0; i < height; ++i){
		map[i] = new char[width];
	}

	for(int y = 0; y < height; ++y){
		for(int x= 0; x < width; ++x){
			map[y][x] = '.';
		}
	}
	return map;
}

void	draw_line(char **map, int x1, int y1, int x2, int y2){
	int start;
	int end;
	if (x1 == x2){
		start = y1;
		end = y2;
		if(y1 > y2){
			start = y2;
			end = y1;
		}
		for (int i = start; i <= end; i++){
			map[i][x1] = '#';
		}
	}
	else{
		start = x1;
		end = x2;
		if(x1 > x2){
			start = x2;
			end = x1;
		}
		for (int i = start; i <= end; i++){
			map[y1][i] = '#';
		}
	}
}

void	set_map(char **map, int width, int height, vector<string> lines, int offset){
	for(int i = 0; i < lines.size(); ++i){
		vector<string> split = strsplit(lines[i], " ");
		for(int j = 0; j < split.size() - 2; j = j + 2){
			vector<string>start = strsplit(split[j],",");
			vector<string>end = strsplit(split[j + 2],",");
			int startx = stoi(start[0]) - 500 + offset;
			int starty = stoi(start[1]);
			int endx = stoi(end[0]) - 500 + offset;
			int endy = stoi(end[1]);
			draw_line(map, startx, starty, endx, endy);
		}
	}
	map[0][offset] ='+';
}

void	print_map(char **map, int width, int height){
	for(int y = 0; y < height; ++y){
		for(int x=0; x < width; ++x){
			cout << map[y][x];
		}
		cout << endl;
	}
}

direction_t next_direction(char ** map,int width, int height, pair<int, int> coor){
	int x = coor.first;
	int y = coor.second;

	if (y == height - 1){
		return ABYSS;
	}
	if (map[y + 1][x] == '.'){
		return DOWN;
	}
	if (x == 0){
		return OUTBOUND;
	}
	if(map[y +1][x -1] == '.'){
		return LEFT;
	}
	if(x == width - 1){
		return OUTBOUND;
	}
	if(map[y+1][x+1] == '.'){
		return RIGHT;
	}
	return STOP;
}

pair<int, int> simulate_drop(char **map, int width, int height, pair<int, int> coor){
	direction_t 	next = DOWN;
	bool			done = false;
	pair<int, int>	final_pos = coor;

	while (done == false)
	{
		next = next_direction(map, width, height, coor);
		if(next == LEFT){
			final_pos.first--;
			final_pos.second++;
		}else if(next == RIGHT){
			final_pos.first++;
			final_pos.second++;
		}else if(next == DOWN){
			final_pos.second++;
		}
	}

}

// int	start_simulation(char **map, int offset, int width, int height){
// 	pair<int, int> start{0,offset};
// 	pair<int,int> last_pos = start;
// 	direction_t direct = DOWN;
// 	int amount = 1;
// 	while(direct != ABYSS && direct != OUTBOUND && direct != STOP)

	

// }

int main(int argc, char ** argv){
	if(argc != 2){
		cout << "Program must have one argument." << endl;
		return (1);
	}
	
	ifstream inputfile(argv[1]);
	if(!inputfile.is_open()){
		cout << "Error opening file" << endl;
		return (1);
	}
	vector<string> lines;
	read_file(inputfile, lines);
	
	int max_x, min_x, max_y, min_y;
	determine_limits(max_x, min_x, max_y, min_y, lines);
	cout << max_x << " " << min_x <<  " " << max_y << " " << min_y << endl;
	int width = max_x - min_x + 3;
	int height = max_y + 2;
	int offset = 500 - min_x + 1;

	char** map = init_map(width,height);
	set_map(map, width, height, lines, offset);


	print_map(map,width, height);
	inputfile.close();
	return (0);
}