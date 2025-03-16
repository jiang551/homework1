#pragma once
# define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
typedef struct Nobe
{
	int data;
	Nobe* next;
}Nobe;
typedef struct DuNobe
{
	int data;
	DuNobe* next;
	DuNobe* prev;
} DuNobe;
Nobe* creat();
void add(Nobe** head, int data);
void printlist(Nobe* head);
DuNobe* ducreat();
void insert(DuNobe** head, int data);
void printforward(DuNobe* head);
void printbackward(DuNobe* head);