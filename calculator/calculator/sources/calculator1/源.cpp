
#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_INPUT 50  // ���뻺������С

/* ��ʽջ�ڵ㶨�� */
typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

/* ��ջ�ṹ */
typedef struct {
    StackNode* top;   // ջ��ָ��
} LinkStack;


// ��ʼ��ջ
void init(LinkStack* s) {
    s->top = NULL;
}

// �п�
bool empty(LinkStack* s) {
    return s->top == NULL;
}

// ѹջ
bool push(LinkStack* s, char x) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("�ڴ����ʧ�ܣ�");
        return false;
    }
    newNode->data = x;
    newNode->next = s->top;
    s->top = newNode;
    return true;
}

// ��ջ
bool pop(LinkStack* s, char* x) {
    if (empty(s)) {
        printf("ջ���磡");
        return false;
    }
    StackNode* delNode = s->top;
    *x = delNode->data;
    s->top = delNode->next;
    free(delNode);
    return true;
}

// ��ȡջ��Ԫ�أ�����ջ��
char getTop(LinkStack* s) {
    return empty(s) ? '\0' : s->top->data;
}


// �Ƚ���������ȼ�
bool compare(LinkStack* s, char x) {
    if (empty(s)) return true;
    char top_op = getTop(s);
    return ((x == '*' || x == '/') &&
        (top_op == '+' || top_op == '-'));
}

// ��ӡ���
void print(LinkStack* s) {
    StackNode* p = s->top;
    while (p) {
        printf("%d\n", p->data - '0');
        p = p->next;
    }
}

int main(void) {
    char user[MAX_INPUT] = { 0 };
    int i = 0;
    char c;

    LinkStack s;   
    init(&s);
    printf("��������ʽ:");

    
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            user[i++] = c;
        }
        else if (c == ')') {
            char temp;
            while (getTop(&s) != '(') {
                pop(&s, &temp);
                user[i++] = temp;
            }
            pop(&s, &temp); // ����������
        }
        else if (c == '(') {
            push(&s, c);
        }
        else if (strchr("+-*/", c)) {
            while (!empty(&s) && !compare(&s, c) &&
                getTop(&s) != '(') {
                char op;
                pop(&s, &op);
                user[i++] = op;
            }
            push(&s, c);
        }
    }

    // ����ʣ�������
    while (!empty(&s)) {
        char op;
        pop(&s, &op);
        user[i++] = op;
    }

   
    LinkStack calc_stack;
    init(&calc_stack);

    for (int j = 0; j < i; j++) {
        if (user[j] >= '0' && user[j] <= '9') {
            push(&calc_stack, user[j]);
        }
        else {
            char a, b;
            pop(&calc_stack, &a);
            pop(&calc_stack, &b);

         
            switch (user[j]) {
            case '+': push(&calc_stack, (b - '0') + (a - '0') + '0'); break;
            case '-': push(&calc_stack, (b - '0') - (a - '0') + '0'); break;
            case '*': push(&calc_stack, (b - '0') * (a - '0') + '0'); break;
            case '/': push(&calc_stack, (b - '0') / (a - '0') + '0'); break;
            }
        }
    }

    print(&calc_stack);
    system("pause");
}