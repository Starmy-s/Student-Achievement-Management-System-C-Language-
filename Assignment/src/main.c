/**
 * @brief 学生成绩管理系统的主程序入口
 * @details 
 * @date 2026-05-26
 */

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "student.h"

Student* head, * tail;


/**
 * @brief 清除输入流残留数据
 */
void clear_buffer() {
	int c;
	// TODO: 如果缓冲区什么都没有，还得手动打一个回车
	while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief 输出学生信息的函数
 * @param student 要输出的学生信息指针，使用前检查student是否为NULL
 */
void print_student(const Student* student) {
	printf("学号:%d\n", student->num);
	printf("姓名:%s\n", student->name);
	for (int i = 0; i < 3; i++) {
		printf("科目[%d]:%d\n", i + 1, student->score[i]);
	}
}


/**
 * @brief 读取整数输入的函数，确保用户输入的是一个有效的整数
 * @param prompt 提示用户输入的字符串
 * @return 读取到的整数值
 * @note 如果用户输入无效，会提示重新输入，直到输入一个有效的整数为止
 */
int get_int(const char* prompt, int min, int max) {
	// TODO: 输入的是小数怎么办
	int value;
	while (1) {
		printf(prompt); 
		if (scanf("%d", &value) == 1) {
			clear_buffer();
			if (value < min) {
				fprintf(stderr, "输入的数至少为%d\n", min);
				continue;
			}
			else if (value > max) {
				fprintf(stderr, "输入的数最大为%d\n", max);
				continue;
			}
			return value;
		}
		fprintf(stderr, "请输入一个整数\n");
		clear_buffer();
	}
}


/**
 * @brief 输入学生信息的函数
 * @param student 要输入的学生信息指针，使用前检查student是否为NULL
 */
void input_student(Student* student) {

	student->num = get_int("学号:", 0, INT_MAX);

	printf("姓名:");
	if (scanf("%19s", student->name) == 1) {
		clear_buffer();
	}
	else {
		printf("读取姓名失败，清重试！\n");
		clear_buffer();
		return;
	}

	for (int i = 0; i < 3; i++) {
		char prompt[20] = {0};
		sprintf(prompt, "科目[%d]:", i + 1);
		student->score[i] = get_int(prompt, 0, 100);
	}
}


/**
 * @brief 链表尾后添加结点
 * @param student 要添加的学生信息指针，使用前检查student是否为NULL
 */
void append_student(Student* student){
	student->next = NULL;
	tail->next = student;
	tail = student;
}


/**
 * @brief 数据初始化函数
 */
void create() {
	// TODO: 怎么保证不会出现相同的学号
	int student_count = get_int("输入学生的个数：", 0, INT_MAX);
	for(int i = 0; i < student_count; i++) {
		Student* current_student = (Student*)malloc(sizeof(Student));
		if (current_student == NULL) {
			printf("内存分配失败！\n");
			return;
		}
		input_student(current_student);
		append_student(current_student);
	}
}


/**
 * @brief 添加学生数据的函数，用户输入学生信息并将其添加到链表末尾
 */
void add() {
	char choice;
	do {
		Student* current_student = (Student*)malloc(sizeof(Student));
		if (current_student == NULL) {
			printf("内存分配失败！\n");
			return;
		}
		input_student(current_student);
		append_student(current_student);
		printf("是否继续添加数据？(y/n)");
		if (scanf("%c", &choice) == 1) {
			clear_buffer();
		}
		else {
			printf("输入无效，清重试！\n");
			clear_buffer();
			return;
		}
	} while (choice == 'y' || choice == 'Y');
}

/*
* @brief 按照学号查找学生信息的函数，用户输入学号，找到对应学生并显示其信息
*/
void find_student_by_num() {
	char choice;
	do {
		int num = get_int("请输入要查找的学号：", 0, INT_MAX);
		int is_find_num = 0;
		Student* current_student = head->next;
		while (current_student != NULL) {
			if (current_student->num == num) {
				is_find_num = 1;
				print_student(current_student);
				break;
			}
			current_student = current_student->next;
		}
		if (is_find_num == 0) {
			printf("没有这个学号的学生！\n");
		}
		printf("你想继续查找数据吗？<是-y>:");
		if (scanf("%c", &choice) == 1) {
			clear_buffer();
		}
		else {
			printf("输入无效，清重试！\n");
			clear_buffer();
			return;
		}
	} while (choice == 'y' || choice == 'Y');
}

/*
* @brief 按照姓名查找学生信息的函数，用户输入姓名，找到对应学生并显示其信息，注意可能存在同名学生
*/
void find_student_by_name() {
	char choice;
	do {
		char name[20] = {0};
		printf("请输入要查找的姓名:");
		if (scanf("%19s", name) == 1) {
			clear_buffer();
		}
		else {
			printf("读取姓名失败，清重试！\n");
			clear_buffer();
			return;
		}
		Student* current_student = head->next;
		int find_count = 0;
		while (current_student != NULL) {
			if (strcmp(current_student->name, name) == 0) {
				print_student(current_student);
				find_count++;
			}
			current_student = current_student->next;
		}
		if (find_count == 0) {
			printf("没有这个姓名的学生！\n");
		}
		printf("你想继续查找数据吗？<是-y>:");
		if (scanf("%c", &choice) == 1) {
			clear_buffer();
		}
		else {
			printf("输入无效，清重试！\n");
			clear_buffer();
			return;
		}
	} while (choice == 'y' || choice == 'Y');
}

// TODO: 可以考虑用双向链表优化
/**
 * @brief 按照学号删除学生信息的函数，用户输入学号，找到对应学生并从链表中删除
 */
void del_by_num() {
	char choice;
	do {
		if (head == tail) {
			printf("链表为空，不能删除数据。\n");
			printf("请先使用初始化功能、新增数据功能或导入数据功能！\n");
			return;
		}
		int num = get_int("请输入要删除的学号：", 0, INT_MAX);
		int has_del = 0;
		Student* current_student = head->next, * prev_student = head;
		while (current_student != NULL) {
			if (current_student->num == num) {
				prev_student->next = current_student->next;
				if (current_student == tail) {
					tail = prev_student;
				}
				free(current_student);
				has_del = 1;
				break;
			}
			prev_student = current_student;
			current_student = current_student->next;
		}
		if (!has_del) {
			printf("没有这个学号的学生！\n");
		}
		printf("你想继续删除数据吗？<是-y>:");
		if (scanf("%c", &choice) == 1) {
			clear_buffer();
		}
		else {
			printf("输入无效，清重试！\n");
			clear_buffer();
			return;
		}
	} while (choice == 'y' || choice == 'Y');

}

/**
 * @brief 按名字删除学生信息的函数，用户输入姓名，找到对应学生并从链表中删除，注意可能存在同名学生
 */
void del_by_name() {
	char choice;
	do {
		// 因为一直在删除，所有每次都得检查
		if (head == tail) {
			printf("链表为空，不能删除数据。\n");
			printf("请先使用初始化功能、新增数据功能或导入数据功能！\n");
			return;
		}
		char name[20] = { 0 };
		printf("请输入要删除的姓名:");
		if (scanf("%19s", name) == 1) {
			clear_buffer();
		}
		else {
			printf("读取姓名失败，清重试！\n");
			clear_buffer();
			return;
		}
		int del_count = 0;
		Student* current_student = head->next, * prev_student = head;
		while (current_student != NULL) {
			if (strcmp(current_student->name, name) == 0) {
				prev_student->next = current_student->next;
				if (current_student == tail) {
					tail = prev_student;
				}
				free(current_student);
				// 特殊处理一下，只更新current_student，不更新prev_student
				current_student = prev_student->next;
				del_count++;
				continue;
			}
			prev_student = current_student;
			current_student = current_student->next;
		}
		if (del_count == 0) {
			printf("没有这个姓名的学生！\n");
		}
		else {
			printf("本次共删除了%d个学生信息\n", del_count);
		}
		printf("你想继续删除数据吗？<是-y>:");
		if (scanf("%c", &choice) == 1) {
			clear_buffer();
		}
		else {
			printf("输入无效，清重试！\n");
			clear_buffer();
			return;
		}
	} while (choice == 'y' || choice == 'Y');
}

/**
 * @brief 数据删除函数，用户输入学号，找到对应学生并从链表中删除
 */
void del() {
	if(head == tail) {
		printf("链表为空，不能删除数据。\n");
		printf("请先使用初始化功能、新增数据功能或导入数据功能！\n");
		return;
	}
	printf("数据删除 子菜单\n");
	printf(" 1 按学号删除\n");
	printf(" 2 按姓名删除\n");
	printf(" 0 返回系统主菜单\n");
	int choice = get_int("请输入您的选择：", 0, INT_MAX);
	switch (choice)
	{
	case 1:del_by_num(); break;
	case 2:del_by_name(); break;
	case 0:return; break;
	default:printf("不是有效的功能，请重新选择\n");
	}
}


/**
 * @brief 数据查找函数，用户输入学号，找到对应学生并显示其信息
 */
void find() {
	if (head == tail) {
		printf("链表为空，不能查找数据。\n");
		printf("请先使用初始化功能、新增数据功能或导入数据功能！\n");
		return;
	}
	printf("数据查询 子菜单\n");
	printf(" 1 按学号查询\n");
	printf(" 2 按姓名查询\n");
	printf(" 0 返回系统主菜单\n");
	int choice = get_int("请输入您的选择：", 0, INT_MAX);
	switch (choice)
	{
	case 1:find_student_by_num(); break;
	case 2:find_student_by_name(); break;
	case 0:return; break;
	default:printf("不是有效的功能，请重新选择\n");
	}
}

/*
* @brief 清空链表函数，释放链表中所有学生信息的内存，并将链表重置为空状态
*/
void clear_list() {
	Student* current_student = head->next;
	while (current_student != NULL) {
		Student* temp = current_student;
		current_student = current_student->next;
		free(temp);
	}
	head->next = NULL;
	tail = head;
}	

/**
 * @brief 数据导出函数，将链表中的学生数据写入文件保存
 */
void put() {
	if(head == tail){
		printf("链表为空，不需要导出数据！\n");
		return;
	}
	FILE* fp = fopen("students.dat", "wb");
	if (fp == NULL) {
		printf("无法打开文件进行保存！\n");
		return;
	}
	Student* current_student = head->next;
	while (current_student != NULL) {
		// TODO: 最好不要存next指针
		fwrite(current_student, sizeof(Student), 1, fp);
		current_student = current_student->next;
	}
	fclose(fp);
	printf("数据已成功保存到文件！\n");
	clear_list();
}


/**
 * @brief 数据导入函数，从文件中读取学生数据并构建链表，注意避免重复导入
 */
void get() {
	if (head != tail) {
		printf("链表中有数据，导入数据后，原链表中的数据将丢失!\n");
		printf("是否继续导入数据？(是 - y）:");
		char choice;
		if (scanf("%c", &choice) == 1) {
			clear_buffer();
		}
		else {
			printf("输入无效，清重试！\n");
			clear_buffer();
			return;
		}
		if (choice == 'y' || choice == 'Y') {
			clear_list();
		}
		else {
			return;
		}
	}
	FILE* fp = fopen("students.dat", "rb");
	if (fp == NULL) {
		printf("没有找到数据，清先创建数据\n");
		return;
	}

	while (1) {
		Student* current_student = (Student*)malloc(sizeof(Student));
		if(current_student == NULL) {
			printf("内存分配失败！\n");
			fclose(fp);
			return;
		}
		if (fread(current_student, sizeof(Student), 1, fp) != 1) {
			free(current_student);
			break;
		}

		print_student(current_student);
		append_student(current_student);
	}
	fclose(fp);
}


/**
 * @brief 数据浏览函数，显示链表中所有学生的信息
 */
void read() {
	if(head == tail) {
		printf("链表为空，没有数据可以浏览！\n");
		return;
	}
	Student* current_student = head->next;
	while (current_student != NULL) {
		print_student(current_student);
		current_student = current_student->next;
	}
}

/**
 * @brief 退出函数，在退出前询问用户是否需要将数据导入文件，如果需要则将链表中的数据写入文件保存
 */
void my_exit() {
	if (head == tail) {
		exit(0);
	}
	char choice;
	printf("是否需要是否需要将数据导入文件(是 - y）");
	if (scanf("%c", &choice) == 1) {
		clear_buffer();
	}
	else {
		printf("输入无效，清重试！\n");
		clear_buffer();
		return;
	}
	if(choice == 'y' || choice == 'Y') {
		put();
	}
	exit(0);
}

/**
 * @brief 打印主菜单
 * @param choice_ptr 功能选择的变量地址，用户输入后会修改该变量的值
 */
void print_menu(int *choice_ptr)
{
	// 清屏
	system("cls");
	printf("========================================\n");
	printf("       学生成绩管理信息系统 v1.0        \n");
	printf("========================================\n");
	printf("  [1] 初始化数据    [5] 导出数据        \n");
	printf("  [2] 新增数据      [6] 导入数据        \n");
	printf("  [3] 删除数据      [7] 浏览数据        \n");
	printf("  [4] 查找数据      [0] 退出系统        \n");
	printf("========================================\n");
	*choice_ptr = get_int("清选择你要使用的功能 [0-7]:", 0, INT_MAX);
}

/**
 * @brief 主控函数，负责显示菜单并调用对应的功能函数
 */
void mainpage()
{
	while (1) {
		int choice;
		print_menu(&choice);
		switch (choice)
		{
		case 1:create(); break;
		case 2:add(); break;
		case 3:del(); break;
		case 4:find(); break;
		case 5:put(); break;
		case 6:get(); break;
		case 7:read(); break;
		case 0:my_exit(); break;
		default:printf("不是有效的功能，请重新选择\n");
		}
		system("pause");
	}
}

/**
 * @brief 主函数，初始化链表头尾指针，并进入主菜单循环
 */
int main() {
	head = (Student*)malloc(sizeof(Student));
	if(head == NULL) {
		printf("内存分配失败！\n");
		return 1;
	}
	head->next = NULL;
	tail = head;

	mainpage();
	return 0;
}