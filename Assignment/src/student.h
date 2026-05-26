#ifndef STUDENT_H
#define STUDENT_H


#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct Student {
	int num;
	char name[20];
	int score[3];
	struct Student* next;
} Student;

#endif