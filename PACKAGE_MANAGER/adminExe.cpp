#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
using namespace std;
using json = nlohmann::json;

json importAcc();
void exportAcc(json acc);

void delAccout() {
	system("cls");
	json acc = importAcc();
	if (acc["nUser"] < 1) {
		cout << "Khong ton tai tai khoan nhan vien nao!" << endl;
		system("pause");
		return;
	}
	cout << "XOA TAI KHOAN NHAN VIEN!" << endl;
	cout << "---- Vui long lua chon tai khoan -----" << endl;
	for (int i = 0; i < acc["nUser"]; i++) {
		cout << i + 1 << ". " << acc["staffs"][i]["name"] << endl;
	}
	cout << "---- Nhap ngoai mien gia tri de thoat -----" << endl;
	int n;
	cin >> n;
	if (n<1 || n >> acc["nUser"]) {
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
		cout << "Tai khoan da chon: " << (string)acc["staffs"][n]["name"] << endl;
		cout << "Xac nhan xoa? \nNhan \'Y\' de doi, bat ki de huy!" << endl;
		char a;
		cin >> a;
		if (a == 'y' || a == 'Y') {
			acc["staffs"].erase(n);
			acc["nUser"] = acc["nUser"] - 1;
			exportAcc(acc);
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
	json acc = importAcc();
	if (acc["nUser"] < 1) {
		cout << "Khong ton tai tai khoan nhan vien nao!" << endl;
		system("pause");
		return;
	}
	cout << "THAY DOI MAT KHAU NHAN VIEN!" << endl;
	cout << "---- Vui long lua chon tai khoan -----" << endl;
	for (int i = 0; i < acc["nUser"]; i++) {
		cout << i + 1 << ". " <<  acc["staffs"][i]["name"] << " - " << acc["staffs"][i]["pass"] << endl;
	}
	cout << "---- Nhap ngoai mien gia tri de thoat -----" << endl;
	int n;
	cin >> n;
	if (n<1 || n >> acc["nUser"]) {
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
		cout << "Tai khoan da chon: " << (string)acc["staffs"][n]["name"] << endl;
		cout << "Mat khau cu: " << (string)acc["staffs"][n]["pass"] << endl;
		cout << "Mat khau moi: ";
		string s;
		cin >> s;
		cout << "Xac nhan doi? \nNhan \'Y\' de doi, bat ki de huy!" << endl;
		char a;
		cin >> a;
		if (a == 'y' || a == 'Y') {
			acc["staffs"][n]["pass"]=s;
			exportAcc(acc);
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
	json acc = importAcc();
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
		for (int i = 0; i < acc["nUser"]; i++) {
			if (uName == (string)acc["staffs"][i]["name"] || uName =="admin") {
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
		acc["staffs"].push_back({ {"name",uName},{"pass",pw}});
		acc["nUser"] = acc["nUser"] + 1;
		exportAcc(acc);
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
		default:
			break;
		}

	} while (a != '4');

}