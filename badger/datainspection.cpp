#include<iostream>
#include<vector>
#include<string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include<algorithm>
#include "data.h"

void data_overview(std::vector<std::vector<std::shared_ptr<cell>>>& table, std::unordered_map<int, int> &data_type, int rows) {
	
	//view ttl number of rows and columns
	std::cout << "number of columns " << table[0].size() << '\n' <<
		"number of rows " << table.size()<< std::endl;

	//overview of datatype
	for (auto &elem: data_type) {
		if (elem.second == 0) {
			std::cout << "Column number: " << elem.first << " : string" << std::endl;
		}
		else {
			std::cout << "Column number: " << elem.first << " : integer" << std::endl;
		}
	}
	//view top x rows
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < table[0].size(); j++) {
			if (data_type[j] == 0) {
				std::cout << *(std::string*)table[i][j]->get_content() << " ";
			}
			else {
				std::cout << *(int*)table[i][j]->get_content() << " ";
			}	
		}
		std::cout << std::endl;
	}

}

bool asd_sort(std::shared_ptr<cell> a, std::shared_ptr<cell> b, int c, std::unordered_map<int, int>& data_type) { //sort in ascending order
	if (data_type[c] == 0) {
		return (*(std::string*)a->get_content() < *(std::string*)b->get_content());
	}
	else {
		return (*(int*)a->get_content() < *(int*)b->get_content());
	}
}
bool dsd_sort(std::shared_ptr<cell> a, std::shared_ptr<cell> b, int c, std::unordered_map<int, int>& data_type) { //sort in descending order
	if (data_type[c] == 0) {
		return (*(std::string*)a->get_content() > *(std::string*)b->get_content());
	}
	else {
		return (*(int*)a->get_content() > *(int*)b->get_content());
	}
}
typedef bool(*sort_fcnPtr)(std::shared_ptr<cell> a, std::shared_ptr<cell> b, int c, std::unordered_map<int, int>& data_type);
void dynamic_sort(std::vector<std::vector<std::shared_ptr<cell>>>& table, int col, std::unordered_map<int, int>& data_type,
	sort_fcnPtr s_ptr) {
	std::sort(table.begin(), table.end(), [col, &data_type, s_ptr](const std::vector<std::shared_ptr<cell>>& A, 
		const std::vector<std::shared_ptr<cell>>& B) {
		 return s_ptr(A[col], B[col], col, data_type);
		});
}



