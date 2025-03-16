#include "list.h"

Nobe* creat()
{
	Nobe* head = NULL;
	return head;
}
void add(Nobe** head, int data)
{
	Nobe* newnobe = (Nobe*)malloc(sizeof(Nobe));
	if (newnobe == NULL)
	{
		printf("failed!");
	}
	newnobe->data = data;
	newnobe->next = NULL;
	if (*head == NULL)
	{
		*head = newnobe;
	}
	else
	{
		Nobe* current = *head;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newnobe;
	}
}
void printlist(Nobe* head)
{
	while (head != NULL)
	{
		printf("%d", head->data);
		printf("->");
		head = head->next;
	}
	printf("NULL");
}
DuNobe* ducreat()
{
	DuNobe* head = NULL;
	return head;
}
void insert(DuNobe** head, int data)
{
	DuNobe* newnobe = (DuNobe*)malloc(sizeof(DuNobe));
	if (newnobe == NULL)
	{
		printf("failed!");
	}
	newnobe->next = NULL;
	newnobe->prev = NULL;
	newnobe->data = data;
	if (*head == NULL)
	{
		*head = newnobe;
	}
	else {
		DuNobe* current = *head;
		while (current->next!= NULL)
		{
			current = current->next;
		}
		current->next = newnobe;
		newnobe->prev = current;
	}
}
void printforward(DuNobe* head)
{
	DuNobe* current = head;
	printf("forward;");
	while (current != NULL)
	{
		printf("%d", current->data);
		printf("->");
		current = current->next;
	}
	printf("NULL");
}
void printbackward(DuNobe* head)
{
	DuNobe* current = head;
	printf("backward;");
	while (current != NULL)
	{
		current = current->next;
	}
	current = current->prev;
	while (current != NULL)
	{
		printf("%d", current->data);
		printf("->");
		current = current->prev;
	}
	printf("NULL");

}