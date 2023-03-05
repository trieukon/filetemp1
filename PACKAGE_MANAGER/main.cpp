#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
#include <ctime>
//#include"execute.hpp"
using namespace std;
using json = nlohmann::json;
bool checkFile(string path);
string login();
void creFileJSON();
void gotoPermision(string x);
int main() {	
	srand(time(NULL));
	creFileJSON();
	gotoPermision(login());
	system("pause");
	return 0;
}