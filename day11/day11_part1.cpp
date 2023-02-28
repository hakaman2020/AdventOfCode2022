#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

enum e_operation
{
	MULTIPLY,
	ADD,
	POWER
};

enum e_displaytype{
	SHORT,
	LONG
};

typedef struct s_monkey
{
	int number;
	deque<int> items;
	e_operation op;
	int opnumber;
	int test;
	int test_true;
	int test_false;
	int items_inspected;
}				monkey_t;

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

void read_file(ifstream & inputfile, vector<string> & lines){
	string line;
	while(getline(inputfile, line))
		lines.push_back(line);
}

void init_monkey(monkey_t & monkey, vector<string> lines, int i){
	vector<string> split = strsplit(lines[i]," ");
	monkey.number = stoi(split[1]);

	split = strsplit(lines[i+1], " ");
	for(int j = 2; j < split.size(); j++){
		monkey.items.push_back(stoi(split[j]));
	}

	split = strsplit(lines[i+2], " ");
	if (split[4].compare("*") == 0 && split[5].compare("old") == 0){
		monkey.op = POWER;
		monkey.opnumber = 2;
	}
	else if (split[4].compare("*") == 0 ){
		monkey.op = MULTIPLY;
		monkey.opnumber = stoi(split[5]);
	}
	else if (split[4].compare("+") == 0 ){
		monkey.op = ADD;
		monkey.opnumber = stoi(split[5]);
	}

	split = strsplit(lines[i+3], " ");
	monkey.test = stoi(split[3]);

	split = strsplit(lines[i+4], " ");
	monkey.test_true = stoi(split[5]);

	split = strsplit(lines[i+5], " ");
	monkey.test_false = stoi(split[5]);

	monkey.items_inspected = 0;
}

void	print_monkey(monkey_t & monkey, e_displaytype dt){
	cout << "monkey " << monkey.number <<": ";
	if (dt == SHORT){
		for(int i = 0; i < monkey.items.size(); ++i){
			cout << monkey.items[i];
			if(i != monkey.items.size() -1)
				cout << ", ";
		}
		cout << endl;
	}
	else if (dt == LONG){
		cout << endl;
		cout << "items :";
		for (int i = 0; i < monkey.items.size(); ++i){
			cout << monkey.items[i];
			if (i != monkey.items.size() - 1)
				cout << ", ";
		}
		cout << endl;
		cout << "monkey op : ";
		if(monkey.op == POWER)
			cout << "POWER OF " << monkey.opnumber << endl;
		else if (monkey.op == MULTIPLY)
			cout << "MULTIPLY BY " << monkey.opnumber << endl;
		else
			cout << "ADD BY " << monkey.opnumber <<endl;
		cout << "Test: divisible by " << monkey.test << endl;
		cout << "  If true : throw to monkey " << monkey.test_true << endl;
		cout << "  If false : throw to monkey " << monkey.test_false << endl;
		cout << endl;
	}

}

void	process_monkey(monkey_t monkeys[], int amount_of_monkeys, monkey_t & monkey){
	
	int itemlist_size = monkey.items.size();
	if(itemlist_size == 0)
		return;

	int newitem = 0;
	for(int i = 0; i < itemlist_size; ++i){
		newitem = monkey.items[i];
		monkey.items_inspected++;
		if (monkey.op == POWER)
			newitem *= newitem;
		else if (monkey.op == ADD)
			newitem += monkey.opnumber;
		else if (monkey.op == MULTIPLY)
			newitem *= monkey.opnumber;
		newitem /= 3;
		if ((newitem % monkey.test) == 0){
			monkeys[monkey.test_true].items.push_back(newitem);
		}
		else{
			monkeys[monkey.test_false].items.push_back(newitem);
		}
	}
	monkey.items.clear();
}


int main(int argc, char ** argv){
	if(argc != 2)
	{
		cout << "Program must have one argument." << endl;
		return (1);
	}
	
	ifstream inputfile(argv[1]);
	if(!inputfile.is_open())
	{
		cout << "Error opening file" << endl;
		return (1);
	}
	vector<string> lines;
	read_file(inputfile, lines);
	
	int amount_monkeys  = 1 + (lines.size() - 6) / 7;
	int amount_of_rounds = 20;
	monkey_t monkeys[amount_monkeys];

	for(int i = 0; i < amount_monkeys; ++i){
		init_monkey(monkeys[i],lines, i * 7);
		//print_monkey(monkeys[i], LONG);
	}

	for(int round = 1; round <= amount_of_rounds; round++){
		cout << "round " << round << endl;
		for(int i = 0; i < amount_monkeys; ++i){
			process_monkey(monkeys, amount_monkeys, monkeys[i]);
		}
		for(int i = 0; i < amount_monkeys; ++i){
			print_monkey(monkeys[i], SHORT);
		}
	}

	int highest[2]={0,0};
	for(int i = 0; i < amount_monkeys; ++i){
		int amount_inspected = monkeys[i].items_inspected;
		if(amount_inspected >= highest[0]){
			highest[1] = highest[0];
			highest[0] = amount_inspected;
		}
		else if(amount_inspected >= highest[1]){
			highest[1] = amount_inspected;
		}
	}

	cout << "total " << highest[0] * highest[1] << endl;

	inputfile.close();
	return (0);
}