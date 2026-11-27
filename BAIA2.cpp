#include <iostream> // ho tro cin va cout
#include <string> // ho tro string va getline
#include <vector> // cung cap mang dong std:: khi xoa/chen tu dieu chinh kich thuoc
#include <algorithm> // cung cap ham sort() de sap xep du lieu
#include <iomanip> // can le (setw), lam tron so thuc (fixed, setprecision).
using namespace std; // ho tro de khgo std:: truoc ham

class SinhVien {
private:
    string maSV, hoTen, lop;
    float diem1, diem2, diem3, diemTB;
    void tinhDiemTB() { diemTB = (diem1 + diem2 + diem3) / 3; }

public:
    void nhap();
    void xuat() const; // const chi cho phep doc du lieu chu khong the thay doi du lieu
    float getDiemTB() const { return diemTB; }
    string getMaSV() const { return maSV; }   
};

void SinhVien::nhap(){
    cout << "Nhap ma sinh vien: "; cin >> maSV; cin.ignore(); //cin.ignore() xoa hoac bo qua  dulieu con trong bo nho dem
    cout << "Nhap ho ten: "; getline(cin, hoTen); // getline() nhap chuoi ki tu co khoang trang
    cout << "Nhap lop: "; getline(cin, lop);
    cout << "Nhap diem hoc phan 1, 2, 3: ";
    cin >> diem1 >> diem2 >> diem3;
    tinhDiemTB();
}

void SinhVien::xuat() const {
    cout << setw(10) << maSV  //setw(10) khoang cach ki thuoc
         << setw(20) << hoTen 
         << setw(10) << lop 
         << setw(6) << fixed << setprecision(2) << diemTB << endl; // setprecision(2) ep kieu data ve so thap phan co 2 so sau dau phay
}

class QuanLySinhVien {
private:
    vector<SinhVien> ds; // danh sach mang dong luu cac sinh vien
    static bool cmp(const SinhVien &a, const SinhVien &b) { // static ham tinh, so sanh 2 sinh vien
        return a.getDiemTB() > b.getDiemTB();
    }
public:
    void nhapDanhSach();
    void inDanhSach() const;
    void sapXep();
    void timKiem() const;
    void them();
    void xoa();
};

void QuanLySinhVien::nhapDanhSach() {
    int n; cout << "Nhap so luong sinh vien: "; cin >> n; cin.ignore();
    ds.clear(); // xoa toan bo phan tu trong vector, dua ve 0
    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin sinh vien thu " << i+1 << ":\n";
        SinhVien sv; sv.nhap();
        ds.push_back(sv); //"push": Đẩy / Chèn dữ liệu vào. "back": Vị trí phía sau (cuối mảng).
    }
}

void QuanLySinhVien::inDanhSach() const {
    cout << "\nDanh sach sinh vien:\n";
    cout << setw(10) << "MaSV" 
         << setw(20) << "Ho Ten" 
         << setw(10) << "Lop" 
         << setw(6) << "DTB" << endl;
    for (size_t i = 0; i < ds.size(); i++) ds[i].xuat();
}

void QuanLySinhVien::sapXep() {
    sort(ds.begin(), ds.end(), cmp); //ds.begin(), ds.end() xac dinh pvi sx pt dau va cuoi
    cout << "Da sap xep danh sach theo diem TB giam dan.\n";
}

void QuanLySinhVien::timKiem() const {
    string ma; cout << "Nhap ma sinh vien can tim: "; cin >> ma;
    bool found = false;
    for (size_t i = 0; i < ds.size(); i++) {
        if (ds[i].getMaSV() == ma) {
            cout << "Thong tin sinh vien tim thay:\n";
            ds[i].xuat();
            found = true;
            break;
        }
    }
    if (!found) cout << "Khong tim thay sinh vien co ma " << ma << endl;
}

void QuanLySinhVien::them() {
    int pos;
    cout << "Nhap vi tri muon them: ";
    cin >> pos;
    if (pos < 0 || pos > (int)ds.size()) { //ds.size() so luong ptu co trong vector
        cout << "Vi tri khong hop le\n"; return;
    }
    SinhVien sv; sv.nhap();
    ds.insert(ds.begin() + pos, sv); //ds.begin() + pos dich chuyen con tro di pos đvi để con tro chinh xac den vi tri pos
    cout << "Da them sinh vien tai vi tri " << pos << ".\n";
}

void QuanLySinhVien::xoa() {
    int pos;
    cout << "Nhap vi tri muon xoa: ";
    cin >> pos;
    if (pos < 0 || pos >= (int)ds.size()) {
        cout << "Vi tri khong hop le\n"; return;
    }
    cout << "Da xoa sinh vien co ma " << ds[pos].getMaSV() << " tai vi tri " << pos << ".\n";
    ds.erase(ds.begin() + pos); // xoa vi tri sinh viẻn
}

int main() {
    QuanLySinhVien ql;
    ql.nhapDanhSach();
    ql.inDanhSach();
    ql.sapXep();
    ql.inDanhSach();
    ql.timKiem();
    cout << "\nThem sinh vien tai vi tri 0:\n";
    ql.them();
    ql.inDanhSach();
    cout << "\nXoa sinh vien tai vi tri 1:\n";
    ql.xoa();
    ql.inDanhSach();
    cout << "Chuong trinh ket thuc.\n";
    return 0;
}
