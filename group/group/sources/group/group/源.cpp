#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// ���нڵ�ṹ
typedef struct Node {
    void* data;         // ��������ָ��
    struct Node* next;  // ָ����һ���ڵ�
} Node;

// ���нṹ
typedef struct {
    Node* front;    // ��ͷָ��
    Node* rear;     // ��βָ��
    int size;       // ����Ԫ�ظ���
} GenericQueue;

// ��ʼ������
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

// �������Ƿ�Ϊ��
int isEmpty(GenericQueue* queue) {
    return queue->size == 0;
}

// ��ȡ����Ԫ�ظ���
int getSize(GenericQueue* queue) {
    return queue->size;
}

// ��Ӳ���
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

// ���Ӳ���
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

// ���ٶ���  
void destroyQueue(GenericQueue* queue) {
    while (!isEmpty(queue)) {
        void* data = dequeue(queue);
    }
    free(queue);
}


int main() {
    // �����洢���͵Ķ���
    GenericQueue* intQueue = createQueue();

    // ���10������
    printf("Enqueue: ");
    for (int i = 0; i < 10; i++) {
        int* num =(int*)malloc(sizeof(int));  // ���붯̬�����ڴ�
        *num = i;
        enqueue(intQueue, num);
        printf("%d ", *num);
    }

    // ���Ӳ���ӡ
    printf("\nDequeue: ");
    while (!isEmpty(intQueue)) {
        int* num = (int*)dequeue(intQueue);
        printf("%d ", *num);
        free(num);  // �ͷŶ�̬������ڴ�
    }
    printf("\n");

    destroyQueue(intQueue);

    // �����洢�ṹ��Ķ���
    typedef struct {
        char name[20];
        int age;
    } Person;

    GenericQueue* personQueue = createQueue();

    // �����Ա��Ϣ
    Person p1 = { "le", 18 };
    Person p2 = { "mi", 20 };

    enqueue(personQueue, &p1);
    enqueue(personQueue, &p2);

    // ���Ӳ���ӡ
    printf("\nstuden Queue:\n");
    while (!isEmpty(personQueue)) {
        Person* p = (Person*)dequeue(personQueue);
        printf("Name: %s, Age: %d\n", p->name, p->age);
    }

    destroyQueue(personQueue);
    system("pause");
    return 0;
}