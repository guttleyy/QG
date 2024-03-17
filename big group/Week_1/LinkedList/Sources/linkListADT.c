#define _CRT_SECURE_NO_WARNINGS 1	//�������ֱ��ʹ��scanf������
#pragma warning(disable:6031)		//���scanf����ֵ�����Ե�����
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//define�������ͣ������޸�
#define ElemType int

typedef struct LNode {
	ElemType data;		//����
	struct LNode* next;
}LNode;

ElemType data,newData, deleteData, searchData;

//����
//��ʼ��������������һ����ͷ���Ŀ�����
LNode* createNode(void) {
	LNode* head = (LNode*)malloc(sizeof(LNode));
	if (head == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
		return NULL;
	}
	head->data = 0;
	head->next = NULL;
	printf("���������!\n");
	return head;
}

//����
void destroyList(LNode** head) {
	LNode* p, *q;
	p = (*head)->next;		
	while (p) {
		q = p;			
		p = p->next;	
		free(q);		//�ͷ�ÿһ�����
	}					
	(*head)->next = NULL;
	(*head) = NULL;	//������������
	printf("������ɣ�\n");
}

//����
void insertNode(LNode* head) {
	if (head == NULL) {
		printf("��������!\n");
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
	}
	else {
		LNode* p = head->next;
		while (p->next != NULL) {	//β�巨���ҵ������ĩβ
			p = p->next;
		}
		p->next = newNode;			//��������
		printf("���ݲ���ɹ�\n");
	}
}

//ɾ��
void deleteNode(LNode* head) {
	if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	else if (head == NULL) {
		printf("��������!\n");
		return;
	}
	printf("������Ҫɾ�������ݣ�");
	scanf("%d", &deleteData);
	LNode* p = head->next;				//�������������ָ��
	LNode* q = head;					//ָ��p����һ�����

	while (p != NULL) {					
		if (p->data == deleteData) {	
			q->next = p->next;			//����һ�����ֱ���������¸����
			free(p);					//�ͷ���Ҫɾ���Ľ��
			printf("����ɾ���ɹ�\n");
			return;
		}
		else {
			p = p->next;
			q = q->next;				//���±���
		}
	}
	printf("���ݲ�����!\n");			//��ѭ��ֻ�����ݲ�����ʱ
}

//����
void searchNode(LNode* head) {
	if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	else if (head == NULL) {
		printf("��������!\n");
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
	if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	else if (head == NULL) {
		printf("��������!\n");
		return;
	}
	LNode* p = head->next;			//ͷ��㲻�洢����
	printf("[");
	while(p != NULL){				//��������
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


//���������ż����
void paritySwap(LNode* head) {
	if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	else if (head == NULL) {
		printf("��������!\n");
		return;
	}
	LNode* p, * p1, * p2;
	p = head;			//ͷָ�벻�洢����					
	p1 = p->next;
	p2 = p1->next;
	while (p1->next != NULL && p2->next != NULL) {

		//p1��p2��ָ�Ľ�㽻��
		p->next = p2;
		p1->next = p2->next;
		p2 ->next = p1;

		//����ƶ�
		p = p1;
		p1 = p->next;
		p2 = p1->next;
	}
	printf("��ż������ɣ�\n");
}

//���ص������м���
LNode* middleNode(LNode* head) {
	if (head->next == NULL) {
		printf("����Ϊ��!\n");
		return;
	}
	else if (head == NULL) {
		printf("��������!\n");
		return;
	}
	if (head->next->next == NULL) {
		return head->next;  //����ֻ��һ�����ʱֱ�ӷ���ͷ�ڵ�
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
			break;			//��fast�޷���ǰ������ʱ����ѭ��
		}
	}
	return slow;
}

//�ж������Ƿ�ɻ�
int isCycle(LNode* head) {	//0���ɻ� 1�ɻ�
	if (head->next == NULL || head->next->next == NULL) {
		return 0;	//����Ϊ�ջ�ֻ��һ�����ʱ�޷��ɻ�
	}
	LNode* fast, * slow;
	fast = head->next;
	slow = head->next;

	//����ָ��ͬ������
	while (fast->next != NULL && fast != NULL) {
		slow = slow->next;
		fast = fast->next;
		if (fast->next != NULL) {
			fast = fast->next;
		}
		else {
			break;			//��fast�޷���ǰ������ʱ��˵�����ɻ�������ѭ��
		}
		//��������ɻ�
		if (fast == slow) {
			return 1;
		}
	}
	//�����������޻�
	return 0;
}

//��ת����������
void reserveListIterative(LNode* head) {
	if (head->next == NULL || head->next->next == NULL) {
		return;	//����Ϊ�ջ�ֻ��һ�����ʱ�޷���ת
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
	printf("��ת������ɣ�\n");
}

//��ת�����ݹ飩	����

void menu() {		//���˵�
	printf("|-------------����������˵�-------------|\n");
	printf("|		[1]��������		 |\n");
	printf("|		[2]��������		 |\n");
	printf("|		[3]ɾ������		 |\n");
	printf("|		[4]��������		 |\n");
	printf("|		[5]��������		 |\n");
	printf("|		[6]��ӡ����		 |\n");
	printf("|		[7]��ż����		 |\n");
	printf("|		[8]��ѯ�м���		 |\n");
	printf("|		[9]�ж��Ƿ�ɻ�		 |\n");
	printf("|		[10]��ת����	   	 |\n");
	printf("|		[11]�˳�	   	 |\n");
	printf("|----------------------------------------|\n");
	printf("�������Ӧ���֣�");
}

int main() {
	LNode* head = NULL;
	LNode* middle;
	int choice,flag;
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
			paritySwap(head);
			break;
		case 8:
			middle = middleNode(head);
			printf("�м�������Ϊ��%d\n", middle->data);
			break;
		case 9:
			flag = isCycle(head);
			if (flag) {
				printf("����ɻ�!\n");
			}
			else{
				printf("�����ɻ�!\n");
			}
			break;
		case 10:
			reserveListIterative(head);
			break;
		case 11:
			exit(0);
		default:
			printf("�����ڸ����֣�����������!\n");
		}
		system("pause");	//��ͣ	
	}
	
	return 0;
}