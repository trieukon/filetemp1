#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
#include <algorithm>
using namespace std;
using json = nlohmann::json;

struct newPkg
{
	char type;
	string idModel , name, idPksg;
	long long price;
	int q;
};
//ham o cac file cpp khac

bool checkHavingModel(json t, char type);
long checkSameOrderd(json t, string id,int n);
string toCurr(long long a);
string toUP(string inp);
void displayOrderd(json items, json t,int n);
json importJSON();
void exportJSON(json data);
string creIdOrder(json pkg);
string now();
void updateQuantity(json* t, char type, int vt, int q);
void printModelQ(json t, char type);
string getNameModel(string idModel, char type, json* t, long long* p, int* vt);
//ham chua viet
void outPkgs(json * pkg);

void displayModels() { cout << "heloo"; };
void findIdPkgs(json* pkg);

void delAccout() {	//Muc xoa acc
	system("cls");
	json data = importJSON();
	if (data["account"]["nUser"] < 1) {
		cout << "Khong ton tai tai khoan nhan vien nao!" << endl;
		system("pause");
		return;
	}
	cout << "XOA TAI KHOAN NHAN VIEN!" << endl;
	cout << "---- Vui long lua chon tai khoan -----" << endl;
	for (int i = 0; i < data["account"]["nUser"]; i++) {
		cout << i + 1 << ". " << data["account"]["staffs"][i]["name"] << endl;
	}
	cout << "---- Nhap ngoai mien gia tri de thoat -----" << endl;
	int n;
	cin >> n;
	if (n<1 || n >> data["account"]["nUser"]) {
		cout << "Ngoai mien gia tri! Da huy!" << endl;
		cin.ignore(99999, '\n');
		cin.clear();
		system("pause");
	}
	else {
		n--;
		system("cls");
		cout << "XOA TAI KHOAN NHAN VIEN!" << endl;
		cout << "---- Xac nhan xoa? -----" << endl;
		cout << "Tai khoan da chon: " << (string)data["account"]["staffs"][n]["name"] << endl;
		cout << "Xac nhan xoa? \nNhan \'Y\' de doi, bat ki de huy!" << endl;
		char a;
		cin >> a;
		if (a == 'y' || a == 'Y') {
			data["account"]["staffs"].erase(n);
			data["account"]["nUser"] = data["account"]["nUser"] - 1;
			exportJSON(data);
			cout << "Da xoa thanh cong!" << endl;
			system("pause");
		}
		else {
			cout << "Da huy!" << endl;
			system("pause");
		}
		
	}
}

void pwAccout() {	//Doi mat khau
	system("cls");
	json data = importJSON();
	if (data["account"]["nUser"] < 1) {
		cout << "Khong ton tai tai khoan nhan vien nao!" << endl;
		system("pause");
		return;
	}
	cout << "THAY DOI MAT KHAU NHAN VIEN!" << endl;
	cout << "---- Vui long lua chon tai khoan -----" << endl;
	for (int i = 0; i < data["account"]["nUser"]; i++) {
		cout << i + 1 << ". " << data["account"]["staffs"][i]["name"] << " - " << data["account"]["staffs"][i]["pass"] << endl;
	}
	cout << "---- Nhap ngoai mien gia tri de thoat -----" << endl;
	int n;
	cin >> n;
	if (n<1 || n >> data["account"]["nUser"]) {
		cout << "Ngoai mien gia tri! Da huy!"<<endl;
		cin.ignore(99999, '\n');
		cin.clear();
		system("pause");
	}
	else {
		n--;
		system("cls");
		cout << "THAY DOI MAT KHAU NHAN VIEN!" << endl;
		cout << "---- Doi mat khau -----" << endl;
		cout << "Tai khoan da chon: " << (string)data["account"]["staffs"][n]["name"] << endl;
		cout << "Mat khau cu: " << (string)data["account"]["staffs"][n]["pass"] << endl;
		cout << "Mat khau moi: ";
		string s;
		cin >> s;
		cout << "Xac nhan doi? \nNhan \'Y\' de doi, bat ki de huy!" << endl;
		char a;
		cin >> a;
		if (a == 'y' || a == 'Y') {
			data["account"]["staffs"][n]["pass"]=s;
			exportJSON(data);
			cout << "Da doi thanh cong!" << endl;
			system("pause");
		}
		else {
			cout << "Da huy!" << endl;
			system("pause");
		}
	}
}

