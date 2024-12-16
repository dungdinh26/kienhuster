#include <iostream>
#include <string>
using namespace std;

#define MAXLENGTH 100         // Chỉ số tối đa của mảng
#define NIL -1                // Giá trị đại diện cho nút rỗng

typedef string DataType;       // Kiểu dữ liệu của các nút là string
typedef int Node;

struct Tree {
    DataType Data[MAXLENGTH]; // Lưu giá trị của các nút
    int MaxNode;              // Số lượng nút hiện tại trong cây

    // Constructor để khởi tạo cây
    Tree() : MaxNode(0) {}
};

// Kiểm tra cây rỗng
bool EmptyTree(const Tree& T) {
    return T.MaxNode == 0;
}

// Xác định nút gốc trong cây
Node Root(const Tree& T) {
    if (!EmptyTree(T))
        return 0; // Nút gốc luôn ở vị trí 0
    else
        return NIL;
}

// Con trái của nút p
int Left_Child(Node p, const Tree& T) {
    return 2 * (p + 1) - 1;
   // Trả về NIL nếu vượt quá số nút trong cây
}

// Con phải của nút p
int Right_Child(Node p, const Tree& T) {
    return 2 * (p + 1);
     // Trả về NIL nếu vượt quá số nút trong cây
}

// Hàm nhập dữ liệu cho cây
void InputTree(Tree& T) {
    cout << "Nhap so luong nut cua cay (toi da " << MAXLENGTH << "): ";
    cin >> T.MaxNode;

    if (T.MaxNode > MAXLENGTH || T.MaxNode <= 0) {
        cout << "So luong nut khong hop le!" << endl;
        T.MaxNode = 0; // Đặt cây rỗng nếu số lượng không hợp lệ
        return;
    }

    cin.ignore(); // Bỏ dòng trống sau khi nhập số lượng nút
    cout << "Nhap gia tri cac nut cua cay:" << endl;
    for (int i = 0; i < T.MaxNode; i++) {
        cout << "Gia tri nut " << i+1<< ": ";
        getline(cin, T.Data[i]); // Dùng getline để nhập chuỗi
    }
    cout << "Cay da duoc khoi tao thanh cong." << endl;
}

// Duyệt hậu tự (LRN)
void LRN(Node p, const Tree& T) {
    if (p == NIL || p >= T.MaxNode) return;

    

    LRN(Left_Child(p, T), T); // Duyệt con trái
    LRN(Right_Child(p, T), T); // Duyệt con phải
    cout << T.Data[p] << " "; // Xử lý nút hiện tại
}

// Duyệt tiền tự (NLR)
void NLR(Node p, const Tree& T) {
    if (p == NIL || p >= T.MaxNode) return;

    cout << T.Data[p] << " "; // Xử lý nút hiện tại
   

    NLR(Left_Child(p, T), T); // Duyệt con trái
    NLR(Right_Child(p, T), T); // Duyệt con phải
}

// Hàm chính để kiểm tra
int main() {
    Tree T;
    InputTree(T);

    if (EmptyTree(T)) {
        cout << "Cay rong!" << endl;
        return 0;
    }

    cout << "\nDuyet hau tu (LRN): ";
    LRN(Root(T), T);

    cout << "\nDuyet tien tu (NLR): ";
    NLR(Root(T), T);

    return 0;
}
