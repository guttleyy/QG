#define _CRT_SECURE_NO_WARNINGS 1	//解决不能直接使用scanf的问题
#pragma warning(disable:6031)		//解决scanf返回值被忽略的问题
#include "../Headers/LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//初始化链栈
Status initLStack(LinkStack** s) {
	*s = (LinkStack*)malloc(sizeof(LinkStack));
	if (*s == NULL) {
		printf("内存分配失败!\n");
		return ERROR;
	}
	(*s)->count = 0;
	(*s)->top = NULL;
	return SUCCESS;
}

//判断栈是否为空
Status isEmptyLStack(LinkStack* s) {
	if (s == NULL) {
		printf("栈不存在，请先创建!\n");
		return ERROR;
	}
	if (s->top == NULL) {
		printf("栈为空！\n");
		return SUCCESS;
	}
	printf("栈不为空！\n");
	return ERROR;
}

//得到栈顶元素
Status getTopLStack(LinkStack* s, ElemType* e) {
	
	*e = s->top->data;
	return SUCCESS;
}

//清空栈
Status clearLStack(LinkStack* s) {
	LinkStackPtr p1, p2;
	p1 = p2 = s->top;
	while (p1 != NULL) {
		p1 = p1->next;
		free(p2);
		p2 = p1;
	}
	s->top = NULL;
	s->count = 0;
	return SUCCESS;
}

//销毁栈
Status destroyLStack(LinkStack** s) {
	if ((*s) == NULL) {
		printf("栈不存在，请先创建!\n");
		return ERROR;
	}
	clearLStack(*s);
	free(*s);
	(*s) = NULL;
	printf("销毁完成!\n");
	return SUCCESS;
}

//检测栈长度
Status LStackLength(LinkStack* s, int* length) {
	*length = s->count;
	return SUCCESS;
}

//入栈
Status pushLStack(LinkStack* s, ElemType data) {
	LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode));
	if (p == NULL) {
		printf("内存分配失败!\n");
		return ERROR;
	}
	p->data = data;
	p->next = s->top;
	s->top = p;
	s->count++;
	return SUCCESS;
}

//出栈
Status popLStack(LinkStack* s, ElemType* data) {
	StackNode* p = s->top;
	*data = p->data;
	s->top = p->next;
	free(p);
	s->count--;
	return SUCCESS;
}

//主菜单
void menu() {
	printf("|-------------链栈操作菜单---------------|\n");
	printf("|		[1]创建栈		 |\n");
	printf("|		[2]数据入栈		 |\n");
	printf("|		[3]数据出栈		 |\n");
	printf("|		[4]判断栈是否为空	 |\n");
	printf("|		[5]输出栈顶元素		 |\n");
	printf("|		[6]检测栈的长度		 |\n");
	printf("|		[7]清空栈		 |\n");
	printf("|		[8]销毁栈		 |\n");
	printf("|		[9]退出			 |\n");
	printf("|----------------------------------------|\n");
	printf("请输入对应数字：");
}

int main() {
	
	LinkStack* s = NULL;
	int choice;
	int length = 0;
	int count = 0;
	ElemType data = 0;
	ElemType* outData = NULL;

	while (1) {
		system("cls");		//系统清屏
		menu();				//显示菜单
		scanf("%d", &choice);

		//清空缓冲区
		scanf("%*[^\n]");	//丢弃输入行中非数字的部分
		getchar();			//消耗掉换行符，防止下一次scanf()读取上一次留下的换行符
		system("cls");		//系统清屏

		switch ((int)choice) {
		case 1:
			if (s != NULL) {
				printf("栈已存在!\n");
				break;
			}
			initLStack(&s);
			printf("创建完成!\n");
			break;
		case 2: 
			if (s == NULL) {
				printf("栈不存在，请先创建!\n");
				break;
			}
			while (1){		//保证入栈的数据是整数
				printf("请输入要入栈的数据(整数)：");
				if (scanf("%d", &data)) {
					count = 0;
					break;
				}
				else {
					scanf("%*[^\n]");	//丢弃输入行中非数字的部分
					getchar();			//消耗掉换行符，防止下一次scanf()读取上一次留下的换行符
					if (count >= 1)
						printf("看不懂中文是吧，都说了输入一个整数!!!\n");
					else
						printf("输入无效，请重新输入一个整数!\n"); 
					count++;
				}
				system("pause");	//暂停	
				system("cls");		//系统清屏
			}
			pushLStack(s, data);
			break;
		case 3:
			if (s == NULL) {
				printf("栈不存在，请先创建!\n");
				break;
			}
			if (s->top == NULL) {
				printf("栈为空！\n");
				break;
			}
			popLStack(s, &data);
			printf("%d\n", data);
			break;
		case 4:
			isEmptyLStack(s);
			break;
		case 5:
			if (s == NULL) {
				printf("栈不存在，请先创建!\n");
				break;
			}
			if (s->top == NULL) {
				printf("栈为空!\n");
				break;
			}
			getTopLStack(s, &data);
			printf("%d\n", data);
			break;
		case 6:
			if (s == NULL) {
				printf("栈不存在，请先创建!\n");
				break;
			}
			LStackLength(s, &length); 
			printf("栈的长度为：%d\n", length);
			break;
		case 7:
			if (s == NULL) {
				printf("栈不存在，请先创建!\n");
				break;
			}
			if (s->top == NULL) {
				printf("栈为空!\n");
				break;
			}
			clearLStack(s);
			printf("清空完成!\n");
			break;
		case 8:
			destroyLStack(&s);
			break;
		case 9:
			exit(0);
		default:
			printf("不存在该数字，请重新输入!\n");
		}
		system("pause");	//暂停	
	}

	return 0;
}