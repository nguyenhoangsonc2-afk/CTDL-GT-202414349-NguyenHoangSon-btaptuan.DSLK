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