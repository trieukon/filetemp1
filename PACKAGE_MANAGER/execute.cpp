#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
using namespace std;
using json = nlohmann::json;

bool checkFile(string path) {
	ifstream f(path);
	bool a = f.good();
	f.close();
	return a;
}
json importAcc() {
	if (!checkFile("account.json")) {
		json a = {
			{"admin",{
				{"name","admin"},
				{"pass","1234"}
			}
			},{"nUser",2},
			{"staffs", {{{"id",1},{"name","konnn"},{"pass","1234"}},{{"id",2},{"name","qui"},{"pass","1234"}} }} };
		ofstream f("account.json");
		f << a;
		f.close();
		cout << "Created!\n";
	}

	fstream a("account.json");
	json acc;
	a >> acc;	
	a.close();
	return acc;
}
void uiAdmin() {
	system("cls");
	cout << "CHAO MUNG ADMIN!" << endl;
	cout << "----------------" << endl;
	cout << "1. Quan ly tai khoan nhan vien" << endl;
}
void uiStaff(string name) {
	system("cls");
	cout << "CHAO MUNG "<<name<<" " << endl;

}
void login() {
	json acc = importAcc();
	string urn, pw;
	cout << "======= Shoppi!!! =======" << endl;
	cout << "Moi ban dang nhap: " << endl;
	cout << "Ten dang nhap:\t";
	cin >> urn;
	cout << "Mat khau:\t";
	cin >> pw;
	
	

	if (urn == string(acc["admin"]["name"]) && pw == (string)acc["admin"]["pass"]) {
		cout << "Admin";
	}
	else if (acc["nUser"] > 0) {
		int i;
		for (i = 0; i < acc["nUser"]; i++) {
			if (urn == (string)acc["staffs"][i]["name"] && pw == (string)acc["staffs"][i]["pass"]) {
				uiStaff((string)acc["staffs"][i]["name"]);
				break;
			}
		}
		if ( i == acc["nUser"])
		cout << "Khong tim thay tai khoan nao!" << endl;
	}
}
