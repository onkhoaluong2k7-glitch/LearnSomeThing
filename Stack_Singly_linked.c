/*
 Đây là cấu trúc đơn giản của một stack, ở đây mình dùng cấu trúc 
singly_linked để mô phỏng cấu trúc của dữ liệu này. Đây chỉ là phần 
cơ bản nên chỉ có một vài thao tác mà cấu trúc này có, bạn muốn xem 
thêm vui lòng vào các trang web để xem
*/
#include<stdio.h>
#include<stdlib.h>

// Định nghĩa Node của Stack
typedef struct Node{
    int data;
    struct Node* next;
} Node;

// Khởi tạo
typedef struct {
    Node* top;
    int size;
} Stack;

// Khởi tạo danh sách rỗng
void init(Stack* st){
    st->top = NULL;
    st->size = 0;
}

// Kiểm tra xem stack có rỗng không
int isEmpty(Stack* st){
    return st->top == NULL;
}

// Thêm phần tử vào stack
void push(Stack* st, int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode){
        printf("Khong du bo nho!!");
        return;
    }
    newNode->data = data;
    newNode->next = st->top;
    st->top = newNode;
    st->size ++;
}

// Xóa phần tử đầu Stack đi
int pop(Stack* st, int* val){
    if (isEmpty(st)){
        printf("Stack rong!!\n");
        return 0;
    }
    *val = st->top->data;
    Node* temp = st->top;
    st->top = st->top->next;
    free(temp);
    st->size--;
    return 1;
}

// Lấy phần từ đầu Stack mà không xóa
int peek(Stack* st, int* val){
     if (isEmpty(st)){
        printf("Stack rong!!\n");
        return 0;
    }
    *val = st->top->data;
    return 1;
}
int main(){ 
    Stack s;
    init(&s);
    
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    int x;
    peek(&s, &x);
    printf("Phan tu tren cung la: %d\n", x);

    while(!isEmpty(&s)){
        pop(&s, &x);
        printf("Lay phan tu %d ra\n", x);
    }
    
    return 0;
}