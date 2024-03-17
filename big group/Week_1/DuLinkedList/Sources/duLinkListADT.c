#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:6031)
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//define�������ͣ������޸�
#define ElemType int

typedef struct LNode {
	ElemType data;		//����
	struct LNode* prev, * next;
}LNode;

ElemType data, newData, deleteData, searchData;


//����
//��ʼ��������������һ����ͷ���Ŀ�����
LNode* createNode(void) {
	LNode* head = (LNode*)malloc(sizeof(LNode));
	if (head == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
		return NULL;
	}
	head->data = 0;
	head->prev = NULL;
	head->next = NULL;
	printf("���������!\n");
	return head;
}

//����
void destroyList(LNode** head) {
	if (head == NULL) {
		printf("��������!\n");
		return;
	}
	LNode* p, * q;
	p = (*head)->next;
	while (p) {
		q = p;
		p = p->next;
		free(q);		//�ͷ�ÿһ�����
	}
	free(*head);	//�ͷ�δ�洢���ݵ�ͷ���
	(*head) = NULL;	//������������
	printf("������ɣ�\n");
}

//����
void insertNode(LNode* head) {
	if (head == NULL) {
		printf("�������ڣ����ȴ�������!\n");
		return;
	}
	printf("������Ҫ��������ݣ�");
	scanf("%d", &newData);
	LNode* newNode = (LNode*)malloc(sizeof(LNode));
	if (newNode == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
		return;
	}
	newNode->data = newData;		//�������ݴ洢������Ľ����
	newNode->next = NULL;
	if (head->next == NULL) {
		head->next = newNode;		//ͷ��㲻�洢����
		newNode->prev = head;
	}
	else {
		LNode* p = head->next;
		while (p->next != NULL) {	//β�巨���ҵ������ĩβ
			p = p->next;
		}
		p->next = newNode;			//��������
		newNode->prev = p;			
		printf("���ݲ���ɹ�\n");
	}
}

//ɾ��
void deleteNode(LNode* head) {
	if (head == NULL) {
		printf("�������ڣ����ȴ�������!\n");
		return;
	}
	else if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	printf("������Ҫɾ�������ݣ�");
	scanf("%d", &deleteData);
	LNode* p = head->next;				//�������������ָ�룬˫����ֻ��Ҫһ��ָ��

	while (p != NULL) {
		if (p->data == deleteData) {
			p->prev->next = p->next;	//����һ�����ֱ���������¸����
			if (p->next != NULL) {
				p->next->prev = p->prev;	//ֻ�е�Ҫɾ�������ݲ������һ�����ʱ�����ø���һ������ǰָ�븳ֵ
			}
			free(p);					//�ͷ���Ҫɾ���Ľ��
			printf("����ɾ���ɹ�\n");
			return;
		}
		else {
			p = p->next;				//���±���
		}
	}
	printf("���ݲ�����!\n");			//��ѭ��ֻ�����ݲ�����ʱ
}

//����
void searchNode(LNode* head) {
	if (head == NULL) {
		printf("�������ڣ����ȴ�������!\n");
		return;
	}
	else if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	printf("������Ҫ���ҵ����ݣ�");
	scanf("%d", &searchData);
	LNode* p = head->next;
	while (p != NULL && p->data != searchData) {	//����
		p = p->next;
	}
	if (p == NULL) {
		printf("���ݲ�����!\n");
		return;
	}
	else {
		printf("���ݴ��ڣ�\n");
	}
}

//չʾ����
void printList(LNode* head) {
	if (head == NULL) {
		printf("��������!\n");
		return;
	}else if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	LNode* p = head->next;			//ͷ��㲻�洢����
	printf("[");
	while (p != NULL) {				//��������
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

void menu() {		//���˵�
	printf("|-------------����������˵�-------------|\n");
	printf("|		[1]��������		 |\n");
	printf("|		[2]��������		 |\n");
	printf("|		[3]ɾ������		 |\n");
	printf("|		[4]��������		 |\n");
	printf("|		[5]��������		 |\n");
	printf("|		[6]��ӡ����		 |\n");
	printf("|		[7]�˳�	   		 |\n");
	printf("|----------------------------------------|\n");
	printf("�������Ӧ���֣�");
}

int main() {
	LNode* head = NULL;
	LNode* middle;
	int choice, flag;
	ElemType data;

	while (1) {
		system("cls");//ϵͳ����
		menu();		//��ʾ�˵�
		scanf("%d", &choice);
		system("cls");//ϵͳ����
		switch (choice) {
		case 1:
			if (head != NULL) {
				printf("�����Ѵ���!\n");	//����������ж�
				printf("������������ٴ���!\n");
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
			printf("�����ڸ����֣�����������!\n");
		}
		system("pause");	//��ͣ	
	}

	return 0;
}