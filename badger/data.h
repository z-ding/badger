#pragma once
class cell {
public:
	virtual void* get_content() { //getter, return void ptr so that base and derive class can return the same type
		std::cout << "virtual function of base class" << std::endl;
		return nullptr;
	}
};

class str_cell : public cell {
private:
	std::string content;
public:
	str_cell(std::string x) {
		content = x;
	}
	void* get_content() {
		//std::cout << content << " ; ";
		return &content;
	}
};

class int_cell : public cell {
private:
	int content;
public:
	int_cell(int x) {
		content = x;
	}
	void* get_content() {
		//std::cout << content << " ; ";
		return &content;
	}
};

void data_overview(std::vector<std::vector<std::shared_ptr<cell>>>& table, std::unordered_map<int, int>& data_type, int rows);
bool asd_sort(std::shared_ptr<cell> a, std::shared_ptr<cell> b, int c, std::unordered_map<int, int>& data_type);
bool dsd_sort(std::shared_ptr<cell> a, std::shared_ptr<cell> b, int c, std::unordered_map<int, int>& data_type);
void dynamic_sort(std::vector<std::vector<std::shared_ptr<cell>>>& table, int col, std::unordered_map<int, int>& data_type,
	bool (*sort_fcnPtr)(std::shared_ptr<cell> a, std::shared_ptr<cell> b, int c, std::unordered_map<int, int>& data_type));