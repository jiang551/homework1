#include "list.h"

int main()
{
    int input;
    while (1)
    {
        printf("1. ����˫������\n2. ������������\n0. �˳�����\n�����룺"); // �˵���ѡ����ʲô������˳�
        if (scanf("%d", &input) != 1) // ��������Ƿ�Ϊ����
        {
            printf("����Ƿ������������룡\n");
            // ������뻺����
            while (getchar() != '\n');
            continue;
        }
        if (input != 1 && input != 2 && input != 0) // �ж����������Ƿ�Ϸ�
        {
            printf("����ȷ������ţ�\n");
            continue;
        }
        if (input == 0)
        {
            printf("�����˳���\n");
            return 0; // �����˳�����
        }
        break;
    }

    if (input == 2) // ���봴������������Ӳ˵�
    {
        Nobe* head = creat(); // ��������ͷ
        while (1)
        {
            int newData;
            printf("\n1. �������\n2. ��ӡ����\n3. �˳�\n�����룺");
            if (scanf("%d", &input) != 1)
            {
                printf("����Ƿ������������룡\n");
                while (getchar() != '\n');
                continue;
            }
            if (input == 3)
            {
                // �ͷ������ڴ棨��Ҫʵ���ͷź�����
                break;
            }
            switch (input)
            {
            case 1: // �������
                printf("������Ҫ��ӵ����ݣ�");
                if (scanf("%d", &newData) != 1)
                {
                    printf("����Ƿ������������룡\n");
                    while (getchar() != '\n');
                    break;
                }
                add(&head, newData);
                break;
            case 2: // ��ӡ����
                printlist(head);
                break;
            }
        }
    }
    else if (input == 1) // ���봴��˫��������Ӳ˵�
    {
        DuNobe* head1 = ducreat();
        while (1)
        {
            int newData;
            printf("\n1. �������\n2. �����ӡ����\n3. �����ӡ����\n4. �˳�\n�����룺");
            if (scanf("%d", &input) != 1)
            {
                printf("����Ƿ������������룡\n");
                while (getchar() != '\n');
                continue;
            }
            if (input == 4)
            {
                // �ͷ������ڴ棨��Ҫʵ���ͷź�����
                break;
            }
            switch (input)
            {
            case 1: // �������
                printf("������Ҫ��ӵ����ݣ�");
                if (scanf("%d", &newData) != 1)
                {
                    printf("����Ƿ������������룡\n");
                    while (getchar() != '\n');
                    break;
                }
                insert(&head1, newData);
                break;
            case 2: // �����ӡ����
                printforward(head1);
                break;
            case 3: // �����ӡ����
                printbackward(head1);
                break;
            }
        }
    }
    return 0;
}