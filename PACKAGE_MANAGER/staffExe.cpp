#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
using namespace std;
using json = nlohmann::json;

struct newPkg
{
	char type;
	string idModel, name, idPksg;
	long long price;
	int q;
};

bool checkHavingModel(json t, char type);
long checkSameOrderd(json t, string id, int n);
string toCurr(long long a);
string toUP(string inp);
void displayOrderd(json items, json t, int n);
json importJSON();
void exportJSON(json data);
string creIdOrder(json pkg);
string now();
void updateQuantity(json* t, char type, int vt, int q);
void printModelQ(json t, char type);
string getNameModel(string idModel, json* t, long long* p, int* vt);
//ham chua viet
void outPkgs(json* pkg, string s);
void displayModels();
void findIdPkgs(json* pkg);


void existModelPkg1(json* t, json* items, int* n) {	//NHAP HANG VOI CAC DON CO SAN
	json temp = *items;
	newPkg f;
	int vt = 0;
reType:
	string display = "DON HANG CO MAU DA CO:\n" + string(30, '-') + "\n"; //Luu display lai
step1:
	//Buoc 1: nhap loai may
	system("cls");
	cout << display;
	cout << "Moi nhap : \n('L':Laptop || 'P': Dien thoai)" << endl << "/>";
	cin >> f.type;
	while (f.type != 'l' && f.type != 'L' && f.type != 'P' && f.type != 'p') goto step1;//Kiem tra nhap

	if (f.type == 'l' || f.type == 'L') {
		f.type = 'L';
		if (!checkHavingModel(*t, f.type)) {
			cout << "Chua co mau may LAPTOP nao co san!" << endl;
			system("pause");
			return;
		}
		else {

			display += "Loai may: L - Laptop\n";
		}
	}
	else {
		f.type = 'P';
		if (!checkHavingModel(*t, f.type)) {
			cout << "Chua co mau may DIEN THOAI nao co san!" << endl;
			system("pause");
			return;
		}
		else {
			display += "Loai may: P - Dien thoai\n";

		}

	};

	//Buoc 2: Nhap id mau may
	system("cls");
	cin.ignore();
step2:
	cout << display;
	printModelQ(*t, f.type);
	cout << "Nhap ma IdModel: ";
	getline(cin, f.idModel);
	cin.clear();
	f.idModel = toUP(f.idModel);
	f.name = getNameModel(f.idModel, t, &f.price, &vt);
	if (f.name == "") {
		system("cls");
		cout << "Khong ton tai IdModel nay!" << endl;
		goto step2;
	}

	//Buoc 3: Gan IdModel cho mau may vua nhap
	display += "IdModel: \'" + f.idModel + "\' : " + f.name + "\n";
	//Buoc 4: Gan don gia
	display += "Don gia: " + toCurr(f.price) + " vnd / chiec,\n" + string(20, '-') + "\n";
	//Buoc 5: Nhap so luong
step5:
	int nHave = 0;
	system("cls");
	cout << display;
	int kk = checkSameOrderd(temp, f.idModel, *n);
	if (kk >= 0) {
		nHave = temp[kk]["quantity"];
		cout << "Hien don nay da nhap: " << nHave << " (chiec)," << endl;
	}
	cout << "So luong nhap vao:";
	cin >> f.q;


	if ((nHave + f.q) < 1) {
		cin.clear(); cin.ignore(999, '\n');
		goto step5;
	};
	display += "So luong: " + to_string(f.q) + " (chiec).\n";
	//Buoc 6: Xac nhan
step6:
	system("cls");
	cout << "XAC NHAN LAI: \n" << string(20, '-') << endl;
	cout << display;
	cout << "1. Hoan tat nhap | 2. Nhap lai | 3. Huy va tro lai\n/>";
	char a;
	cin >> a;
	switch (a)
	{
	case '1': {

		int kk = checkSameOrderd(temp, f.idModel, *n);
		if (kk >= 0) {
			temp[kk]["quantity"] = temp[kk]["quantity"] + f.q;
		}
		else {
			temp.push_back({
				{"idModel",f.idModel},{"quantity",f.q} });
			*n = *n + 1;
		}
		updateQuantity(t, f.type, vt, f.q);
		*items = temp;
		break;
	}
	case '2': {
		goto reType;
		break;
	}
	case '3': {
		break;
	}
	default:
		goto step6;
		break;
	}
	system("pause");
}

void newPkgsStaff(json* pkg, string ss) { //NHAP HANG VOI CAC TUY CHON
	char a;
	json t = *pkg;
	json items = {};
	string id = creIdOrder(*pkg), from;
	t["packages"]["nImp"] = t["packages"]["nImp"] + 1;
	cout << "NHAP DON HANG MOI: " << endl << string(30, '-') << endl;
	cout << "Nhap ten doanh nghiep cung cap: ";
	cin.ignore();
	getline(cin, from);
	int n = 0;
renew:
	system("cls");
	cout << "NHAP DON HANG MOI:" << endl;
	cout << "Ten doanh nghiep cung cap: " << from << endl;
	cout << "Ma don hang : " << id << endl << string(30, '-') << endl;
	cout << "LUA CHON NHAP DON HANG:" << endl;
	cout << "1/ Nhap mau may da co," << endl;
	if (n > 0) {
		cout << "2/ Luu don hang va tro lai," << endl;
	}
	cout << "0/ Huy bo va tro lai." << endl;
	//==============================
	displayOrderd(items, t, n);
	//==============================
	cout << "/>";
	cin >> a;
	switch (a)
	{
	case'1': {
		existModelPkg1(&t, &items, &n);
		goto renew;
		break;
	}
	case'2': {
		if (n > 0) {
			t["packages"]["pkgs"].push_back({ {"n",n},{"id",id},{"items",items},{"time",now()},{"t","imp"},{"name",ss},{"from",from} });
			*pkg = t;
			exportJSON(*pkg);
			cout << "Luu thanh cong!" << endl;
			system("pause");
		}
		else goto renew;
		break;
	}
	case '0': {
		cout << "Da huy!" << endl;
		system("pause");
		break;
	}
	default:
		goto renew;
		break;
	}
};

void displayStaff(string s) {
	system("cls");
	cout << "Chao mung ban, " << s << "!" << endl;
	cout << "----------------" << endl;
	cout << "1. Nhap DON HANG NHAP MAY moi," << endl;
	cout << "2. Xuat DON HANG NHAP MAY moi," << endl;
	cout << "3. Xem DON HANG NHAP / XUAT," << endl;
	cout << "4. Xem tat ca MAU MODEL dang co trong kho," << endl;
	cout << "5. Xuat nhat ky nhap/xuat," << endl;
	cout << "0. Thoat." << endl;
	cout << "/>";
}

void gotoStaff(string s) {
	json pkg = importJSON();
	//getname
	string ss;
	for (int i = 0; i < pkg["account"]["nUser"]; i++) {
		if ((string)pkg["account"]["staffs"][i]["uname"] == s) {
			ss = (string)pkg["account"]["staffs"][i]["name"];
			break;
		}
	}
	///===========
	char a;
	do {
		displayStaff(ss);
		cin >> a;
		switch (a)
		{
		case '1': {
			newPkgsStaff(&pkg, ss);
			break;
		}
		case '2': {
			outPkgs(&pkg, ss);
			break;
		}
		case '3': {
			findIdPkgs(&pkg);
			break;
		}
		case '4': {
			displayModels();
			break; 
		}
		case '5': {
			
			break;
		}
		default:
			break;
		}

	} while (a != '0');

}