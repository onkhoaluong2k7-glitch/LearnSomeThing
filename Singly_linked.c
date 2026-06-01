#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node *next;
};

// Hàm duyệt phần tử có thể để in kết quả ra màn hình, hoặc đếm số phần tử
// Giả sử đây là hàm để in các phần tử ra màn hình
// Bạn có thể thay thao tác in phần tử bằng một thao tác nào đó như là đếm phần tử
void Print(struct Node *head){
    // Kiểm tra xem node head có rỗng không
    if (head == NULL) return;

    struct Node* tmp = head;
    while(tmp != NULL){
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
    return;
}

// Hàm tìm kiếm một giá trị nào đó có trong danh sách liên kết đơn hay không
// và trả về Node đó.
struct Node* find(struct Node* head, int data){
    // Kiểm trả xem node head có rỗng không nếu có sẽ trả về NULL
    if (head == NULL) return head;

    struct Node* tmp = head;
    while (tmp != NULL){
        // Nếu tìm thấy sẽ trả về node đó ngay lập tức
        if (tmp->data == data) return tmp;
        tmp = tmp->next;
    }

    // Nếu không tìm thấy ta sẽ trả về NULL
    return NULL;
}


// Hàm này để tạo ra một node mới với một giá trị data cho trước
struct Node* makeNode(int data){
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode){
        printf("Loi cap phat bo nho!!");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hàm chèn phần tử vào cuối danh sách
void insertLast(struct Node* head, int data){
    struct Node* newNode = makeNode(data);
    struct Node* tmp = head;

    if (head == NULL) return;

    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = newNode;
    return;
}

// Hàm chèn vào sau phần tử prev_node
void insertAfter(struct Node* prev_node, int data){
    struct Node* newNode = makeNode(data);
    newNode->next = prev_node->next;
    prev_node->next = newNode;
    return;
}

// Hàm chèn vào đầu danh sách
void push(struct Node** head, int data){
    struct Node* newNode = makeNode(data);

    newNode->next = (*head);
    (*head) = newNode;
    return;
}

// Hàm xóa 1 phần tử đầu tiên có giá trị là data
void remove_data(struct Node** head, int data){
    if (*head == NULL) return;

    struct Node* tmp = *head;
   
    if (tmp->data == data){
        (*head) = (*head)->next;
        free(tmp);
        return;
    }
    struct Node* prev = NULL;
    while(tmp != NULL){
        if (tmp->data == data){
            prev->next = tmp->next;
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }

    return;
}
int main(){
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    // Tạo ra 3 ô trong bộ nhớ để lưu các node 
    head = (struct Node*)malloc(sizeof(struct Node));
    second = (struct Node*)malloc(sizeof(struct Node));
    third = (struct Node*)malloc(sizeof(struct Node));
    
    //Gán giá trị cho node Head = 1 và nối với node second
    head->data = 1;
    head->next = second;

    // Gán giá trị cho node Second = 2 và nối với node Third;
    second->data = 2;
    second->next = third;

    // Gán giá trị cho node third = 3 nối node third với NULL
    third->data = 3;
    third->next = NULL;

    insertLast(head, 4);
    push(&head, 0);
    insertLast(head, 5);

    Print(head);

    remove_data(&head, 5);
    remove_data(&head, 4);

    Print(head);

    return 0;
}