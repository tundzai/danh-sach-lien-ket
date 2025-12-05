#include <bits/stdc++.h>
using namespace std;
enum KieuDuLieu {
    KIEU_INT,
    KIEU_FLOAT,
    KIEU_STRING
};
class DanhSachLienKetDon {
private:
    struct Nut {
        KieuDuLieu kieu;

        union GiaTri {
            int soNguyen;
            float soThuc;
            string* chuoi;

            GiaTri() {}
            ~GiaTri() {}
        } duLieu;

        Nut* nutKeTiep;

        Nut(int giaTri) : kieu(KIEU_INT), nutKeTiep(nullptr) {
            duLieu.soNguyen = giaTri;
        }

        Nut(float giaTri) : kieu(KIEU_FLOAT), nutKeTiep(nullptr) {
            duLieu.soThuc = giaTri;
        }

        Nut(const string& giaTri) : kieu(KIEU_STRING), nutKeTiep(nullptr) {
            duLieu.chuoi = new string(giaTri);
        }

        ~Nut() {
            if (kieu == KIEU_STRING && duLieu.chuoi != nullptr) {
                delete duLieu.chuoi;
            }
        }
    };

    Nut* dauDanhSach;
    int kichThuoc;

public:
    DanhSachLienKetDon() : dauDanhSach(nullptr), kichThuoc(0) {}

    ~DanhSachLienKetDon() {
        Nut* hienTai = dauDanhSach;
        while (hienTai != nullptr) {
            Nut* nutKeTiep = hienTai->nutKeTiep;
            delete hienTai;
            hienTai = nutKeTiep;
        }
    }

    int LayKichThuoc() const {
        return kichThuoc;
    }

    void ThemCuoi(int giaTri) { ThemCuoiNut(new Nut(giaTri)); }
    void ThemCuoi(float giaTri) { ThemCuoiNut(new Nut(giaTri)); }
    void ThemCuoi(const string& giaTri) { ThemCuoiNut(new Nut(giaTri)); }

    void ThemCuoiNut(Nut* nutMoi) {
        if (dauDanhSach == nullptr) {
            dauDanhSach = nutMoi;
        } else {
            Nut* hienTai = dauDanhSach;
            while (hienTai->nutKeTiep != nullptr) {
                hienTai = hienTai->nutKeTiep;
            }
            hienTai->nutKeTiep = nutMoi;
        }
        kichThuoc++;
        cout << "Da them mot phan tu vao cuoi\n";
    }

    void ChenGiua(int giaTri, int viTri) { ChenGiuaNut(new Nut(giaTri), viTri); }
    void ChenGiua(float giaTri, int viTri) { ChenGiuaNut(new Nut(giaTri), viTri); }
    void ChenGiua(const string& giaTri, int viTri) { ChenGiuaNut(new Nut(giaTri), viTri); }

    void ChenGiuaNut(Nut* nutMoi, int viTri) {
        if (viTri < 0 || viTri > kichThuoc) {
            cout << "Vi tri chen khong hop le\n";
            delete nutMoi;
            return;
        }

        if (viTri == 0) {
            nutMoi->nutKeTiep = dauDanhSach;
            dauDanhSach = nutMoi;
        } else {
            Nut* hienTai = dauDanhSach;
            for (int i = 0; i < viTri - 1; ++i) {
                hienTai = hienTai->nutKeTiep;
            }
            nutMoi->nutKeTiep = hienTai->nutKeTiep;
            hienTai->nutKeTiep = nutMoi;
        }
        kichThuoc++;
        cout << "=> Da chen mot phan tu vao vi tri " << viTri << "\n";
    }

    void XoaTaiViTri(int viTri) {
        if (dauDanhSach == nullptr || viTri < 0 || viTri >= kichThuoc) {
            cout << " Vi tri xoa khong hop le hoac danh sach rong\n";
            return;
        }

        Nut* nutCanXoa;
        if (viTri == 0) {
            nutCanXoa = dauDanhSach;
            dauDanhSach = dauDanhSach->nutKeTiep;
        } else {
            Nut* hienTai = dauDanhSach;
            for (int i = 0; i < viTri - 1; ++i) {
                hienTai = hienTai->nutKeTiep;
            }
            nutCanXoa = hienTai->nutKeTiep;
            hienTai->nutKeTiep = nutCanXoa->nutKeTiep;
        }

        delete nutCanXoa;
        kichThuoc--;
        cout << "=> Da xoa phan tu tai vi tri " << viTri << "\n";
    }

