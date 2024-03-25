#define _CRT_SECURE_NO_WARNINGS 1	//�������ֱ��ʹ��scanf������
#pragma warning(disable:6031)		//���scanf����ֵ�����Ե�����

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
		system("cls");      //ϵͳ����
		menu();             //��ʾ�˵�
		scanf("%d", &choice);//���������Ӧ����

		//��ջ�����
		scanf("%*[^\n]"); // �����������з����ֵĲ���
		getchar(); // ���ĵ����з�����ֹ��һ��scanf()��ȡ��һ�����µĻ��з�
		system("cls");		//ϵͳ����

		switch (choice) {
		case 1:
			InitLQueue(&Q);
			printf("�������!\n");
			break;
		case 2:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			type = getType();
			LScan(data, type);
			EnLQueue(Q, data, type);
			break;
		case 3:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			DeLQueue(Q);
			break;
		case 4:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			if (IsEmptyLQueue(Q)) {
				printf("����Ϊ��!\n");
			}
			else {
				printf("���в�Ϊ��!\n");
			}
			break;
		case 5:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			type = GetHeadLQueue(Q, data);
			LPrint(data, type);
			break;
		case 6:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			length = LengthLQueue(Q);
			printf("���г���Ϊ��%d\n", length);
			break;
		case 7:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			ClearLQueue(Q);
			printf("������!\n");
			break;
		case 8:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			DestoryLQueue(&Q);
			printf("�������!\n");
			break;
		case 9:
			if (Q == NULL) {
				printf("���в����ڣ����ȴ������У�\n");
				break;
			}
			TraverseLQueue(Q, LPrint);
			break;
		case 10:
			exit(0);
		default:
			printf("�����ڸ����֣�����������!\n");
		}
		system("pause");	//��ͣ
	}


	return 0;
}

void menu() {
	printf("+---------------���в����˵�-------------+\n");
	printf("|		[1]��������		 |\n");
	printf("|		[2]�������		 |\n");
	printf("|		[3]���ݳ���		 |\n");
	printf("|		[4]�ж϶����Ƿ�Ϊ��	 |\n");
	printf("|		[5]�����ͷԪ��		 |\n");
	printf("|		[6]ȷ�����г���		 |\n");
	printf("|		[7]��ն���		 |\n");
	printf("|		[8]���ٶ���		 |\n");
	printf("|		[9]��ӡ����		 |\n");
	printf("|		[10]�˳�		 |\n");
	printf("+----------------------------------------+\n");
	printf("�������Ӧ���֣�");
}

//��ʼ��
void InitLQueue(LQueue** Q) {
	(*Q) = (LQueue*)malloc(sizeof(LQueue));
	(*Q)->front = (*Q)->rear = NULL;
	(*Q)->length = 0;
}

//���ٶ���
void DestoryLQueue(LQueue** Q) {
	ClearLQueue(*Q);
	free(*Q);
	(*Q) = NULL;
}

//�������Ƿ�Ϊ��
Status IsEmptyLQueue(const LQueue* Q) {
	if (Q->length == 0) {
		return true;
	}
	else if (Q->length > 0) {
		return false;
	}
}

//�鿴��ͷԪ��
int GetHeadLQueue(LQueue* Q, void* e) {
	if (Q->front == NULL) {
		printf("����Ϊ��!\n");
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

//ȷ�����г���
int LengthLQueue(LQueue* Q) {
	return Q->length;
}

//��Ӳ���
Status EnLQueue(LQueue* Q, void* data,int type) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL) {
		free(p);
		printf("�ڴ����ʧ��!\n");
		return false;
	}
	p->type = type;


	switch (type) {
	case 1:
		p->data = malloc(sizeof(int));
		if (p->data == NULL) {
			free(p->data);
			printf("�ڴ����ʧ��!\n");
			return false;
		}
		*((int*)(p->data)) = *((int*)data);
		break;
	case 2:
		if (p->data == NULL) {
			free(p->data);
			printf("�ڴ����ʧ��!\n");
			return false;
		}
		p->data = malloc(sizeof(double));
		*((double*)(p->data)) = *((double*)data);
		break;
	case 3:
		if (p->data == NULL) {
			free(p->data);
			printf("�ڴ����ʧ��!\n");
			return false;
		}
		p->data = malloc(sizeof(char));
		*((char*)(p->data)) = *((char*)data);
		break;
	default:
		printf("�������!\n");
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

//���Ӳ���
Status DeLQueue(LQueue* Q) {
	if (IsEmptyLQueue(Q)) {
		printf("����Ϊ��!\n");
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

//��ն���
void ClearLQueue(LQueue* Q) {
	while (!IsEmptyLQueue(Q)) {
		DeLQueue(Q);
	}
}

//������������
Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q)) {
	if (Q->front == NULL) {
		printf("����Ϊ��!\n");
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
		printf("1��������,2����С��,3�����ַ�!\n");
		printf("��������������:");
		scanf("%d", &type);
		scanf("%*[^\n]"); // �����������з����ֵĲ���
		getchar(); // ���ĵ����з�����ֹ��һ��scanf()��ȡ��һ�����µĻ��з�
		if (type >= 1 && type <= 3) {
			break;
		}
		printf("�����������������!\n");
		system("pause");	//��ͣ
	}
	return type;
}

void LScan(void* q, int type) {
	switch (type) {
	case 1:
		printf("������һ������:");
		scanf("%d", (int*)q);
		break;
	case 2:
		printf("������һ��С��:");
		scanf("%lf", (double*)q);
		break;
	case 3:
		printf("������һ���ַ�:");
		scanf("%c", (char*)q);
		break;
	}
}

//��������
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

