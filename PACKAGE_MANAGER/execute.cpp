#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
#include <ctime>

using namespace std;
using json = nlohmann::json;

struct newPkg
{
	char type;
	string code,name,id;
	long long price;
	int q;
} ;



string now() {
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

void gotoAdmin();
void gotoStaff(string name);

void exportJSON(json data) {
	ofstream a("data.json");
	a << data;
	a.close();
}

bool checkFile(string path) {
	ifstream f(path);
	bool a = f.good();
	f.close();
	return a;
}
void creFileJSON() {
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
				{"PC",{
					{"n",0},{"goods",{}}
			}},
				{"PHONE",{
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

json importJSON() {
	fstream a("data.json");
	json data;
	a >> data;	
	a.close();
	return data;
}



string login() {
	
	json data = importJSON();
	string urn, pw;
	cout << "======= Shoppi!!! =======" << endl;
	cout << "Moi ban dang nhap: " << endl;
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
string creIdOrder(json a) {
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
				if (s == a["packages"]["pkgs"]["id"][n]) {
				n = a["packages"]["nAll"];
				k = 0;
				break;
			}	//tao id 8 ky tu
		} while (--n);}		
	} while (k!=true);
	return s;	
}
void gotoPermision(string x) {
	if (x == "") {
		gotoAdmin();
	}
	else {
		gotoStaff(x);
	}
}
//==============================================================
void newPkgs(json* pkg) {
	string id = creIdOrder(*pkg);
	json inp = *pkg;
	json outp = { {"id",id},{"items",{}} };
	newPkg f;
	

	int n = 0;
newStep:
	n++;
	string s = "NHAP DON HANG MOI!\n---------------------------\n";//47
	s += "Ma dinh danh don hang: " + id + "\n";
step1:
	system("cls");	
	cout << s ;		
	cout << "Loai may ('L': May tinh, 'P': Dien thoai) :";
	cin >> f.type;
	if (f.type != 'l' && f.type != 'L' && f.type != 'P' && f.type != 'p')
	{
		goto step1;
		
	}
	else {
		if (f.type == 'l' || f.type == 'L') {
			s += "Loai may: L - Laptop,\n";
		}else s += "Loai may: P - Dien thoai,\n";
		
	}
	s += "Ten may: ";
	system("cls");
	cout << s;
	cin.ignore(99999, '\n');cin.clear();
	getline(cin, f.name);
	s += f.name +",\n";
	system("cls");
	cout << s<<"Ma dong may (viet lien khong dau): ";
	getline(cin, f.code);
	s += "Ma dong may: " + f.code + ",\n";
	system("cls");
step2:
	cout << s << "Nhap so luong nhap vao: ";
	cin >> f.q;
	
	if (f.q < 1) {
		system("cls");
		cout << "So luong khong hop le!"<<endl;
		cin.clear();
		cin.ignore(99999, '\n'); 
		goto step2;
	}
	else {
		s += "So luong: " + to_string(f.q) + " (chiec),\n";
	}
	system("cls");
step3:
	cout << s<<"Nhap don gia (nghin vnd):";
	cin >> f.price;
	if (f.price < 1) {
		system("cls");
		cout << "Menh gia khong hop le!" << endl;
		cin.clear();
		cin.ignore(99999, '\n');
		goto step3;
	}
	else {
		s += "Don gia: " + to_string(f.price) + "000d /chiec. \n";
	}
	s.erase(s.begin(), s.begin() + 47);
	system("cls");
	
confirm:
	cout << "XAC NHAN DON HANG!\n---------------------------\n";
	cout << s<<endl;
	cout << "1. Tiep tuc hang moi| 2. Ket thuc nhap | 3. Huy nhap"<<endl;
	char a;
	cin >> a;
	if (a == '1' || a == '2') {
		outp["items"].push_back(
			{	{"type",f.type},
				{"name",f.name},
				{"idModel",f.code},
				{"quantity",f.q},
				{"price",f.price}
			}
		);
		outp.push_back({ "n",n });
		if (a == '1') {
			goto newStep;
		}else{
			outp.push_back({ "time",now() });
			inp["packages"]["nAll"] = inp["packages"]["nAll"] + 1;
			inp["packages"]["nHaving"] = inp["packages"]["nHaving"] + 1;
			inp["packages"]["pkgs"].push_back(outp);
			*pkg = inp;
			exportJSON(*pkg);
			cout << "Da luu thanh cong!" << endl;
		}
	}
	else if (a == '3') {
		cout << "Da huy nhap!" << endl;
	}
	else {
		goto confirm;
	}
	system("pause");
};
