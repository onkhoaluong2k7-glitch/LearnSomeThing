#include <stdio.h>
#include <stdlib.h>

typedef enum {RED, BLACK} Color;

// Cấu trúc của 1 node trong cây RB
typedef struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
} Node;

Node *root = NULL;
// Tạo một node mới với giá trị key
Node* createNode(int key){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->color = RED;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode; 
}

// phép quay trái
void rotateLeft(Node **root, Node *x){
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL){
        *root = y;
    } else if (x->parent->right == x){
        x->parent->right = y;
    } else if (x->parent->left == x){
        x->parent->left = y;
    }
    y->left = x;
    x->parent = y;
}

// Phép quay phải
void rotateRight(Node **root, Node *x){
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL){
        *root = y;
    } else if (x->parent->right == x){
        x->parent->right = y;
    } else if (x->parent->left == x){
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void fixInsert(Node **root, Node *z){
    while(z->parent && z->parent->color == RED){
        if (z->parent == z->parent->parent->left){
            Node* uncle = z->parent->parent->right;
            if (uncle != NULL && uncle->color == RED){
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right){
                    z = z->parent;
                    rotateLeft(root, z);
                } 

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        } else {
            Node* uncle = z->parent->parent->right;
            if (uncle != NULL && uncle->color == RED){
                uncle->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left){
                    z = z->parent;
                    rotateRight(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z);
            }
        }
    }

    (*root)->color = BLACK;
};

void insert(Node **root, int key){
    Node *x = *root;
    Node *parent = NULL;
    Node *z = createNode(key);

    while(x != NULL){
        parent = x;
        if (z->key < parent->key) x = x->left;
        else x = x->right;
    }
    z->parent = parent;
    if (parent == NULL) *root = z;
    else if (parent->key > z->key) parent->left = z;
    else if (parent->key < z->key) parent->right = z;
    fixInsert(root, z);
}

void traveral(Node* root){
    if (root == NULL) return;
    printf("%d ", root->key);

    traveral(root->left);
    traveral(root->right);
}

Node* minimumNode(Node* x){
    while (x->left != NULL) x = x->left;
    return x;
}

// thay the Node u boi Node v
void replaceNode(Node **root, Node *u, Node *v){
    if (!u->parent) *root = v;
    else if (u == u->parent->right) u->parent->right = v;
    else u->parent->left = v;
    if (v) v->parent = u->parent;
}

void fixDelete(Node **root, Node * x){
    while(x != *root  && (x == NULL || x->color == BLACK)){
        if ( x == x->parent->left){
            Node *w = x->parent->right;
            if (w != NULL && w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(root, x->parent);
                w = x->parent->right;
            }
            if ((w->left == NULL || w->left->color == BLACK)
            && (w->right == NULL || w->right->color == BLACK)){
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK){
                    if (w->left) w->left->color = BLACK;
                    rotateLeft(root, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                rotateLeft(root, x->parent);
                x = *root;
            } 
        } else {
            Node* w = x->parent->left;
            if (w->color);
        }
    }
}

void deleteNode(Node** root, int key){
    Node *z = *root, *x, *y;
    while (z && z->key != key){
        if (z->key < key) z = z->right;
        else z = z->left;
    }
    if (!z) return;

    y = z;
    Color ori_y = y->color;
    
    if (!z->left){
        x = z->right;
        replaceNode(root, z, z->right);
    } else if (!z->right){
        x = z->left;
        replaceNode(root, z, z->left);
    } else {
        y = minimumNode(z->right);
        ori_y = y->color;
        x = y->right;

        if (y->parent == z){
            if (x) x->parent = y;
        } else {
            replaceNode(root, y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
        }

        replaceNode(root, z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->color = z->color;
    }
    free(z);
    if (ori_y == BLACK){
        fixDelete(root, x);
    }
}

int main(){
    insert(&root, 10); 
    insert(&root, 20); 
    insert(&root, 30); 
    insert(&root, 15); 
    insert(&root, 25); 
    insert(&root, 5); 
    printf("Preorder:\n"); 
    traveral(root); 

    return 0;
}