// doubly-linked
#include <stdio.h>
#include <stdlib.h>

// Cấu trúc cơ bản của một node trong danh sách liên kết đôi
struct Node{
    int data;
    struct Node* prev;
    struct Node* next;
};

// Hàm này để tạo ra một node mới với data được truyền vào
struct Node* makeNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode){
        printf("Cap phat bi loi!!");
        return NULL;
    }
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Hàm này để đưa node mới vào đầu danh sách
void Push(struct Node** head, int data){
    struct Node* newNode = makeNode(data);
    //nếu không tạo được node thì return
    if (!newNode) return;
    // Nếu node head == NULL thì ta gán node hiện tại là head mà không cần nối
    if (*head == NULL){
        (*head) = newNode;
        return;
    }
    // Ta cần nối prev của head với newNode và next của newNode với head
    (*head)->prev = newNode;
    newNode->next = (*head);
    (*head) = newNode;
    return;
}

void insertLast(struct Node* head, int data){
    struct Node* newNode = makeNode(data);
    // nếu không tạo được node hoặc head == NULL thì sẽ return
    if (!newNode || !head) return;
    struct Node* tmp = head;
    while (tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = newNode;
    newNode->prev = tmp;
    return;
}

void reverse(struct Node** head){
    struct Node* tmp = NULL;
    struct Node* cur = *head;

    while (cur != NULL){
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }
    if (tmp != NULL){
        *head = tmp->prev;
    }
    return;
}

// Đây là hàm để on các phần tử trong danh sách ra màn hình
void Print(struct Node* head){
    if (!head) return;
    struct Node* tmp = head;

    while(tmp != NULL){
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}

void removeData(struct Node** head, int data){
    if (*head == NULL) return;

    struct Node* tmp = (*head);

    if ((*head)->data == data){
        (*head) = tmp->next;

        if ((*head) != NULL) (*head)->prev = NULL;
            
        free(tmp);
        return;
    }

    while(tmp != NULL){
        if (tmp->data == data) break;
        tmp = tmp->next;
    }
    if (tmp == NULL) return;
    if (tmp->prev != NULL) {
        tmp->prev->next = tmp->next;
    }
    if (tmp->next != NULL){
        tmp->next->prev = tmp->prev;
    }
    free(tmp);
}

int main(){
    struct Node* head = makeNode(0);
    
    insertLast(head, 1);
    insertLast(head, 2);
    insertLast(head, 3);
    
    Print(head);
    
    removeData(&head, 3);
    removeData(&head, 2);
    
    Print(head);

    return 0;
}