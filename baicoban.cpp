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
}

int main() {
     List dsSV;
    khoiTao(dsSV);

    //CASE 1
    cout << "CASE 1: DANH SACH TRONG\n";
    xuatDanhSach(dsSV);
    xuatDanhSach(dsSV);
     return 0;
}