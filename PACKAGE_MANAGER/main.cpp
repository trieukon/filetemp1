#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
//#include"execute.hpp"
using namespace std;
using json = nlohmann::json;
bool checkFile(string path);
string login();
void creFileAcc();
void gotoPermision(string x);
int main() {	
	creFileAcc();
	gotoPermision(login());
	system("pause");
	return 0;
}