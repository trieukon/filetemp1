#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;
using json = nlohmann::json;

struct newPkg
{
	char type;
	string idModel, name, idPksg;
	long long price, expPrice;
	int q;
};
string toCurr(long long a) {	//ham tra ve string in tien, vd a=1200 (long long) thi return = 1.200.000 (string)
	string s = to_string(a);
	long long n = s.length() - 1, d = 2;
	while (d < n && n >= 3) {
		n = s.length() - 1;
		s.insert((n - d), ".");
		d += 4;
	}
	return s + ".000";
}

string toUP(string inp) { //tra ve string la UPCASE cua string vao
	transform(inp.begin(), inp.end(), inp.begin(), ::toupper);
	return inp;
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
					{"uname","admin"},
					{"name","Nguyen Thien Phu"},
					{"pass","1234"}
						}
				},
				{"nUser",2},
				{"staffs", {
				{
					{"uname","konnn"},
					{"name","Nguyen Thanh Trieu"},
					{"pass","1234"}
				},
				{
					{"uname","qui"},
					{"name","Tran Le Anh Qui"},
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
			{"nExp",0},{"nImp",0},{"pkgs",{}}
		}
		},
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

	if (urn == string(data["account"]["admin"]["uname"]) && pw == (string)data["account"]["admin"]["pass"]) {
		return "";
	}
	else if (data["account"]["nUser"] > 0) {
		int i;
		for (i = 0; i < data["account"]["nUser"]; i++) {
			if (urn == (string)data["account"]["staffs"][i]["uname"] && pw == (string)data["account"]["staffs"][i]["pass"]) {
				return (string)data["account"]["staffs"][i]["uname"];
				break;
			}
		}
		if (i == data["account"]["nUser"]) {
			cout << "Khong tim thay tai khoan nao!" << endl;
			system("pause");
			exit(0);
		}
		
	}

}

