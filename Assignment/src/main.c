#include "student.h"




void create() {
	FILE* fp = fopen("students.dat", "rb");
	if (fp == NULL) {
		printf("No data file found. Please create new data.\n");
		return;
	}

	if (head != tail) {
		printf("Data already exists. You couldn't init it again\n");
		fclose(fp);
		return;
	}

	while (1) {
		Student* new_student = (Student*)malloc(sizeof(Student));
		if (fread(new_student, sizeof(Student), 1, fp) != 1) {
			free(new_student);
			break;
		}
		
		new_student->next = NULL;


		printf("学号:%d\n", new_student->num);
		printf("姓名:%s\n", new_student->name);
		for (int i = 0; i < 3; i++) {
			printf("科目[%d]:%d\n", i + 1, new_student->score[i]);
		}

		tail->next = new_student;
		tail = new_student;
	}
	fclose(fp);
}

void add() {
	do {
		Student* new_student = (Student*)malloc(sizeof(Student));
		printf("学号:");
		scanf_s("%d", &new_student->num);
		printf("姓名:");
		scanf_s(" %[^\n]s", new_student->name, 20);
		for (int i = 0; i < 3; i++) {
			printf("科目[%d]:", i + 1);
			scanf_s("%d", &new_student->score[i]);
		}
		new_student->next = NULL;
		tail->next = new_student;
		tail = new_student;
		printf("是否继续添加数据？(y/n)");
		getchar();
	} while ( getchar() == 'y');

}

void del() {

}

void find() {

}

void put() {

}

void get() {

}

void read() {

}

void my_exit() {
	char choice;
	printf("是否需要是否需要将数据导入文件");
	scanf_s(" %c", &choice);
	if(choice == 'y') {
		FILE* fp = fopen("students.dat", "wb");
		if (fp == NULL) {
			printf("无法打开文件进行保存！\n");
			return;
		}
		Student* current_student = head->next;
		while (current_student != NULL) {
			fwrite(current_student, sizeof(Student), 1, fp);
			current_student = current_student->next;
		}
		fclose(fp);
		printf("数据已成功保存到文件！\n");
	}
	exit(0);
}

/*
* 打印主菜单
* 将全局变量修改为参数传递
*/
void print_menu(int *operation_id)
{
	// 情况
	system("cls");
	printf("========================================\n");
	printf("       学生成绩管理信息系统 v1.0        \n");
	printf("========================================\n");
	printf("  [1] 初始化数据    [5] 导出数据        \n");
	printf("  [2] 新增数据      [6] 导入数据        \n");
	printf("  [3] 删除数据      [7] 浏览数据        \n");
	printf("  [4] 查找数据      [0] 退出系统        \n");
	printf("========================================\n");
	printf(" 清选择你要使用的功能 [0-7]: ");
	scanf_s("%d", &operation_id);
}

void mainpage()
{
	print();
	switch (operation_id)
	{
	case 1:create(); mainpage(); break;
	case 2:add(); mainpage(); break;
	case 3:del(); mainpage(); break;
	case 4:find(); mainpage(); break;
	case 5:put(); mainpage(); break;
	case 6:get(); mainpage(); break;
	case 7:read(); mainpage(); break;
	case 0:my_exit(); mainpage(); break;
	default:printf("Error select!!Input again.....\n"); mainpage();
	}
}


int main() {
	Student* head, * tail;
	int operation_id;

	head = (Student*)malloc(sizeof(Student));
	head->next = NULL;
	tail = head;

	mainpage();
	return 0;
}