    void InDanhSach() const {
        Nut* hienTai = dauDanhSach;
        if (hienTai == nullptr) {
            cout << "\nDANH SACH HIEN TAI: RONG (Sz: 0)\n";
            return;
        }
        cout << "\nDANH SACH HIEN TAI (Sz: " << kichThuoc << "): ";
        while (hienTai != nullptr) {
            if (hienTai->kieu == KIEU_INT) {
                cout << " " << hienTai->duLieu.soNguyen;
            } else if (hienTai->kieu == KIEU_FLOAT) {
                cout << " " << hienTai->duLieu.soThuc;
            } else if (hienTai->kieu == KIEU_STRING) {
                cout << " \"" << *(hienTai->duLieu.chuoi) << "\"";
            } else {
                cout << "Kieu khong xac dinh";
            }
            if (hienTai->nutKeTiep != nullptr) {
                cout << "  ";
            }
            hienTai = hienTai->nutKeTiep;
        }
        cout << "\n";
    }
};

void NhapVaThemCuoi(DanhSachLienKetDon& danhSach) {
    int kieu;
    cout << "Chon kieu du lieu\n";
    cout << "1.int\n";
    cout << "2.float\n";
    cout << "3.string\n";
    cout << "Nhap lua chon: ";
    if (!(cin >> kieu)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); return; }

    try {
        if (kieu == 1) {
            int giaTri;
            cout << "Nhap gia tri: ";
            if (cin >> giaTri) danhSach.ThemCuoi(giaTri);
        } else if (kieu == 2) {
            float giaTri;
            cout << "Nhap gia tri: ";
            if (cin >> giaTri) danhSach.ThemCuoi(giaTri);
        } else if (kieu == 3) {
            string giaTri;
            cout << "Nhap gia tri: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, giaTri);
            danhSach.ThemCuoi(giaTri);
        } else {
            cout << "Lua chon kieu du lieu khong dung\n";
        }
    } catch (...) {
        cout << "Loi nhap du lieu\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void NhapVaChenGiua(DanhSachLienKetDon& danhSach) {
    int kieu, viTri;
    cout << "Chon kieu du lieu de chen:\n";
    cout << "1.int\n";
    cout << "2.float\n";
    cout << "3.string\n";
    cout << "Nhap lua chon: ";
    if (!(cin >> kieu)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); return; }

    cout << "Nhap vi tri muon chen (0 -> " << danhSach.LayKichThuoc() << "): ";
    if (!(cin >> viTri)) { cout << "Loi nhap vi tri\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); return; }

    try {
        if (kieu == 1) {
            int giaTri;
            cout << "Nhap gia tri: ";
            if (cin >> giaTri) danhSach.ChenGiua(giaTri, viTri);
        } else if (kieu == 2) {
            float giaTri;
            cout << "Nhap gia tri: ";
            if (cin >> giaTri) danhSach.ChenGiua(giaTri, viTri);
        } else if (kieu == 3) {
            string giaTri;
            cout << "Nhap gia tri: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, giaTri);
            danhSach.ChenGiua(giaTri, viTri);
        } else {
            cout << "Lua chon kieu du lieu khong dung\n";
        }
    } catch (...) {
        cout << "Loi nhap du lieu hoac vi tri\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


int main() {
    DanhSachLienKetDon danhSach;
    int luaChon = 0;
    int viTri;

    do {
        cout << " MENU DANH SACH LIEN KET \n";
        cout << "1.Them phan tu vao CUOI\n";
        cout << "2. Them phan tu vao GIUA\n";
        cout << "3. Xoa phan tu theo vi tri\n";
        cout << "4. Lay kich thuoc danh sach\n";
        cout << "5. Hien thi danh sach\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "     ---     \n";
        cout << "Moi ban nhap lua chon: ";

        if (!(cin >> luaChon)) {
            cout << "\n Lua chon khong hop le. Vui long nhap so.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (luaChon) {
            case 1:
                NhapVaThemCuoi(danhSach);
                break;

            case 2:
                NhapVaChenGiua(danhSach);
                break;

            case 3:
                cout << "Nhap vi tri muon xoa (0 -> " << danhSach.LayKichThuoc() - 1 << "): ";
                if (!(cin >> viTri)) break;
                danhSach.XoaTaiViTri(viTri);
                break;

            case 4:
                cout << "\n Kich thuoc danh sach hien tai la: " << danhSach.LayKichThuoc() << "\n";
                break;

            case 5:
                danhSach.InDanhSach();
                break;

            case 0:
                cout << "\nTam biet!\n";
                break;

            default:
                cout << "\nLua chon khong ton tai. Vui long nhap lai.\n";
                break;
        }

        if (cin.fail() && luaChon != 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while (luaChon != 0);
}
