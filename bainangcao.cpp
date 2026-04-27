#include <iostream>
#include <chrono>

using namespace std;

//  Node 
struct Node {
    int data;
    Node* next;
};

// Tạo danh sách vòng 
Node* taoDanhSachVong(int n) {
    if (n <= 0) return nullptr;

    Node* dau = nullptr;
    Node* cuoi = nullptr;

    for (int i = 1; i <= n; i++) {
        Node* nodeMoi = new Node();
        nodeMoi->data = i;
        nodeMoi->next = nullptr;

        if (dau == nullptr) {
            dau = cuoi = nodeMoi;
        } else {
            cuoi->next = nodeMoi;
            cuoi = nodeMoi;
        }
    }

    // nối vòng
    cuoi->next = dau;

    return dau;
}
//Tìm người thắng
void timNguoiThang(Node* dau, int m) {
    if (dau == nullptr) return;

    Node* hienTai = dau;     // người đang giữ bóng
    Node* truoc = dau;       // người đứng trước

    // tìm node cuối để làm "truoc" ban đầu
    while (truoc->next != dau) {
        truoc = truoc->next;
    }

    while (hienTai->next != hienTai) {
        // đếm m bước
        for (int i = 0; i < m; i++) {
            truoc = hienTai;
            hienTai = hienTai->next;
        }

        // xóa người bị loại
        truoc->next = hienTai->next;

        Node* xoa = hienTai;
        hienTai = hienTai->next;
        delete xoa;
    }

    cout << "\nNguoi con lai la: " << hienTai->data << endl;
    delete hienTai;
}
