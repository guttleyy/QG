#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//define数据类型，方便修改
#define ElemType int

typedef struct LNode {
	ElemType data;		//数据
	struct LNode* prev, * next;
}LNode;

ElemType data, newData, deleteData, searchData;


//生成
//初始化函数，创建了一个带头结点的空链表
LNode* createNode(void) {
	LNode* head = (LNode*)malloc(sizeof(LNode));
	if (head == NULL) {
		printf("内存分配失败！\n");
		return NULL;
	}
	head->data = 0;
	head->prev = NULL;
	head->next = NULL;
	printf("链表创建完成!\n");
	return head;
}

//销毁
void destroyList(LNode** head) {
	if (head == NULL) {
		printf("链表不存在!\n");
		return;
	}
	LNode* p, * q;
	p = (*head)->next;
	while (p) {
		q = p;
		p = p->next;
		free(q);		//释放每一个结点
	}
	free(*head);	//释放未存储数据的头结点
	(*head) = NULL;	//彻底销毁链表
	printf("销毁完成！\n");
}

//插入
void insertNode(LNode* head) {
	if (head == NULL) {
		printf("链表不存在，请先创建链表!\n");
		return;
	}
	printf("请输入要插入的数据：");
	scanf("%d", &newData);
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL) {
		printf("内存分配失败！\n");
		return;
	}
	newNode->data = newData;		//将新数据存储到分配的结点中
	newNode->next = NULL;
	if (head->next == NULL) {
		head->next = newNode;		//头结点不存储数据
		newNode->prev = head;
	}
	else {
		LNode* p = head->next;
		while (p->next != NULL) {	//尾插法，找到链表的末尾
			p = p->next;
		}
		p->next = newNode;			//插入数据
		newNode->prev = p;			
		printf("数据插入成功\n");
	}
}

//删除
void deleteNode(LNode* head) {
	if (head == NULL) {
		printf("链表不存在，请先创建链表!\n");
		return;
	}
	else if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	printf("请输入要删除的数据：");
	scanf("%d", &deleteData);
	LNode* p = head->next;				//用来遍历链表的指针，双链表只需要一个指针

	while (p != NULL) {
		if (p->data == deleteData) {
			p->prev->next = p->next;	//将上一个结点直接连接下下个结点
			if (p->next != NULL) {
				p->next->prev = p->prev;	//只有当要删除的数据不是最后一个结点时，才用给后一个结点的前指针赋值
			}
			free(p);					//释放需要删除的结点
			printf("数据删除成功\n");
			return;
		}
		else {
			p = p->next;				//向下遍历
		}
	}
	printf("数据不存在!\n");			//出循环只有数据不存在时
}

//查找
void searchNode(LNode* head) {
	if (head == NULL) {
		printf("链表不存在，请先创建链表!\n");
		return;
	}
	else if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	printf("请输入要查找的数据：");
	scanf("%d", &searchData);
	LNode* p = head->next;
	while (p != NULL && p->data != searchData) {	//遍历
		p = p->next;
	}
	if (p == NULL) {
		printf("数据不存在!\n");
		return;
	}
	else {
		printf("数据存在！\n");
	}
}

//展示链表
void printList(LNode* head) {
	if (head == NULL) {
		printf("链表不存在!\n");
		return;
	}else if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	LNode* p = head->next;			//头结点不存储数据
	printf("[");
	while (p != NULL) {				//遍历链表
		if (p->next == NULL) {
			printf("%d", p->data);
		}
		else {
			printf("%d, ", p->data);
		}
		p = p->next;
	}
	printf("]\n");
}

void menu() {		//主菜单
	printf("|-------------单链表操作菜单-------------|\n");
	printf("|		[1]创建链表		 |\n");
	printf("|		[2]插入数据		 |\n");
	printf("|		[3]删除数据		 |\n");
	printf("|		[4]查找数据		 |\n");
	printf("|		[5]销毁链表		 |\n");
	printf("|		[6]打印链表		 |\n");
	printf("|		[7]退出	   		 |\n");
	printf("|----------------------------------------|\n");
	printf("请输入对应数字：");
}

int main() {
	LNode* head = NULL;
	LNode* middle;
	int choice, flag;
	ElemType data;

	while (1) {
		system("cls");//系统清屏
		menu();		//显示菜单
		scanf("%d", &choice);
		system("cls");//系统清屏
		switch (choice) {
		case 1:
			if (head != NULL) {
				printf("链表已存在!\n");	//链表存在性判断
				printf("请销毁链表后再创建!\n");
				break;
			}
			head = createNode();
			break;
		case 2:
			insertNode(head);
			break;
		case 3:
			deleteNode(head);
			break;
		case 4:
			searchNode(head);
			break;
		case 5:
			destroyList(&head);
			break;
		case 6:
			printList(head);
			break;
		case 7:
			exit(0);
		default:
			printf("不存在该数字，请重新输入!\n");
		}
		system("pause");	//暂停	
	}

	return 0;
}