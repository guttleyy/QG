#define _CRT_SECURE_NO_WARNINGS 1	//�������ֱ��ʹ��scanf������
#pragma warning(disable:6031)		//���scanf����ֵ�����Ե�����
#include "../Headers/LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//��ʼ����ջ
Status initLStack(LinkStack** s) {
	*s = (LinkStack*)malloc(sizeof(LinkStack));
	if (*s == NULL) {
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}
	(*s)->count = 0;
	(*s)->top = NULL;
	return SUCCESS;
}

//�ж�ջ�Ƿ�Ϊ��
Status isEmptyLStack(LinkStack* s) {
	if (s == NULL) {
		printf("ջ�����ڣ����ȴ���!\n");
		return ERROR;
	}
	if (s->top == NULL) {
		printf("ջΪ�գ�\n");
		return SUCCESS;
	}
	printf("ջ��Ϊ�գ�\n");
	return ERROR;
}

//�õ�ջ��Ԫ��
Status getTopLStack(LinkStack* s, ElemType* e) {
	
	*e = s->top->data;
	return SUCCESS;
}

//���ջ
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

//����ջ
Status destroyLStack(LinkStack** s) {
	if ((*s) == NULL) {
		printf("ջ�����ڣ����ȴ���!\n");
		return ERROR;
	}
	clearLStack(*s);
	free(*s);
	(*s) = NULL;
	printf("�������!\n");
	return SUCCESS;
}

//���ջ����
Status LStackLength(LinkStack* s, int* length) {
	*length = s->count;
	return SUCCESS;
}

//��ջ
Status pushLStack(LinkStack* s, ElemType data) {
	LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode));
	if (p == NULL) {
		printf("�ڴ����ʧ��!\n");
		return ERROR;
	}
	p->data = data;
	p->next = s->top;
	s->top = p;
	s->count++;
	return SUCCESS;
}

//��ջ
Status popLStack(LinkStack* s, ElemType* data) {
	StackNode* p = s->top;
	*data = p->data;
	s->top = p->next;
	free(p);
	s->count--;
	return SUCCESS;
}

//���˵�
void menu() {
	printf("|-------------��ջ�����˵�---------------|\n");
	printf("|		[1]����ջ		 |\n");
	printf("|		[2]������ջ		 |\n");
	printf("|		[3]���ݳ�ջ		 |\n");
	printf("|		[4]�ж�ջ�Ƿ�Ϊ��	 |\n");
	printf("|		[5]���ջ��Ԫ��		 |\n");
	printf("|		[6]���ջ�ĳ���		 |\n");
	printf("|		[7]���ջ		 |\n");
	printf("|		[8]����ջ		 |\n");
	printf("|		[9]�˳�			 |\n");
	printf("|----------------------------------------|\n");
	printf("�������Ӧ���֣�");
}

int main() {
	
	LinkStack* s = NULL;
	int choice;
	int length = 0;
	int count = 0;
	ElemType data = 0;
	ElemType* outData = NULL;

	while (1) {
		system("cls");		//ϵͳ����
		menu();				//��ʾ�˵�
		scanf("%d", &choice);

		//��ջ�����
		scanf("%*[^\n]");	//�����������з����ֵĲ���
		getchar();			//���ĵ����з�����ֹ��һ��scanf()��ȡ��һ�����µĻ��з�
		system("cls");		//ϵͳ����

		switch ((int)choice) {
		case 1:
			if (s != NULL) {
				printf("ջ�Ѵ���!\n");
				break;
			}
			initLStack(&s);
			printf("�������!\n");
			break;
		case 2: 
			if (s == NULL) {
				printf("ջ�����ڣ����ȴ���!\n");
				break;
			}
			while (1){		//��֤��ջ������������
				printf("������Ҫ��ջ������(����)��");
				if (scanf("%d", &data)) {
					count = 0;
					break;
				}
				else {
					scanf("%*[^\n]");	//�����������з����ֵĲ���
					getchar();			//���ĵ����з�����ֹ��һ��scanf()��ȡ��һ�����µĻ��з�
					if (count >= 1)
						printf("�����������ǰɣ���˵������һ������!!!\n");
					else
						printf("������Ч������������һ������!\n"); 
					count++;
				}
				system("pause");	//��ͣ	
				system("cls");		//ϵͳ����
			}
			pushLStack(s, data);
			break;
		case 3:
			if (s == NULL) {
				printf("ջ�����ڣ����ȴ���!\n");
				break;
			}
			if (s->top == NULL) {
				printf("ջΪ�գ�\n");
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
				printf("ջ�����ڣ����ȴ���!\n");
				break;
			}
			if (s->top == NULL) {
				printf("ջΪ��!\n");
				break;
			}
			getTopLStack(s, &data);
			printf("%d\n", data);
			break;
		case 6:
			if (s == NULL) {
				printf("ջ�����ڣ����ȴ���!\n");
				break;
			}
			LStackLength(s, &length); 
			printf("ջ�ĳ���Ϊ��%d\n", length);
			break;
		case 7:
			if (s == NULL) {
				printf("ջ�����ڣ����ȴ���!\n");
				break;
			}
			if (s->top == NULL) {
				printf("ջΪ��!\n");
				break;
			}
			clearLStack(s);
			printf("������!\n");
			break;
		case 8:
			destroyLStack(&s);
			break;
		case 9:
			exit(0);
		default:
			printf("�����ڸ����֣�����������!\n");
		}
		system("pause");	//��ͣ	
	}

	return 0;
}