void creAccout() {	//Tao acc
	system("cls");
	json data = importJSON();
	string uName, pw;
	bool k;
	do {
		k = 0;
		cout << "TAO TAI KHOAN NHAN VIEN!" << endl;
		cout << "----------------" << endl;
		cout << "\tUsername: ";
		cin >> uName;
		cout << "\tPassword: ";
		cin >> pw;
		//nhap username va password
		for (int i = 0; i < data["account"]["nUser"]; i++) {
			if (uName == (string)data["account"]["staffs"][i]["name"] || uName =="admin") {
				system("cls");
				cout << "Tai khoan da ton tai!" << endl;
				k = 1;
				break;
			}
		}
	} while (k);
	system("cls");
	cout << "XAC THUC TAI KHOAN" << endl;
	cout << "----------------" << endl;
	cout << "\tUsername: " << uName << endl;
	cout << "\tPassword: " << pw << endl;
	cout << "Nhan \'Y\' de tao, bat ki de huy: ";
	char a;
	cin >> a;
	// Xac nhan tao hay khong?
	if (a == 'y' || a == 'Y') {
		data["account"]["staffs"].push_back({ {"name",uName},{"pass",pw}});
		data["account"]["nUser"] = data["account"]["nUser"] + 1;
		exportJSON(data);
		cout << "Da luu thanh cong!" << endl;
		system("pause");
	}
	else {
		cout << "Da huy!" << endl;
		system("pause");
	}
}

void editAccout() {	//Muc sua  tai khoan (xoa, doi pass, tao moi)
	
	char a;
	do {
		system("cls");
		cout << "QUAN LY TAI KHOAN NHAN VIEN!" << endl;
		cout << "----------------" << endl;
		cout << "1. Tao moi," << endl;
		cout << "2. Doi mat khau," << endl;
		cout << "3. Xoa," << endl;
		cout << "4. Tro lai." << endl;
		cout << "/>";
		//=========================
		cin >> a;
		switch (a)
		{
		case '1': {
			creAccout();
			break;
		}
		case '2': {
			pwAccout();
			break;
		}
		case '3': {
			delAccout();
			break;
		}
		default:
			break;
		}

	} while (a != '4');
}
//====================== QUAN LY DON HANG =================================



string creIdModel(json a) {	//tao id cho Model thiet bi
	int n;
	bool k = 1;
	string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890", s = ""; //36 KY TU
	do {
		k = 1;
		for (int i = 0; i < 6; i++) {
			if (i < 5) {
				s += abc[rand() % 36];
			}else s +=  abc[26 + rand() % 10];
		}
		n = a["model"]["L"]["n"];
		if (n>0) {
			for (int i = 0; i < a["model"]["L"]["n"]; i++) {
				if ((string)a["model"]["L"]["goods"][i]["id"] == s) k=0;
			}
		}
		n = a["model"]["P"]["n"];
		if (n > 0) {
			for (int i = 0; i < a["model"]["P"]["n"]; i++) {
				if ((string)a["model"]["P"]["goods"][i]["id"] == s) k = 0;
			}
		}

		
	} while (k != true);
	return s;
}

bool checkSameModel(json* t, char type,string name) {	//kiem tra xem co trung model da nhap trong don do khong
	json temp=*t;											//phuc vu viec cong don hang
	if (type == 'L' && temp["model"]["L"]["n"] > 0) {
		for (int i = 0; i < temp["model"]["L"]["n"]; i++) {
			if ((string)temp["model"]["L"]["goods"][i]["name"] == name) return 0;
		}
	}
	else if (type == 'P' && temp["model"]["P"]["n"] > 0) {
		for (int i = 0; i < temp["model"]["P"]["n"]; i++) {
			if ((string)temp["model"]["P"]["goods"][i]["name"] == name) return 0;
		}
	}return 1;
}




