#define _CRT_SECURE_NO_WARNINGS 1	//解决不能直接使用scanf的问题
#pragma warning(disable:6031)		//解决scanf返回值被忽略的问题

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../Header/LQueue.h"

int main() {

	LQueue* Q = NULL;
	int choice;
	int type,length;
	void* data = malloc(sizeof(double));

	
	while (1) {
		system("cls");      //系统清屏
		menu();             //显示菜单
		scanf("%d", &choice);//输入操作对应数字

		//清空缓冲区
		scanf("%*[^\n]"); // 丢弃输入行中非数字的部分
		getchar(); // 消耗掉换行符，防止下一次scanf()读取上一次留下的换行符
		system("cls");		//系统清屏

		switch (choice) {
		case 1:
			InitLQueue(&Q);
			printf("创建完成!\n");
			break;
		case 2:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			type = getType();
			LScan(data, type);
			EnLQueue(Q, data, type);
			break;
		case 3:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			DeLQueue(Q);
			break;
		case 4:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			if (IsEmptyLQueue(Q)) {
				printf("队列为空!\n");
			}
			else {
				printf("队列不为空!\n");
			}
			break;
		case 5:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			type = GetHeadLQueue(Q, data);
			LPrint(data, type);
			break;
		case 6:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			length = LengthLQueue(Q);
			printf("队列长度为：%d\n", length);
			break;
		case 7:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			ClearLQueue(Q);
			printf("清空完成!\n");
			break;
		case 8:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			DestoryLQueue(&Q);
			printf("销毁完成!\n");
			break;
		case 9:
			if (Q == NULL) {
				printf("队列不存在，请先创建队列！\n");
				break;
			}
			TraverseLQueue(Q, LPrint);
			break;
		case 10:
			exit(0);
		default:
			printf("不存在该数字，请重新输入!\n");
		}
		system("pause");	//暂停
	}


	return 0;
}

void menu() {
	printf("+---------------队列操作菜单-------------+\n");
	printf("|		[1]创建队列		 |\n");
	printf("|		[2]数据入队		 |\n");
	printf("|		[3]数据出队		 |\n");
	printf("|		[4]判断队列是否为空	 |\n");
	printf("|		[5]输出队头元素		 |\n");
	printf("|		[6]确定队列长度		 |\n");
	printf("|		[7]清空队列		 |\n");
	printf("|		[8]销毁队列		 |\n");
	printf("|		[9]打印队列		 |\n");
	printf("|		[10]退出		 |\n");
	printf("+----------------------------------------+\n");
	printf("请输入对应数字：");
}

//初始化
void InitLQueue(LQueue** Q) {
	(*Q) = (LQueue*)malloc(sizeof(LQueue));
	(*Q)->front = (*Q)->rear = NULL;
	(*Q)->length = 0;
}

//销毁队列
void DestoryLQueue(LQueue** Q) {
	ClearLQueue(*Q);
	free(*Q);
	(*Q) = NULL;
}

//检查队列是否为空
Status IsEmptyLQueue(const LQueue* Q) {
	if (Q->length == 0) {
		return true;
	}
	else if (Q->length > 0) {
		return false;
	}
}

//查看队头元素
int GetHeadLQueue(LQueue* Q, void* e) {
	if (Q->front == NULL) {
		printf("队列为空!\n");
		return -1;
	}
	int t = Q->front->type;
	switch (t) {
	case 1:
		*(int *)e = *(int*)(Q->front->data);
		break;
	case 2:
		*(double*)e = *(double*)(Q->front->data);
		break;
	case 3:
		*(char*)e = *(char*)(Q->front->data);
		break;
	}
	return t;
}

//确定队列长度
int LengthLQueue(LQueue* Q) {
	return Q->length;
}

//入队操作
Status EnLQueue(LQueue* Q, void* data,int type) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL) {
		free(p);
		printf("内存分配失败!\n");
		return false;
	}
	p->type = type;


	switch (type) {
	case 1:
		p->data = malloc(sizeof(int));
		if (p->data == NULL) {
			free(p->data);
			printf("内存分配失败!\n");
			return false;
		}
		*((int*)(p->data)) = *((int*)data);
		break;
	case 2:
		if (p->data == NULL) {
			free(p->data);
			printf("内存分配失败!\n");
			return false;
		}
		p->data = malloc(sizeof(double));
		*((double*)(p->data)) = *((double*)data);
		break;
	case 3:
		if (p->data == NULL) {
			free(p->data);
			printf("内存分配失败!\n");
			return false;
		}
		p->data = malloc(sizeof(char));
		*((char*)(p->data)) = *((char*)data);
		break;
	default:
		printf("输入错误!\n");
	}
	p->next = NULL;
	if (Q->front == NULL) {
		Q->front = p;
		Q->rear = p;
		Q->length++;
		return true;
	}
	Q->rear->next = p;
	Q->rear = p;
	Q->length++;
	return true;
}

//出队操作
Status DeLQueue(LQueue* Q) {
	if (IsEmptyLQueue(Q)) {
		printf("队列为空!\n");
		return false;
	}
	Node* p = Q->front;
	Q->front = Q->front->next;
	if (Q->front == NULL) {
		Q->rear == NULL;
	}
	free(p);
	Q->length--;
	return true;
}

//清空队列
void ClearLQueue(LQueue* Q) {
	while (!IsEmptyLQueue(Q)) {
		DeLQueue(Q);
	}
}

//遍历函数操作
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q)) {
	if (Q->front == NULL) {
		printf("队列为空!\n");
		return false;
	}
	if (foo == NULL) {
		return false;
	}
	Node* curr = Q->front;
	while (curr != NULL) {
		foo(curr->data,curr->type);
		curr = curr->next;
	}
	return true;
}

int getType() {
	int type = 0;
	while(1){
		system("cls");
		printf("1代表整数,2代表小数,3代表字符!\n");
		printf("请输入数据类型:");
		scanf("%d", &type);
		scanf("%*[^\n]"); // 丢弃输入行中非数字的部分
		getchar(); // 消耗掉换行符，防止下一次scanf()读取上一次留下的换行符
		if (type >= 1 && type <= 3) {
			break;
		}
		printf("输入错误，请重新输入!\n");
		system("pause");	//暂停
	}
	return type;
}

void LScan(void* q, int type) {
	switch (type) {
	case 1:
		printf("请输入一个整数:");
		scanf("%d", (int*)q);
		break;
	case 2:
		printf("请输入一个小数:");
		scanf("%lf", (double*)q);
		break;
	case 3:
		printf("请输入一个字符:");
		scanf("%c", (char*)q);
		break;
	}
}

//操作函数
void LPrint(void* q,int type) {
	
	switch (type) {
	case 1:
		printf("%d ", *((int*)q));
		break;
	case 2:
		printf("%.3lf ", *(double*)q);
		break;
	case 3:
		printf("%c ", *(char*)q);
		break;
	}
}

