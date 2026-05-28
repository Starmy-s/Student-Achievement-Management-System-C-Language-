/**
 * @brief 学生成绩管理系统的核心数据结构定义
 * @date 2026-05-26
 */

#ifndef STUDENT_H
#define STUDENT_H

#define MAX_ID_LEN   20
#define MAX_NAME_LEN 50

/*
* @brief 学科枚举类型
* @field CHINESE 语文
* @field MATH 数学
* @field ENGLIFH 英语
* @field SUBJECT_COUNT 科目数量
*/
enum Subjects {
	CHINESE = 0,
	MATH,
	ENGLISH,
	SUBJECT_COUNT
};

/*
* @brief 学生信息结构体
* @field id 学号
* @field name 姓名
* @field score 成绩数组，包含3门课程的成绩
*/
typedef struct {
	char id[MAX_ID_LEN];
	char name[MAX_NAME_LEN];
	int score[SUBJECT_COUNT];
	
} Student;


/*
* @brief 学生信息双向链表节点结构体
* @field data 学生信息结构体
* @field prev 前驱节点
* @field next后继节点
*/
typedef struct StudentNode {
	Student data;
	struct StudentNode* prev;
	struct StudentNode* next;
} StudentNode;

#endif