#define _CRT_SECURE_NO_WARNINGS 1	//解决不能直接使用scanf的问题
#pragma warning(disable:6031)		//解决scanf返回值被忽略的问题
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//define数据类型，方便修改
#define ElemType int

typedef struct LNode {
	ElemType data;		//数据
	struct LNode* next;
}LNode;

ElemType data,newData, deleteData, searchData;

//生成
//初始化函数，创建了一个带头结点的空链表
LNode* createNode(void) {
	LNode* head = (LNode*)malloc(sizeof(LNode));
	if (head == NULL) {
		printf("内存分配失败！\n");
		return NULL;
	}
	head->data = 0;
	head->next = NULL;
	printf("链表创建完成!\n");
	return head;
}

//销毁
void destroyList(LNode** head) {
	LNode* p, *q;
	p = (*head)->next;		
	while (p) {
		q = p;			
		p = p->next;	
		free(q);		//释放每一个结点
	}					
	(*head)->next = NULL;
	(*head) = NULL;	//彻底销毁链表
	printf("销毁完成！\n");
}

//插入
void insertNode(LNode* head) {
	if (head == NULL) {
		printf("链表不存在!\n");
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
	}
	else {
		LNode* p = head->next;
		while (p->next != NULL) {	//尾插法，找到链表的末尾
			p = p->next;
		}
		p->next = newNode;			//插入数据
		printf("数据插入成功\n");
	}
}

//删除
void deleteNode(LNode* head) {
	if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	else if (head == NULL) {
		printf("链表不存在!\n");
		return;
	}
	printf("请输入要删除的数据：");
	scanf("%d", &deleteData);
	LNode* p = head->next;				//用来遍历链表的指针
	LNode* q = head;					//指向p的上一个结点

	while (p != NULL) {					
		if (p->data == deleteData) {	
			q->next = p->next;			//将上一个结点直接连接下下个结点
			free(p);					//释放需要删除的结点
			printf("数据删除成功\n");
			return;
		}
		else {
			p = p->next;
			q = q->next;				//向下遍历
		}
	}
	printf("数据不存在!\n");			//出循环只有数据不存在时
}

//查找
void searchNode(LNode* head) {
	if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	else if (head == NULL) {
		printf("链表不存在!\n");
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
	if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	else if (head == NULL) {
		printf("链表不存在!\n");
		return;
	}
	LNode* p = head->next;			//头结点不存储数据
	printf("[");
	while(p != NULL){				//遍历链表
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


//单链表的奇偶调换
void paritySwap(LNode* head) {
	if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	else if (head == NULL) {
		printf("链表不存在!\n");
		return;
	}
	LNode* p, * p1, * p2;
	p = head;			//头指针不存储数据					
	p1 = p->next;
	p2 = p1->next;
	while (p1->next != NULL && p2->next != NULL) {

		//p1与p2所指的结点交换
		p->next = p2;
		p1->next = p2->next;
		p2 ->next = p1;

		//向后移动
		p = p1;
		p1 = p->next;
		p2 = p1->next;
	}
	printf("奇偶调换完成！\n");
}

//返回单链表中间结点
LNode* middleNode(LNode* head) {
	if (head->next == NULL) {
		printf("链表为空!\n");
		return;
	}
	else if (head == NULL) {
		printf("链表不存在!\n");
		return;
	}
	if (head->next->next == NULL) {
		return head->next;  //链表只有一个结点时直接返回头节点
	}
	LNode* fast, * slow;
	fast = head->next;
	slow = head->next;
	while (fast->next != NULL && fast != NULL) {
		slow = slow->next;
		fast = fast->next;
		if (fast->next != NULL) {
			fast = fast->next;
		}
		else {
			break;			//当fast无法再前进两步时跳出循环
		}
	}
	return slow;
}

//判断链表是否成环
int isCycle(LNode* head) {	//0不成环 1成环
	if (head->next == NULL || head->next->next == NULL) {
		return 0;	//链表为空或只有一个结点时无法成环
	}
	LNode* fast, * slow;
	fast = head->next;
	slow = head->next;

	//快慢指针同步遍历
	while (fast->next != NULL && fast != NULL) {
		slow = slow->next;
		fast = fast->next;
		if (fast->next != NULL) {
			fast = fast->next;
		}
		else {
			break;			//当fast无法再前进两步时，说明不成环，跳出循环
		}
		//相遇，则成环
		if (fast == slow) {
			return 1;
		}
	}
	//不相遇，则无环
	return 0;
}

//反转链表（迭代）
void reserveListIterative(LNode* head) {
	if (head->next == NULL || head->next->next == NULL) {
		return;	//链表为空或只有一个结点时无法反转
	}
	LNode* prev, * curr, * next;
	prev = NULL;
	curr = head->next;
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head->next = prev;
	printf("反转链表完成！\n");
}

//反转链表（递归）	不会

void menu() {		//主菜单
	printf("|-------------单链表操作菜单-------------|\n");
	printf("|		[1]创建链表		 |\n");
	printf("|		[2]插入数据		 |\n");
	printf("|		[3]删除数据		 |\n");
	printf("|		[4]查找数据		 |\n");
	printf("|		[5]销毁链表		 |\n");
	printf("|		[6]打印链表		 |\n");
	printf("|		[7]奇偶调换		 |\n");
	printf("|		[8]查询中间结点		 |\n");
	printf("|		[9]判断是否成环		 |\n");
	printf("|		[10]反转链表	   	 |\n");
	printf("|		[11]退出	   	 |\n");
	printf("|----------------------------------------|\n");
	printf("请输入对应数字：");
}

int main() {
	LNode* head = NULL;
	LNode* middle;
	int choice,flag;
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
			paritySwap(head);
			break;
		case 8:
			middle = middleNode(head);
			printf("中间结点数据为：%d\n", middle->data);
			break;
		case 9:
			flag = isCycle(head);
			if (flag) {
				printf("链表成环!\n");
			}
			else{
				printf("链表不成环!\n");
			}
			break;
		case 10:
			reserveListIterative(head);
			break;
		case 11:
			exit(0);
		default:
			printf("不存在该数字，请重新输入!\n");
		}
		system("pause");	//暂停	
	}
	
	return 0;
}