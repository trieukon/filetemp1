#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
//#include"execute.hpp"
using namespace std;
using json = nlohmann::json;
bool checkFile(string path);
void login();
int main() {	
	login();
	system("pause");
	return 0;
}