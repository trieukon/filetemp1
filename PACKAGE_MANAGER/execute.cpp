#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
using json = nlohmann::json;

//struct newPkg
//{
//	char type;
//	string code,name,id;
//	long long price;
//	int q;
//} ;
string toCurr(long long a) {	//ham tra ve string in tien, vd a=1200 (long long) thi return = 1.200.000 (string)
	string s = to_string(a);
	int n = s.length() - 1, d = 2;
	while (d < n && n >= 3) {
		n = s.length() - 1;
		s.insert((n - d), ".");
		d += 4;
	}
	return s + ".000";
}


string now() {	//Lay thoi gian may tra ve string
	time_t now = time(nullptr);
	char buffer[20];
	tm local_time;
#ifdef _WIN32
	localtime_s(&local_time, &now);
#else
	localtime_r(&now, &local_time);
#endif
	strftime(buffer, 20, "%Y-%m-%d %H:%M:%S", &local_time);
	return string(buffer);
}

void gotoAdmin();	//o file adminExe.cpp
void gotoStaff(string name);//o file staffExe.cpp


void exportJSON(json data) {	//nhap JSON de xuat ra data.json
	ofstream a("data.json");
	a << data;
	a.close();
}

bool checkFile(string path) {	//kiem tra su ton tai cua file data.json
	ifstream f(path);
	bool a = f.good();
	f.close();
	return a;
}
void creFileJSON() {	// khoi tao ban dau file data.json
	if (!checkFile("data.json")) {
		json a = {
			{"account",{
				{"admin",{
					{"name","admin"},
					{"pass","1234"}
						}
				},
				{"nUser",2},
				{"staffs", {
				{
					{"name","konnn"},
					{"pass","1234"}
				},
				{
					{"name","qui"},
					{"pass","1234"}
				} 
				}
				}
				}
			},
			{"model",{
				{"L",{
					{"n",0},{"goods",{}}
			}},
				{"P",{
					{"n",0},{"goods",{}}
			}}
		}},
			{"packages",{
			{"nAll",0},{"nHaving",0},{"pkgs",{}
			}}},
			{"logs",{}}
		};
		ofstream f("data.json");
		f << a;
		f.close();
		cout << "Created!\n";
	}
}

json importJSON() {	//tra ve json tu du lieu data.json
	fstream a("data.json");
	json data;
	a >> data;	
	a.close();
	return data;
}



string login() {	//dang nhap
	
	json data = importJSON();
	string urn, pw;
	cout << "======= Shoppi!!! =======" << endl;
	cout << "Moi ban dang nhap! " << endl;
	cout << "Ten dang nhap:\t";
	cin >> urn;
	cout << "Mat khau:\t";
	cin >> pw;

	if (urn == string(data["account"]["admin"]["name"]) && pw == (string)data["account"]["admin"]["pass"]) {
		return "";
	}
	else if (data["account"]["nUser"] > 0) {
		int i;
		for (i = 0; i < data["account"]["nUser"]; i++) {
			if (urn == (string)data["account"]["staffs"][i]["name"] && pw == (string)data["account"]["staffs"][i]["pass"]) {
				return (string)data["account"]["staffs"][i]["name"];
				break;
			}
		}
		if ( i == data["account"]["nUser"])
		cout << "Khong tim thay tai khoan nao!" << endl;
	}

}
string creIdOrder(json a) {	// tao id don hang (co kiem tra long nhau)
	int n;
	bool k=1;
	string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", s = ""; //36 KY TU
	do {
		k = 1;
		for (int i = 0; i < 8; i++) {
			s += abc[rand() % 36];
		}
		n = a["packages"]["nAll"]; 
		if (n > 0) {
			do {
				if (s == a["packages"]["pkgs"][n-1]["id"]) {
				n = a["packages"]["nAll"];
				k = 0;
				break;
			}	//tao id 8 ky tu
		} while (--n);}		
	} while (k!=true);
	return s;	
}
void gotoPermision(string x) {//re nhanh quyen tu login()
	if (x == "") {
		gotoAdmin();
	}
	else {
		gotoStaff(x);
	}
}
//==============================================================
void updateQuantity(json* t,char type, int vt, int q) {
	json tt = *t;
	if (type == 'L') {
		tt["model"]["L"]["goods"][vt]["quantity"] = tt["model"]["L"]["goods"][vt]["quantity"] + q;
	}else tt["model"]["P"]["goods"][vt]["quantity"] = tt["model"]["P"]["goods"][vt]["quantity"] + q;
	*t = tt;
}
//
void findIdPkgs(json*pkg) {	//muc 2 cua quan ly don hang
	/*json inp = *pkg; inp = inp["packages"];
	
	if (inp["nAll"] < 1) {
		cout << "Khong co don hang nao trong csdl!" << endl;
		system("pause");
	}
	else {
		cout << "NHAP MA DINH DANH CUA DON HANG DE TRUY XUAT" << endl;
		cout << string(20,'-') << endl << "/>";
		string inS;
		cin >> inS;
		int n = inp["nAll"];
		while(n--) {
			cout << n << endl;
			if (inp["pkgs"][n]["id"] == inS) {
				cout << inp["pkgs"][n]["name"];
				system("pause");
				break;				
			}
		}
		cout << "NO";
		system("pause");
	}*/
	
}

long checkSameOrderd(json t, string id,int n) { //tra ve vi tri ma idModel dung trong mang json neu no ton tai truoc do, k co tra ve -1
	if (n>0) for (int i = 0; i < n; i++) {
		if ((string)t[i]["idModel"] == id) return i;
	}
	return -1;
}

void displayOrderd(json items,json t, int n) { //lenh in man hinh don hang da nhap 
	if (n > 0) 
	{
		int* p=new int[n];
		long long sum = 0;
		cout << string(30, '-') << endl<<"DON HANG BAO GOM: "<<endl;
		for (int i = 0; i < n; i++) {
			cout << i+1<<". " << items[i]["idModel"] << " - ";
			
			if (t["model"]["L"]["n"]>0) for (int j = 0; j < t["model"]["L"]["n"]; j++) {
				if (items[i]["idModel"] == t["model"]["L"]["goods"][j]["id"]) {
					cout << t["model"]["L"]["goods"][j]["name"] << " : ";
					p[i] = t["model"]["L"]["goods"][j]["price"];
				}
			}
			if (t["model"]["P"]["n"] > 0) for (int j = 0; j < t["model"]["P"]["n"]; j++) {
				if (items[i]["idModel"] == t["model"]["P"]["goods"][j]["id"]) {
					cout << t["model"]["P"]["goods"][j]["name"] << " : ";
					p[i] = t["model"]["P"]["goods"][j]["price"];
				}
			}

			cout << items[i]["quantity"] << "*" << toCurr(p[i]) << " = " << toCurr((int)items[i]["quantity"] * p[i]) << " vnd" << endl;
			sum += (int)items[i]["quantity"] * p[i];

		}
		cout << "Tong gia tri: " << toCurr(sum) << " vnd." << endl;
		cout << string(30, '-') << endl;
		delete[]p;
		p = nullptr;
	}
}
string toUP(string inp) { //tra ve string la UPCASE cua string vao
	transform(inp.begin(), inp.end(), inp.begin(), ::toupper);
	return inp;
}