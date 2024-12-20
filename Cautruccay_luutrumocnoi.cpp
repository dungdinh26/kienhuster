#include <iostream>
#include <string>
using namespace std;

struct NODE {
    char data;
    NODE* left;
    NODE* right;

    NODE(char val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

struct QueueNode {
    NODE* data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
};

void InitQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

bool IsEmpty(Queue* q) {
    return q->front == NULL;
}

void Enqueue(Queue* q, NODE* node) {
    QueueNode* newNode = new QueueNode{node, NULL};
    if (IsEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

NODE* Dequeue(Queue* q) {
    if (IsEmpty(q)) {
        return NULL;
    }
    QueueNode* temp = q->front;
    NODE* data = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    delete temp;
    return data;
}

NODE* MAKE_NODE(char data) {
    NODE* p = new NODE(data);
    return p;
}

bool IS_EMPTY(NODE* root) {
    return root == NULL;
}

NODE* INSERT(NODE* root, char data) {
    NODE* newNode = MAKE_NODE(data);

    if (IS_EMPTY(root)) {
        return newNode;
    }

    Queue q;
    InitQueue(&q);
    Enqueue(&q, root);

    while (!IsEmpty(&q)) {
        NODE* current = Dequeue(&q);

        if (current->left == NULL) {
            current->left = newNode;
            return root;
        } else {
            Enqueue(&q, current->left);
        }

        if (current->right == NULL) {
            current->right = newNode;
            return root;
        } else {
            Enqueue(&q, current->right);
        }
    }

    return root;
}

void INFIX(NODE* root) {
    if (IS_EMPTY(root)) return;
    INFIX(root->left);
    cout << root->data << " ";
    INFIX(root->right);
}

void PREFIX(NODE* root) {
    if (IS_EMPTY(root)) return;
    cout << root->data << " ";
    PREFIX(root->left);
    PREFIX(root->right);
}

void POSTFIX(NODE* root) {
    if (IS_EMPTY(root)) return;
    POSTFIX(root->left);
    POSTFIX(root->right);
    cout << root->data << " ";
}

int main() {
    NODE* root = NULL;
    char data;
    int n = 7;

    for (int i = 0; i < n; i++) {
        cin >> data;
        root = INSERT(root, data);
    }

    cout << "Trung to (Infix): ";
    INFIX(root);
    cout << endl;

    cout << "Hau to (Postfix): ";
    POSTFIX(root);
    cout << endl;

    cout << "Tien to (Prefix): ";
    PREFIX(root);
    cout << endl;

    return 0;
}
