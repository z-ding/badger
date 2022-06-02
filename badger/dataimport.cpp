#include<iostream>
#include<vector>
#include<string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <memory>
#include<algorithm>
#include "data.h"

void transpose_load_csv_totable(int c, std::vector<std::vector<std::shared_ptr<cell>>>& table, std::string s,
	std::unordered_map<int, int> &data_type) {
	if (data_type[c] ==0) { //string
		table[c].emplace_back(std::make_shared<str_cell>(s));
	}
	else {
		table[c].emplace_back(std::make_shared<int_cell>(std::stoi(s)));
	}
}

void load_csv_totable(int c, std::vector<std::vector<std::shared_ptr<cell>>>& table, std::string s,
	std::unordered_map<int, int>& data_type, std::vector<std::shared_ptr<cell>> &col) {
	if (data_type[c] == 0) { //string
		col.emplace_back(std::make_shared<str_cell>(s));
	}
	else {
		col.emplace_back(std::make_shared<int_cell>(std::stoi(s)));
	}
}


int main() {
	std::vector<std::vector<std::shared_ptr<cell>>> table; //shared_ptr<> no need to use * in <>
	std::vector<std::string> col_name;//vector of strings to read csv content
	int columns = 0; 
	std::cout << "enter the number of columns in the csv file >>> ";
	std::cin >> columns;
	//create data type info for each column
	std::unordered_map<int, int> data_type;

	for (int i = 0; i < columns; i++) {
		std::string s;
		col_name.push_back(s); //empty string for reading csv later
		int type = 0;
		std::cout << "enter the data type of column " << i <<" 0 for string, 1 for int: ";
		std::cin >> type;
		data_type.emplace(i, type);
		//std::vector<std::shared_ptr<cell>> col;
		//table.emplace_back(col);//now there are x empty col vector for x columns
	}
	//import file
	std::ifstream churn_data("churn_data.csv");
	if (!churn_data.is_open()) { //make sure the file is open
		std::cout << "csv failed open" << std::endl;
		return 0;
	}

	
	while (std::getline(churn_data, col_name[0], ',')) {
		std::vector<std::shared_ptr<cell>> col;
		load_csv_totable(0,table, col_name[0], data_type,col);
		for (int i = 1; i < columns-1; i++) {
			getline(churn_data, col_name[i], ',');
			load_csv_totable(i,table, col_name[i], data_type,col);
		}
		getline(churn_data, col_name[columns-1], '\n');
		load_csv_totable(columns - 1,table, col_name[columns - 1], data_type,col);
		table.emplace_back(col);
	}

	data_overview(table, data_type, 50);
	dynamic_sort(table, 0, data_type, asd_sort);
	std::cout << "after ascending sort column 0" << std::endl;
	data_overview(table, data_type, 10);

	dynamic_sort(table, 7, data_type, dsd_sort);
	std::cout << "after descending sort column 7" << std::endl;
	data_overview(table, data_type, 10);

	return 0;
}