string getNameModel(string idModel, json* t, long long* p, int* vt) {	//lay ten tu idModel da cho
	json temp = *t;
	for (int i = 0; i < temp["model"]["L"]["n"]; i++) {
		if ((string)temp["model"]["L"]["goods"][i]["id"] == idModel) {
			*p = temp["model"]["L"]["goods"][i]["price"];
			*vt = i;
			return (string)temp["model"]["L"]["goods"][i]["name"];
			break;
		}
	}
	for (int i = 0; i < temp["model"]["P"]["n"]; i++) {
		if ((string)temp["model"]["P"]["goods"][i]["id"] == idModel) {
			*p = temp["model"]["P"]["goods"][i]["price"];
			return (string)temp["model"]["P"]["goods"][i]["name"];
			break;
		}
	}
	return "";
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
		n =(int) a["packages"]["nImp"] + (int)a["packages"]["nExp"];
		if (n > 0) {
			do {
				if (s == a["packages"]["pkgs"][n-1]["id"]) {
				n = (int)a["packages"]["nImp"] + (int)a["packages"]["nExp"];
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

void displayDetail(json t,json pkg) {
	system("cls");
	cout << "CHI TIET DON HANG!!!" << endl << string(30, '-') << endl;;
	cout << "ID: " << t["id"] << endl;
	cout << "Nguoi len don: " << (string)t["name"] << endl;
	cout << "Thoi gian len don: " << (string)t["time"] << endl;
	if ((string)t["t"] == "imp") {
		cout << "Loai don hang: Nhap vao" << endl;
		cout << "Nhap tu doanh nghiep: " << t["from"] << endl;
	}
	else {
		cout << "Loai don hang: Xuat ra" << endl;
		cout << "Xuat den doanh nghiep: " << t["to"] << endl;
	}
	cout << "--------- Chi tiet don hang -----------" << endl;
	string s;
	long long p,sum=0;
	int vt;
	for (int i = 0; i < t["n"]; i++) {
		s = getNameModel((string)t["items"][i]["idModel"], &pkg, &p, &vt);
		if ((string)t["t"] == "exp") {
			p = t["items"][i]["pExp"];
		}
		cout << i + 1 << ". " << (string)t["items"][i]["idModel"] << " | " << s <<endl;
		cout << "\tSo luong * Don gia: " << t["items"][i]["quantity"] << " * " << toCurr(p) << " = " << toCurr((long long)t["items"][i]["quantity"] * p) << endl;
		sum += (long long)t["items"][i]["quantity"] * p;
	}
	cout << "Tong gia tri: " << toCurr(sum) << "vnd." << endl;
	cout << string(30, '-') << endl;

}

void findIdPkgs(json*pkg) {	//muc 2 cua quan ly don hang
	json inp = *pkg; 
	inp = inp["packages"];	
	int n = (int)inp["nImp"] + inp["nExp"];
	if (n< 1) {
		cout << "Khong co don hang nao trong csdl!" << endl;
		system("pause");
	}
	else {
		system("cls");
		cout << "NHAP MA DINH DANH CUA DON HANG DE TRUY XUAT" << endl;
		cout << string(20,'-') << endl << "/>";
		string inS;
		cin.ignore();
		cin >> inS;	
		inS = toUP(inS);
		cin.clear();
		while(n--) {
			if ((string)inp["pkgs"][n]["id"] == inS) {
				displayDetail(inp["pkgs"][n],*pkg);
				system("pause");
				break;				
			}
		}
		if (n < 0) {
			cout << "Khong tim thay don hang nay!" << endl;
			system("pause");
		}
	}
	
}

long checkSameOrderd(json t, string id,int n) { //tra ve vi tri ma idModel dung trong mang json neu no ton tai truoc do, k co tra ve -1
	if (n>0) for (int i = 0; i < n; i++) {
		if ((string)t[i]["idModel"] == id) return i;
	}
	return -1;
}

void printModelQ(json t, char type) {	//in cac mau may da tung nhap
	cout << string(30, '-') << endl;;
	if (type == 'L') {
		for (int i = 0; i < t["model"]["L"]["n"]; i++) {
			cout << t["model"]["L"]["goods"][i]["id"] << " - " << t["model"]["L"]["goods"][i]["name"] << endl;
		}
	}
	else {
		for (int i = 0; i < t["model"]["P"]["n"]; i++) {
			cout << t["model"]["P"]["goods"][i]["id"] << " - " << t["model"]["P"]["goods"][i]["name"] << endl;
		}
	}
	cout << string(30, '-') << endl;;
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





bool checkHavingModel(json t, char type) { //Kiem tra su ton tai cua Model da ton tai chua
	if (type == 'L' && (t["model"]["L"]["n"] > 0)) {
		return 1;
	}
	else if (type == 'P' && (t["model"]["P"]["n"] > 0)) {
		return 1;
	}
	else return 0;
}


void displayExp(json items, json t, int n) {
	if (n > 0)
	{
		int* p = new int[n];
		long long sum = 0;
		cout << string(30, '-') << endl << "DON HANG XUAT DI BAO GOM: " << endl;
		for (int i = 0; i < n; i++) {
			cout << i + 1 << ". " << items[i]["idModel"] << " - ";

			if (t["model"]["L"]["n"] > 0) for (int j = 0; j < t["model"]["L"]["n"]; j++) {
				if (items[i]["idModel"] == t["model"]["L"]["goods"][j]["id"]) {
					cout << t["model"]["L"]["goods"][j]["name"] << " : ";
					p[i] = items[i]["pExp"];
				}
			}
			if (t["model"]["P"]["n"] > 0) for (int j = 0; j < t["model"]["P"]["n"]; j++) {
				if (items[i]["idModel"] == t["model"]["P"]["goods"][j]["id"]) {
					cout << t["model"]["P"]["goods"][j]["name"] << " : ";
					p[i] = items[i]["pExp"];
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


void newPkgExp(json *t,json *items,int* n) {
	json temp = *items;
	json pks = *t;
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

	//Buoc 3: Gan Ten cho mau may vua nhap
	display += "IdModel: \'" + f.idModel + "\' : " + f.name + "\n";
	system("cls");

	int kk = checkSameOrderd(temp, f.idModel, *n); //kiem tra trung don hang
	//Buoc 4: Gan don gia
	if (kk >= 0) {
		f.expPrice = temp[kk]["pExp"];
	}
	else {
	step4:
		cout << display;
		cout << "Don gia von co cua Mau may nay: " << toCurr(f.price) << " (chiec)," << endl;
		cout << "Don gia xuat ra (don vi nghin vnd): ";
		cin >> f.expPrice;
		cin.ignore(999, '\n'); cin.clear();
		if (f.expPrice < 0) {
			system("cls");
			cout << "(Don gia khong hop le!)" << endl;
			goto step4;
		}
	}
	display += "Don gia von: " + toCurr(f.expPrice) + " vnd / chiec,\n";
	display += "Don gia xuat ra: " + toCurr(f.expPrice) + " vnd / chiec,\n" + string(20, '-') + "\n";

	//Buoc 5: Nhap so luong	
	

	system("cls");
step5:	
	int nHave = 0;
	cout << display;	
	if (kk >= 0) {
		nHave = temp[kk]["quantity"];
		cout << "Hien don nay dang xuat: " << nHave << " (chiec)," << endl;
	}	
	int sl = 0;
	if (f.type == 'L') {		
		sl = pks["model"]["L"]["goods"][vt]["quantity"];
	}
	else {
		sl = pks["model"]["P"]["goods"][vt]["quantity"];
	}

	cout << "Trong kho con lai: " << sl << " (chiec)" << endl;
	cout << "So luong xuat ra:";
	cin >> f.q;// cho phep nhap am de tru so don hang dang nhap

	if (f.q == 0) {
		cout << "Da huy yeu cau do so luong nhap vao bang 0!" << endl;
		system("pause");
		return;
		
	}
	if (!(((sl - f.q >= 0) && (f.q > 0)) || (((f.q + nHave) >= 0) && (f.q < 0)))) {
		
		system("cls");
		cout << "Nhap so luong khong hop le!" << endl;
		goto step5;
	};
	//nhap thanh cong
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
			if (temp[kk]["quantity"] == 0) {
				temp.erase(temp.begin()+kk);
			}
		}
		else {
			temp.push_back({
				{"idModel",f.idModel},{"quantity",f.q},{"pExp",f.expPrice} });
			*n = *n + 1;
		}
		updateQuantity(t, f.type, vt, -f.q);

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


void outPkgs(json* pkg,string s) { //Xuat hang
	json t = *pkg;
	if (t["packages"]["pkgs"].size()==0) {
		cout << "Kho rong, khong the xuat don!" << endl;
		system("pause");
		return;
	}
	char a;
	
	json items = {};
	string id = creIdOrder(*pkg),to;
	cout << "NHAP DON HANG MOI: " << endl << string(30, '-') << endl;
	cout << "Nhap ten doanh nghiep xuat den: ";
	cin.ignore();
	getline(cin, to);

	t["packages"]["nExp"] = t["packages"]["nExp"] + 1;
	int n = 0;
renew:
	system("cls");
	cout << "NHAP DON XUAT HANG MOI:" << endl;
	cout << "Ten doanh nghiep xuat hang: " << to << endl;
	cout<< "Ma don hang: " << id << endl << string(30, '-') << endl;
	cout << "LUA CHON NHAP DON HANG:" << endl;
	cout << "1/ Xuat mau trong kho," << endl;
	if (n > 0) {			
		cout << "2/ Luu don hang va tro lai," << endl;
	}
	cout << "0/ Huy bo va tro lai." << endl;
	//==============================
	displayExp(items, t, n);
	//==============================
	cout << "/>";
	cin >> a;
	switch (a)
	{
	case'1': {
		newPkgExp(&t, &items, &n);
			goto renew;
			break;
	}
	case'2': {
			if (n > 0) {
				t["packages"]["pkgs"].push_back({ {"n",n},{"id",id},{"items",items},{"time",now()},{"t","exp"},{"name",s},{"to",to}});
				*pkg = t;
				exportJSON(*pkg);
				cout << "Luu thanh cong!" << endl;
				system("pause");
			}else goto renew;
			break;
	}
	default:
		goto renew;
		break;
	}
}


void displayModels() {
	cout << "-";
}
