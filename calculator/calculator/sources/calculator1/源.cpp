
#pragma once
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_INPUT 50  // 输入缓冲区大小

/* 链式栈节点定义 */
typedef struct StackNode {
    char data;
    struct StackNode* next;
} StackNode;

/* 链栈结构 */
typedef struct {
    StackNode* top;   // 栈顶指针
} LinkStack;


// 初始化栈
void init(LinkStack* s) {
    s->top = NULL;
}

// 判空
bool empty(LinkStack* s) {
    return s->top == NULL;
}

// 压栈
bool push(LinkStack* s, char x) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        printf("内存分配失败！");
        return false;
    }
    newNode->data = x;
    newNode->next = s->top;
    s->top = newNode;
    return true;
}

// 弹栈
bool pop(LinkStack* s, char* x) {
    if (empty(s)) {
        printf("栈下溢！");
        return false;
    }
    StackNode* delNode = s->top;
    *x = delNode->data;
    s->top = delNode->next;
    free(delNode);
    return true;
}

// 获取栈顶元素（不弹栈）
char getTop(LinkStack* s) {
    return empty(s) ? '\0' : s->top->data;
}


// 比较运算符优先级
bool compare(LinkStack* s, char x) {
    if (empty(s)) return true;
    char top_op = getTop(s);
    return ((x == '*' || x == '/') &&
        (top_op == '+' || top_op == '-'));
}

// 打印结果
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
    printf("请输入算式:");

    
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
            pop(&s, &temp); // 弹出左括号
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

    // 弹出剩余运算符
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