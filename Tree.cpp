/*Đây là đoạn script mô tả sơ lược về một cái cây.*/
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;
// Cây này sẽ liên kết với các nút bằng cách liên kết với đứa con đầu tiên
// và người anh em tiếp theo của nó
typedef struct Node{
    int data;
    struct Node* firstChild;
    struct Node* nextSibling;
} Node;

// Ta có 3 cách duyệt một cây
// Cách đầu tiên là preorder: thứ tự trước
void preOrder(Node* root){
    if (root == NULL) return;
    printf("%d ", root->data);
    Node* p = root->firstChild;
    while( p != NULL ){
        preOrder(p);
        p = p->nextSibling;
    }
}

// Duyệt theo mức: level Traversal
void levelTraversal(Node* root){
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* p = q.front();
        q.pop();
        printf("%d ", p->data);
        Node* p1 = p->firstChild;
        while(p1 != NULL){
            q.push(p1);
            p1 = p1->nextSibling;
        }
    }
    printf("\n");
}

// Duyệt theo thứ tự sau: Post Order
void postOrder(Node* root){
    if(root == NULL) return;
    Node* p = root->firstChild;
    while(p != NULL){
        postOrder(p);
        p = p->nextSibling;
    }
    printf("%d ", root->data);
}

// Hàm tìm và trả về node có giá trị là val
Node* find(Node* root, int val){
    if (root == NULL) return NULL;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* p = q.front();
        q.pop();
        if (p->data == val) return p;
        Node* p1 = p->firstChild;
        while(p1 != NULL){
            q.push(p1);
            p1 = p1->nextSibling;
        }
    }
    return NULL;
}

// Hàm tạo node và cấp phát động
Node* makeNode(int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    return newNode;
}

// Hàm chèn một node vào cây có giá trị làm con cua root
void insert1(Node* root, int val){
    if (root == NULL) return;
    Node* newNode = makeNode(val);
    if (root->firstChild == NULL) root->firstChild = newNode;
    else {
        Node* p = root->firstChild;
        while(p->nextSibling != NULL){
            p = p->nextSibling;
        }
        p->nextSibling = newNode;
    }

}

// Hàm trả về số node lá trên cây
int countLeaves(Node* root){
    if (root == NULL) return 0;
    int sum = 0;
    Node* p = root->firstChild;
    if (p == NULL) return 1;
    while(p != NULL){
        sum += countLeaves(p);
        p = p->nextSibling;
    }
    return sum;
}

// Hàm trả về số node trên cây
int countNode(Node* root){
    if (root == NULL) return 0;
    int sum = 0;
    Node* p = root->firstChild;
    while(p != NULL){
        sum += countLeaves(p);
        p = p->nextSibling;
    }
    return sum + 1;
}
// Hàm trả về node cha của node r
Node* parent(Node* root, Node* r){
    if (root == NULL) return NULL;
    Node* p = root->firstChild;
    while(p != NULL){
        if (p == r) return root;
        Node* pq = parent(p, r);
        if (pq != NULL) return pq;
        p = p->nextSibling;
    }
    return NULL;
}

// Hàm trả về độ cao của root
int height (Node* root){
    if (root == NULL) return 0;
    Node* p = root->firstChild;
    int max_h = 0;
    while(p != NULL){
        int h = height(p);
        max_h = max(max_h, h);
        p = p->nextSibling;
    }
    return max_h + 1;  
}
// Hàm trả về độ sâu của node r
int depth(Node* root, int val, int d){
    if (root == NULL) return -1;
    if (root->data == val) return d;
    Node* p = root->firstChild;
    while(p != NULL){
        if (p->data == val) return d+1;
        int dv = depth(p, val, d+1);
        if (dv > 0) return dv;
        p = p->nextSibling;
    }
    return -1;
    
}
int callDepth(Node* root, int val){
    return depth(root, val, 0);
}

int main(){
    
    return 0; 
}