// g++ -O3 -Wall -o a MakePage.cpp -static
// なんかMinGW5.3.0だとgetlineで死んで2h無駄にした

/*******INCLUDE HEADER***********/
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm> // std::getline
#include <windows.h>
//#include <direct.h>
//#include <sys/stat.h>
//#include <cassert>
#include <filesystem>

/******* GLOBAL VARIABLES ***********/
namespace gloval_values {
	const char* PAGE_LIST = "PageList.csv";
}
using namespace gloval_values;
using namespace std;

/******* TYPES ***********/
// csv item
struct Item {
	int level;
	char page_name[256];
	int other;
};

/******* FUNCTION PROTOTYPES ***********/
int MainFunc();

bool MyMkdir(const string &paths) {

	//std::filesystem::create_directory("a");
	// 暫定的にコメントアウト
	/*if (_mkdir(path.c_str()) != 0) {
		cout << "muri\n";
		return false;
	}*/		
	
	return true;
}


// Main
// return -1 : error
//         0 : normal
int MainFunc() {
	std::ifstream ifs("PageList.csv");
	if (!ifs) {
		printf("csv open error!\n");
		return -1;
	}

    string line, folder;
	getline(ifs, line); // header
	
    while (getline(ifs, line)) {
		replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		string n, sub_dir, main_dir, address;
		iss >> n;
		int num;
		try {
			num = std::stoi(n);
		}
		catch (const std::invalid_argument& e) {
			return -1;
		}
		catch (const std::out_of_range& e) {
			return -1;
		}
		if (num == 0) iss >> main_dir >> address;
		else iss >> sub_dir >> address;

		// todo 1
		// c++17のfilesystemに書き換える

		// todo 2
		// フォルダ作成する(かを聞く)(変なところに作るとまずいから)

		// 0 is main dir
		if (num == 0) {
			folder = "../Pages/" + main_dir;
			MyMkdir(folder);
		}
		// Non-Zero is sub dir
		else {
			folder += "/" + sub_dir;
			if (MyMkdir(folder)) {
				// 
			}
		}

    }

/*
	Item item[50];
	char dummy[300];
	fscanf(fp, "%s", dummy);
	int i = 0;
	while (fscanf(fp, "%d,%s,%d", &item[i].level, item[i].page_name, &item[i].other) != EOF){
		printf("%d %s %d\n",item[i].level, item[i].page_name, item[i].other);
		i++;
	}
	*/

	return 0;
}


int main() {

	MainFunc();


	return 0;
}


