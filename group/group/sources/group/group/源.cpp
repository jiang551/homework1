#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 队列节点结构
typedef struct Node {
    void* data;         // 泛型数据指针
    struct Node* next;  // 指向下一个节点
} Node;

// 队列结构
typedef struct {
    Node* front;    // 队头指针
    Node* rear;     // 队尾指针
    int size;       // 队列元素个数
} GenericQueue;

// 初始化队列
GenericQueue* createQueue() {
    GenericQueue* queue = (GenericQueue*)malloc(sizeof(GenericQueue));
    if (!queue) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

// 检查队列是否为空
int isEmpty(GenericQueue* queue) {
    return queue->size == 0;
}

// 获取队列元素个数
int getSize(GenericQueue* queue) {
    return queue->size;
}

// 入队操作
void enqueue(GenericQueue* queue, void* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->size++;
}

// 出队操作
void* dequeue(GenericQueue* queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Queue is empty!\n");
        return NULL;
    }

    Node* temp = queue->front;
    void* data = temp->data;

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    queue->size--;
    return data;
}

// 销毁队列  
void destroyQueue(GenericQueue* queue) {
    while (!isEmpty(queue)) {
        void* data = dequeue(queue);
    }
    free(queue);
}


int main() {
    // 创建存储整型的队列
    GenericQueue* intQueue = createQueue();

    // 入队10个整数
    printf("Enqueue: ");
    for (int i = 0; i < 10; i++) {
        int* num =(int*)malloc(sizeof(int));  // 必须动态分配内存
        *num = i;
        enqueue(intQueue, num);
        printf("%d ", *num);
    }

    // 出队并打印
    printf("\nDequeue: ");
    while (!isEmpty(intQueue)) {
        int* num = (int*)dequeue(intQueue);
        printf("%d ", *num);
        free(num);  // 释放动态分配的内存
    }
    printf("\n");

    destroyQueue(intQueue);

    // 创建存储结构体的队列
    typedef struct {
        char name[20];
        int age;
    } Person;

    GenericQueue* personQueue = createQueue();

    // 入队人员信息
    Person p1 = { "le", 18 };
    Person p2 = { "mi", 20 };

    enqueue(personQueue, &p1);
    enqueue(personQueue, &p2);

    // 出队并打印
    printf("\nstuden Queue:\n");
    while (!isEmpty(personQueue)) {
        Person* p = (Person*)dequeue(personQueue);
        printf("Name: %s, Age: %d\n", p->name, p->age);
    }

    destroyQueue(personQueue);
    system("pause");
    return 0;
}