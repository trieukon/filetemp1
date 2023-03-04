#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
using namespace std;
using json = nlohmann::json;

void gotoAdmin();
void gotoStaff(string name);

void exportAcc(json acc) {
	ofstream a("account.json");
	a << acc;
	a.close();
}

bool checkFile(string path) {
	ifstream f(path);
	bool a = f.good();
	f.close();
	return a;
}
void creFileAcc() {
	if (!checkFile("account.json")) {
		json a = {
			{"admin",{
				{"name","admin"},
				{"pass","1234"}
			}
			},{"nUser",2},
			{"staffs", {{{"name","konnn"},{"pass","1234"}},{{"name","qui"},{"pass","1234"}} }} };
		ofstream f("account.json");
		f << a;
		f.close();
		cout << "Created!\n";
	}
}
json importAcc() {
	fstream a("account.json");
	json acc;
	a >> acc;	
	a.close();
	return acc;
}



string login() {
	json acc = importAcc();
	string urn, pw;
	cout << "======= Shoppi!!! =======" << endl;
	cout << "Moi ban dang nhap: " << endl;
	cout << "Ten dang nhap:\t";
	cin >> urn;
	cout << "Mat khau:\t";
	cin >> pw;

	if (urn == string(acc["admin"]["name"]) && pw == (string)acc["admin"]["pass"]) {
		return "";
	}
	else if (acc["nUser"] > 0) {
		int i;
		for (i = 0; i < acc["nUser"]; i++) {
			if (urn == (string)acc["staffs"][i]["name"] && pw == (string)acc["staffs"][i]["pass"]) {
				return (string)acc["staffs"][i]["name"];
				break;
			}
		}
		if ( i == acc["nUser"])
		cout << "Khong tim thay tai khoan nao!" << endl;
	}

}
void gotoPermision(string x) {
	if (x == "") {
		gotoAdmin();
	}
	else {
		gotoStaff(x);
	}
}
