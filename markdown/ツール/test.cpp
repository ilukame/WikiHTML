// g++ -Wall -o a test.cpp -static -std=c++17

/*******INCLUDE HEADER***********/
#include <iostream>
#include <filesystem> // C++17

int main() {
	std::filesystem::copy("test", "test2/", std::filesystem::copy_options::recursive);
	
	return 0;
}