void newModels(json* pkg) {
	json t = *pkg;
	newPkg f;
reType:
	string display = "NHAP MAU MAY MOI:\n" + string(30, '-') + "\n"; //Luu display lai
step1:
	//Buoc 1: nhap loai may
	system("cls");
	cout << display;
	cout << "Moi nhap : \n('L':Laptop || 'P': Dien thoai)" << endl << "/>";
	cin >> f.type;
	while (f.type != 'l' && f.type != 'L' && f.type != 'P' && f.type != 'p') goto step1;//Kiem tra nhap

	if (f.type == 'l' || f.type == 'L') {
		f.type = 'L';
		display += "Loai may: L - Laptop\n";
	}
	else {
		f.type = 'P';
		display += "Loai may: P - Dien thoai\n";
	};
	cin.ignore();
step2://Nhap ten mau may
	system("cls");
	cout << display;
	printModelQ(t, f.type);
	cout << "Nhap ten mau may: ";	
	getline(cin, f.name);	
	f.name=toUP(f.name);
	cin.clear();
	if (checkSameModel(&t, f.type, f.name) == 0) goto step2;
	//Buoc 3: Tao IdModel cho mau may vua nhap
	f.idModel = creIdModel(t);
	display += "IdModel: \'" + f.idModel + "\' : "+f.name+"\n";
	//Buoc 4: Nhap don gia
step4:
	system("cls");
	cout << display;
	cout << "Nhap don gia (don vi 'nghin vnd'): ";
	cin >> f.price;
	if (f.price < 1) {
		cin.ignore(999, '\n'); cin.clear();
		goto step4;
	};
	display += "Don gia: " + toCurr(f.price) + " vnd / chiec,\n" + string(20,'-') +"\n";
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
		if (f.type == 'L') {
			t["model"]["L"]["n"] = t["model"]["L"]["n"] + 1;
			t["model"]["L"]["goods"].push_back({ { "name",f.name }, { "id",f.idModel }, { "price",f.price },{"quantity",0} });
			*pkg=t;
		}
		else {			
			t["model"]["P"]["n"] = t["model"]["P"]["n"] + 1;
			t["model"]["P"]["goods"].push_back({ {"name",f.name}, {"id",f.idModel}, {"price",f.price},{"quantity",0} });
			*pkg = t;
		}
		exportJSON(t);
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

void existModelPkg(json* t, json* items, int* n) {	//NHAP HANG VOI CAC DON CO SAN
	json temp = *items;
	newPkg f;
	int vt=0;
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
	f.idModel=toUP(f.idModel);
	f.name = getNameModel(f.idModel, f.type, t,&f.price,&vt);
	if ( f.name=="") {
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
		cout << "Hien don nay da nhap: " << nHave << " (chiec),"<<endl;
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
		
		int kk = checkSameOrderd(temp, f.idModel,*n);
		if ( kk>= 0) {
			temp[kk]["quantity"] = temp[kk]["quantity"]+f.q;
		}else{			
			temp.push_back({
				{"idModel",f.idModel},{"quantity",f.q} });
			*n = *n + 1;
		}
		updateQuantity(t,f.type, vt, f.q);
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
//model plantom > good{id, name} & n
void newModelPkg(json* t,json *items,int *n) { //NHAP DON HANG CO MAU MODEL MOI
	
	newPkg f;
reType:
	string display= "DON HANG CO MAU MOI:\n" + string(30, '-') + "\n"; //Luu display lai
step1:
	//Buoc 1: nhap loai may can nhap
	system("cls");
	cout << display;
	cout << "Moi nhap loai may: \n('L':Laptop || 'P': Dien thoai)"<<endl<<"/>";
	cin >> f.type;
	while (f.type!='l' && f.type != 'L'&&f.type != 'P'&&f.type != 'p') goto step1;//Kiem tra nhap
	if (f.type == 'l' || f.type == 'L') {
		f.type = 'L';
		display += "Loai may: L - Laptop\n";
	}
	else {
		display += "Loai may: P - Dien thoai\n";
		f.type = 'P';
	};
	//Buoc 2: Nhap ten mau may
	cin.ignore();
step2:
	system("cls");
	cout << display;
	cout << "Nhap ten mau may: ";	
	getline(cin, f.name);	
	f.name=toUP(f.name);
	cin.clear();
	if (checkSameModel(t, f.type, f.name) == 0) goto step2;
	//Buoc 3: Tao IdModel cho mau may vua nhap
	f.idModel = creIdModel(*t);
	display += "IdModel: \'" + f.idModel + "\' : "+f.name+"\n";
	//Buoc 4: Nhap don gia
step4:
	system("cls");
	cout << display;
	cout << "Nhap don gia (don vi 'nghin vnd'): ";
	cin >> f.price;
	if (f.price < 1) {
		cin.ignore(999, '\n'); cin.clear();
		goto step4;
	};
	display += "Don gia: " + toCurr(f.price) + " vnd / chiec,\n" + string(20,'-') +"\n";
	//Buoc 5: Nhap so luong
step5:
	system("cls");
	cout << display;
	cout << "So luong nhap vao:";
	cin >> f.q;
	if (f.q < 1) {
		cin.ignore(999, '\n'); cin.clear();
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
		json temp=*items;
		temp.push_back({
			{"idModel",f.idModel},{"quantity",f.q}});
		*items = temp;
		*n = *n + 1;
		if (f.type == 'L') {
			json tt=*t;
			tt["model"]["L"]["n"] = tt["model"]["L"]["n"] + 1;
			tt["model"]["L"]["goods"].push_back({ { "name",f.name }, { "id",f.idModel }, { "price",f.price },{"quantity",f.q}});
			*t = tt;
		}else {
			json tt = *t;
			tt["model"]["P"]["n"] = tt["model"]["P"]["n"] + 1;
			tt["model"]["P"]["goods"].push_back({{"name",f.name}, {"id",f.idModel}, {"price",f.price},{"quantity",f.q} });
			*t = tt;
		}
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
};

void newPkgs(json* pkg) { //NHAP HANG VOI CAC TUY CHON
	char a;
	json t=*pkg;
	json items={};
	string id = creIdOrder(*pkg);
	t["packages"]["nImp"] = t["packages"]["nImp"] + 1;
	
	int n = 0;
renew:
	system("cls");
	cout << "NHAP DON HANG MOI:\nMa don hang: " << id << endl<< string(30, '-') << endl;
	cout << "LUA CHON NHAP DON HANG:" << endl;
	cout << "1/ Nhap mau Mau moi" << endl;
	cout << "2/ Mau da co," << endl;
	if (n>0) {
		cout << "3/ Luu don hang va tro lai," << endl;
	}
	cout << "0/ Huy bo va tro lai."<<endl;
	//==============================
	displayOrderd(items,t,n);
	//==============================
	cout << "/>";
	cin >> a;
	switch (a)
	{
	case'1': {
		newModelPkg(&t,&items,&n);
		goto renew;
		break;
	}
	case'2': {
		existModelPkg(&t, &items, &n);
		goto renew;
		break;
	}
	case'3': {
		if (n>0){
			t["packages"]["pkgs"].push_back({ {"n",n},{"id",id},{"items",items},{"time",now()},{"t","imp"}});
			*pkg = t;
			exportJSON(*pkg);
			cout << "Luu thanh cong!" << endl;
			system("pause");
		}
		break;
	}
	default:
		break;
	}


};

void editPackage0() {
	json pkg = importJSON();
	char a;
	do {
		system("cls");
		cout << "QUAN LY DON HANG TRONG KHO!" << endl;
		cout << "---------------------------" << endl;
		cout << "1. Nhap danh sach MAU MAY duoc phep nhap," << endl;
		cout << "2. Nhap DON HANG NHAP MAY moi," << endl;
		cout << "3. Xuat DON HANG NHAP MAY moi," << endl;
		cout << "4. Xem DON HANG NHAP / XUAT," << endl;
		cout << "5. Xem tat ca MAU MODEL dang co trong kho," << endl;
		cout << "0. Tro lai." << endl;
		cout << "/>";
		cin >> a;
		switch (a)
		{
		case '1': {
			newModels(&pkg);
			break;
		}
		case '2': {
			newPkgs(&pkg);
			break;
		}
		case '3': {
			outPkgs(&pkg); 
			break;
		}
		case '4': {
			findIdPkgs(&pkg);
			break;
		}
		case '5': {
			displayModels();
			break;
		}
		
		default:
			break;
		}
	} while (a!='5');
}

void displayAdmin() {
	system("cls");
	cout << "CHAO MUNG ADMIN!" << endl;
	cout << "----------------" << endl;
	cout << "1. Quan ly tai khoan nhan vien," << endl;
	cout << "2. Quan ly kho hang," << endl;
	cout << "3. Xuat log nhap/xuat," << endl;
	cout << "4. Thoat." << endl;
	cout << "/>";
}

void gotoAdmin() {

	char a;
	do {
		displayAdmin();
		cin >> a;
		switch (a)
		{
		case '1': {
			editAccout();
			break;
		}
		case '2': {
			editPackage0();
			break;
		}
		default:
			break;
		}

	} while (a != '4');

}