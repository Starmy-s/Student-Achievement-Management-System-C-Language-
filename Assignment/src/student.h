/**
 * @brief 学生成绩管理系统的核心数据结构定义
 * @date 2026-05-26
 */

#ifndef STUDENT_H
#define STUDENT_H

/*
* @brief 学生信息结构体
* @field num 学号
* @field name 姓名
* @field score 成绩数组，包含3门课程的成绩
*/
typedef struct Student {
	int num;
	char name[20];
	int score[3];
	struct Student* next;
} Student;

#endif