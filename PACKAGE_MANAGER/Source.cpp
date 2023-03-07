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
cout << s;
cout << "Loai may ('L': May tinh, 'P': Dien thoai) :";
cin >> f.type;
if (f.type != 'l' && f.type != 'L' && f.type != 'P' && f.type != 'p')
{
	goto step1;

}
else {
	if (f.type == 'l' || f.type == 'L') {
		s += "Loai may: L - Laptop,\n";
	}
	else s += "Loai may: P - Dien thoai,\n";

}
s += "Ten may: ";
system("cls");
cout << s;
cin.ignore(99999, '\n'); cin.clear();
getline(cin, f.name);
s += f.name + ",\n";
system("cls");
cout << s << "Ma dong may (viet lien khong dau): ";
getline(cin, f.code);
s += "Ma dong may: " + f.code + ",\n";
system("cls");
step2:
cout << s << "Nhap so luong nhap vao: ";
cin >> f.q;

if (f.q < 1) {
	system("cls");
	cout << "So luong khong hop le!" << endl;
	cin.clear();
	cin.ignore(99999, '\n');
	goto step2;
}
else {
	s += "So luong: " + to_string(f.q) + " (chiec),\n";
}
system("cls");
step3:
cout << s << "Nhap don gia (nghin vnd):";
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
cout << s << endl;
cout << "1. Tiep tuc hang moi| 2. Ket thuc nhap | 3. Huy nhap" << endl;
char a;
cin >> a;
if (a == '1' || a == '2') {
	outp["items"].push_back(
		{ {"type",f.type},
			{"name",f.name},
			{"idModel",f.code},
			{"quantity",f.q},
			{"price",f.price}
		}
	);
	outp.push_back({ "n",n });
	if (a == '1') {
		goto newStep;
	}
	else {
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