// g++ -O3 -Wall -o a MakePage.cpp -static -std=c++17
// なんかMinGW5.3.0だとgetlineで死んで2h無駄にした
// gcc 8.1.0だとfilesystemをincludeできません＾＾

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
#include <filesystem> // C++17

/******* GLOBAL VARIABLES ***********/
namespace gloval_values {
	const char* PAGE_LIST = "PageList.csv";
	const char* TEMPLATE_FOLDER_PATH = "../Pages/Template";
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

bool MyMkdir(const string &folder_path) {
	bool result = std::filesystem::create_directory(folder_path.c_str());
	if (!result) {
		return false;
	}
	return true;
}

// コピーしてリネームする
void MyDirCopy(const string &to_folder_path, const string &folder_name) {
	cout << std::filesystem::exists(TEMPLATE_FOLDER_PATH) << endl;
	cout << std::filesystem::exists(to_folder_path) << endl;
	cout << TEMPLATE_FOLDER_PATH << endl;
	cout << to_folder_path << endl;
	std::filesystem::copy(TEMPLATE_FOLDER_PATH, to_folder_path, std::filesystem::copy_options::recursive);
	string s = to_folder_path + "/Template";
	string s2 = to_folder_path + folder_name;
	std::filesystem::rename(s.c_str(), s2.c_str());
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

    string line, folder_path;
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

		
		// 0 is main dir
		if (num == 0) {
			folder_path = "../Pages/" + main_dir;
			bool isExists = std::filesystem::exists(folder_path.c_str());
			if(!isExists) {
				cout << main_dir << " フォルダを作成しますか?\n";
				// todo 1
				// フォルダ作成する(かを聞く)(変なところに作るとまずいから)


				MyMkdir(folder_path);
			}
		}
		// Non-Zero is sub dir
		
		else {
			string sub_folder_path = folder_path + "/" + sub_dir;
			bool isExists = std::filesystem::exists(sub_folder_path.c_str());
			cout << sub_folder_path << endl;
			if(!isExists) {
				cout << main_dir << " フォルダを作成しますか?\n";
				// todo 2
				// フォルダ作成する(かを聞く)(変なところに作るとまずいから)

				// コピーしてリネームする
				MyDirCopy(folder_path, sub_dir);
			}
		}
    }
	return 0;
}


int main() {

	MainFunc();


	return 0;
}
