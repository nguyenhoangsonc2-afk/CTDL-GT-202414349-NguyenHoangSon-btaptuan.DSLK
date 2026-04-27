#include <iostream>
#include <string.h>

using namespace std;

// khai báo ctdl

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];     
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];      
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

// các hàm

void khoiTao(List &ds) {
    ds.first = ds.last = NULL;
}

Node* taoNode(SinhVien sv) {
    Node* p = new Node;
    p->data = sv;
    p->link = NULL;
    return p;
}
//Thêm có thứ tự
void themCoThuTu(List &ds, SinhVien sv) {
    Node* p = taoNode(sv);

    if (ds.first == NULL || strcmp(sv.maSV, ds.first->data.maSV) < 0) {
        p->link = ds.first;
        ds.first = p;
        if (ds.last == NULL) ds.last = p;
    } else {
        Node* hienTai = ds.first;
        while (hienTai->link != NULL &&
               strcmp(hienTai->link->data.maSV, sv.maSV) < 0) {
            hienTai = hienTai->link;
        }
        p->link = hienTai->link;
        hienTai->link = p;
        if (p->link == NULL) ds.last = p;
    }
}

// Xuất
void xuatSinhVien(SinhVien sv) {
    cout << "[" << sv.maSV << "] " << sv.hoTen << " | "
         << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam
         << " | " << sv.lop << " | " << sv.khoa << endl;
}

void xuatDanhSach(List ds) {
    if (ds.first == NULL) {
        cout << "(Danh sach rong)" << endl;
        return;
    }
    Node* p = ds.first;
    while (p != NULL) {
        xuatSinhVien(p->data);
        p = p->link;
    }
}
// In sinh viên trùng ngày sinh
void inSinhVienTrungNgaySinh(List ds) {
    bool co = false;
    for (Node* p = ds.first; p != NULL; p = p->link) {
        bool trung = false;
        for (Node* q = ds.first; q != NULL; q = q->link) {
            if (p != q &&
                p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) {
                trung = true;
                break;
            }
        }
        if (trung) {
            xuatSinhVien(p->data);
            co = true;
        }
    }
    if (!co) cout << "khong co sinh vien trung ngay sinh\n";
}


//Xóa sinh viên trùng ngày sinh
void xoaSinhVienTrungNgaySinh(List &ds) {
    if (ds.first == NULL) return;

    //lưu các ngày sinh bị trùng
    Ngay trung[100];
    int dem = 0;

    for (Node* p = ds.first; p != NULL; p = p->link) {
        for (Node* q = p->link; q != NULL; q = q->link) {
            if (p->data.ngaySinh.ngay == q->data.ngaySinh.ngay &&
                p->data.ngaySinh.thang == q->data.ngaySinh.thang &&
                p->data.ngaySinh.nam == q->data.ngaySinh.nam) {

                bool daCo = false;
                for (int i = 0; i < dem; i++) {
                    if (trung[i].ngay == p->data.ngaySinh.ngay &&
                        trung[i].thang == p->data.ngaySinh.thang &&
                        trung[i].nam == p->data.ngaySinh.nam) {
                        daCo = true;
                        break;
                    }
                }

                if (!daCo) {
                    trung[dem++] = p->data.ngaySinh;
                }
            }
        }
    }

// xóa các sinh viên có ngày sinh trùng
    Node* p = ds.first;
    Node* prev = NULL;

    while (p != NULL) {
        bool canXoa = false;

        for (int i = 0; i < dem; i++) {
            if (p->data.ngaySinh.ngay == trung[i].ngay &&
                p->data.ngaySinh.thang == trung[i].thang &&
                p->data.ngaySinh.nam == trung[i].nam) {
                canXoa = true;
                break;
            }
        }

        if (canXoa) {
            Node* tmp = p;
            if (p == ds.first) {
                ds.first = p->link;
                p = ds.first;
                prev = NULL;
                if (ds.first == NULL) ds.last = NULL;
            } else {
                prev->link = p->link;
                if (p == ds.last) ds.last = prev;
                p = prev->link;
            }
            delete tmp;
        } else {
            prev = p;
            p = p->link;
        }
    }
}
int main() {
     List dsSV;
    khoiTao(dsSV);

    //CASE 1
    cout << "CASE 1: DANH SACH TRONG\n";
    xuatDanhSach(dsSV);
    xuatDanhSach(dsSV);
     // CASE 2
    cout << "\nCASE 2: KHONG TRUNG\n";
    SinhVien s1 = {"2023001", "A", 0, {1,1,2005}, "", "L1", "CNTT"};
    SinhVien s2 = {"2023002", "B", 1, {2,2,2005}, "", "L2", "Dien"};
    themCoThuTu(dsSV, s1);
    themCoThuTu(dsSV, s2);

    xuatDanhSach(dsSV);
    inSinhVienTrungNgaySinh(dsSV);

    // CASE 3
    cout << "\nCASE 3: CO TRUNG \n"; // danh sách có svien trùng ngày sinh
    SinhVien s3 = {"2023005", "C", 0, {1,1,2005}, "", "L1", "CNTT"};
    SinhVien s4 = {"2023003", "D", 0, {3,3,2005}, "", "L3", "KT"};
    SinhVien s5 = {"2023004", "E", 1, {3,3,2005}, "", "L3", "KT"};

    themCoThuTu(dsSV, s3);
    themCoThuTu(dsSV, s4);
    themCoThuTu(dsSV, s5);

    cout << "Truoc khi xoa:\n";
    xuatDanhSach(dsSV);

    cout << "Sinh vien trung:\n"; //sinh viên trùng
    inSinhVienTrungNgaySinh(dsSV);

    xoaSinhVienTrungNgaySinh(dsSV);

    cout << "Sau khi xoa:\n";
    xuatDanhSach(dsSV);
     return 0;
}