#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
using namespace std;
using json = nlohmann::json;

json importJSON();
void exportJSON(json data);
void outAllPkgs() { cout << "heloo"; };
void outModels(){ cout << "heloo"; };
void findIdPkgs(){ cout << "heloo"; };
void newPkgs(json* pkg);

void delAccout() {
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

void pwAccout() {
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

void creAccout() {
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

void editAccout() {
	
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

void editPackage0() {
	json pkg = importJSON();
	char a;
	do {
		system("cls");
		cout << "QUAN LY DON HANG TRONG KHO!" << endl;
		cout << "---------------------------" << endl;
		cout << "1. Nhap DON HANG moi," << endl;
		cout << "2. Truy xuat DON HANG nhanh," << endl;
		cout << "3. Xem tat ca DON HANG con lai trong kho," << endl;
		cout << "4. Xem tat ca MAU MODEL dang co," << endl;
		cout << "5. Tro lai." << endl;
		cout << "/>";
		cin >> a;
		switch (a)
		{
		case '1': {
			newPkgs(&pkg);
			break;
		}
		case '2': {
			findIdPkgs();
			break;
		}
		case '3': {
			outAllPkgs();
			break;
		}
		case '4': {
			outModels();
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