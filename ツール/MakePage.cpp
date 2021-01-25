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
// サブフォルダも検索しながらfileExの拡張子が付いたファイルを削除する
bool DelFiles(const string &path, const vector<string> &fileEx) {
	WIN32_FIND_DATA dirFile;
	string searchPath = path + "\\*"; // all file and dir search
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &dirFile);

	// file and dir not find
	if (hFind == INVALID_HANDLE_VALUE) {
		return false;
	}
	do {
		string fileName = dirFile.cFileName;
		// skip
		if (fileName == "." || fileName == "..") {
			continue;
		}

		string fullFileName = path + "\\" + fileName;
		// dir
		if (dirFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (DelFiles(fullFileName, fileEx) == false) {
				return false;
			}
		}
		// file
		else {
			for (int i = 0; i < fileEx.size(); i++) {
				// 右から検索
				int pos = fullFileName.rfind(fileEx[i]);
				// 右端ではなかったら削除しない
				if (pos != string::npos && fileEx[i].size() + pos == fullFileName.size()) {
					// 削除
					if (remove(fullFileName.c_str()) != 0) {
						printf("error\n");
						return false;
					}
					break;
				}
			}
		}
		// search next file
	} while (FindNextFile(hFind, &dirFile));
	// close
	FindClose(hFind);
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

    string line;
	getline(ifs, line); // header
	
    while (getline(ifs, line)) {
		replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		string s[3];
		iss >> s[0] >> s[1] >> s[2];

		// todo1
		// stoiで変換https://cpprefjp.github.io/reference/string/stoi.html
		
		try {
			int num = std::stoi(s[0]);
			
		}
		catch (const std::invalid_argument& e) {
			return -1;
		}
		catch (const std::out_of_range& e) {
			return -1;
		}
		

		// todo2
		// フォルダ作成するかを@聞く

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


