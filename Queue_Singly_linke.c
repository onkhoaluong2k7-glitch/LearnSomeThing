/*Đây là cấu trúc của queue một cách cơ bản nhất, mình chỉ viết một vài 
thao tác cơ bản để mô tả cấu trúc này, bạn có thể tìm hiểu kỹ hơn cấu trúc
này trên wiki, hoặc các trang học thuật liên quan. Ở đây mình dùng cấu trúc
danh sách liên kết để viết lên cấu trúc queue này nên có thể tham khảo, ngoài
ra để biểu diễn queue ta còn có thể dùng mảng.*/

#include <stdio.h>
#include <stdlib.h>

// cấu trúc node của queue
typedef struct Node{
    int data;
    struct Node* next;
} Node;

// Queue quản lý bằng 2 con trỏ: front và rear 
typedef struct{
    Node* front;
    Node* rear;
}  Queue;

// Khởi tạo Queue rỗng
void init(Queue* q){
    q->front = q->rear = NULL;
}

// Kiểm tra xem Queue có rỗng không
int isEmpty(Queue* q){
    return q->front == NULL;
}

// thêm phần tử vào Queue
void enQueue(Queue* q, int val){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode){
        printf("Cap phat loi!!");
        return;
    }
    newNode->data = val;
    newNode->next = NULL;

    if (q->rear == NULL){
        q->front = q->rear = newNode;
    } else{
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

//Lấy phần tử ra khỏi queue
int deQueue(Queue* q){
    if (q->front == NULL){
        printf("Queue rong !!!\n");
        return -1;
    }
    Node* temp = q->front;
    q->front = q->front->next;

    if(q->front == NULL){
        q->rear = NULL;
    }
    int val = temp->data;
    free(temp);
    return val;
}

void Print(Queue* q){
    if (q->front == NULL){
        printf("Queue rong!!!\n");
        return;
    }
    Node* temp = q->front;
    printf("Queue hien tai co:\n");
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    Queue q;
    init(&q);

    enQueue(&q, 1);
    enQueue(&q, 2);
    enQueue(&q, 3);
    Print(&q);

    printf("Lay %d ra\n", deQueue(&q));
    Print(&q);
    

    return 0;
}