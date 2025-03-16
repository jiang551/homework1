#include "list.h"

int main()
{
    int input;
    while (1)
    {
        printf("1. 建立双向链表\n2. 建立单向链表\n0. 退出程序\n请输入："); // 菜单，选择建立什么链表或退出
        if (scanf("%d", &input) != 1) // 检查输入是否为整数
        {
            printf("输入非法，请重新输入！\n");
            // 清空输入缓冲区
            while (getchar() != '\n');
            continue;
        }
        if (input != 1 && input != 2 && input != 0) // 判断输入数字是否合法
        {
            printf("请正确输入序号！\n");
            continue;
        }
        if (input == 0)
        {
            printf("程序退出。\n");
            return 0; // 正常退出程序
        }
        break;
    }

    if (input == 2) // 进入创建单向链表的子菜单
    {
        Nobe* head = creat(); // 建立链表头
        while (1)
        {
            int newData;
            printf("\n1. 添加链表\n2. 打印链表\n3. 退出\n请输入：");
            if (scanf("%d", &input) != 1)
            {
                printf("输入非法，请重新输入！\n");
                while (getchar() != '\n');
                continue;
            }
            if (input == 3)
            {
                // 释放链表内存（需要实现释放函数）
                break;
            }
            switch (input)
            {
            case 1: // 添加链表
                printf("请输入要添加的数据：");
                if (scanf("%d", &newData) != 1)
                {
                    printf("输入非法，请重新输入！\n");
                    while (getchar() != '\n');
                    break;
                }
                add(&head, newData);
                break;
            case 2: // 打印链表
                printlist(head);
                break;
            }
        }
    }
    else if (input == 1) // 进入创建双向链表的子菜单
    {
        DuNobe* head1 = ducreat();
        while (1)
        {
            int newData;
            printf("\n1. 添加链表\n2. 正向打印链表\n3. 反向打印链表\n4. 退出\n请输入：");
            if (scanf("%d", &input) != 1)
            {
                printf("输入非法，请重新输入！\n");
                while (getchar() != '\n');
                continue;
            }
            if (input == 4)
            {
                // 释放链表内存（需要实现释放函数）
                break;
            }
            switch (input)
            {
            case 1: // 添加链表
                printf("请输入要添加的数据：");
                if (scanf("%d", &newData) != 1)
                {
                    printf("输入非法，请重新输入！\n");
                    while (getchar() != '\n');
                    break;
                }
                insert(&head1, newData);
                break;
            case 2: // 正向打印链表
                printforward(head1);
                break;
            case 3: // 反向打印链表
                printbackward(head1);
                break;
            }
        }
    }
    return 0;
}