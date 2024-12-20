#include <iostream>
#include <string>
using namespace std;

// Định nghĩa một nút trong cây mục lục
struct TreeNode {
    string title;         // Tiêu đề của mục
    int pageCount;        // Số trang của mục
    TreeNode* firstChild; // Con đầu tiên
    TreeNode* nextSibling; // Anh em kế tiếp

    // Constructor
    TreeNode(string t, int p) : title(t), pageCount(p), firstChild(nullptr), nextSibling(nullptr) {}
};

// Định nghĩa cấu trúc cây
struct Tree {
    TreeNode* root; // Nút gốc đại diện cho sách

    // Constructor
    Tree() : root(nullptr) {}

    // Destructor để giải phóng bộ nhớ
    ~Tree() { clearTree(root); }

    // Hàm đệ quy giải phóng bộ nhớ
    void clearTree(TreeNode* node) {
        if (!node) return;
        clearTree(node->firstChild);
        clearTree(node->nextSibling);
        delete node;
    }
};
TreeNode* inputNode() {
    string title;
    int pageCount;
    cout << "Nhap tieu de: ";
    getline(cin, title);
    cout << "Nhap so trang: ";
    cin >> pageCount;
    cin.ignore(); // Bỏ qua ký tự xuống dòng
    return new TreeNode(title, pageCount);
}

void inputTree(TreeNode* parent) {
    int childCount;
    cout << "Nhap so muc con cua \"" << parent->title << "\": ";
    cin >> childCount;
    cin.ignore(); // Bỏ qua ký tự xuống dòng

    TreeNode* prevChild = nullptr;
    for (int i = 0; i < childCount; i++) {
        cout << "\nNhap thong tin muc con thu " << i + 1 << " cua \"" << parent->title << "\":\n";
        TreeNode* child = inputNode();

        if (!prevChild) {
            parent->firstChild = child; // Gắn con đầu tiên
        } else {
            prevChild->nextSibling = child; // Liên kết anh em kế tiếp
        }
        prevChild = child;

        inputTree(child); // Nhập dữ liệu cho con
    }
}
int countChapters(TreeNode* node) {
    if (!node || !node->firstChild) return 0;

    int count = 0;
    TreeNode* current = node->firstChild;
    while (current) {
        count++;
        current = current->nextSibling;
    }
    return count;
}
TreeNode* findLongestChapter(TreeNode* node, TreeNode*& longest) {
    if (!node) return longest;

    if (!longest || node->pageCount > longest->pageCount) {
        longest = node; // Cập nhật chương dài nhất
    }

    // Tìm trong các con
    findLongestChapter(node->firstChild, longest);
    // Tìm trong các anh em
    findLongestChapter(node->nextSibling, longest);

    return longest;
}

bool removeNode(TreeNode* parent, const string& title) {
    TreeNode* current = parent->firstChild;
    TreeNode* prev = nullptr;

    while (current) {
        if (current->title == title) {
            if (prev) {
                prev->nextSibling = current->nextSibling; // Bỏ qua nút cần xóa
            } else {
                parent->firstChild = current->nextSibling; // Cập nhật con đầu tiên
            }

            Tree treeToDelete;
            treeToDelete.root = current; // Gán để giải phóng các con
            return true;
        }
        prev = current;
        current = current->nextSibling;
    }

    // Tìm tiếp trong các con
    current = parent->firstChild;
    while (current) {
        if (removeNode(current, title)) {
            return true;
        }
        current = current->nextSibling;
    }

    return false;
}

bool findAndRemove(Tree& tree, const string& title) {
    if (!tree.root) return false;

    if (tree.root->title == title) {
        // Xóa gốc cây
        Tree treeToDelete;
        treeToDelete.root = tree.root;
        tree.root = nullptr;
        return true;
    }

    return removeNode(tree.root, title);
}
int main() {
    Tree book;
    cout << "Nhap thong tin cuon sach:\n";
    book.root = inputNode();
    inputTree(book.root);

    cout << "\nSo chuong cua cuon sach: " << countChapters(book.root) << endl;

    TreeNode* longestChapter = nullptr;
    findLongestChapter(book.root, longestChapter);
    if (longestChapter) {
        cout << "Chuong dai nhat: " << longestChapter->title 
             << " (" << longestChapter->pageCount << " trang)" << endl;
    }

    string titleToRemove;
    cout << "\nNhap tieu de muc can xoa: ";
    getline(cin, titleToRemove);
    if (findAndRemove(book, titleToRemove)) {
        cout << "Da xoa muc \"" << titleToRemove << "\" khoi sach.\n";
    } else {
        cout << "Khong tim thay muc \"" << titleToRemove << "\".\n";
    }

    return 0;
}
