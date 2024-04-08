#define _CRT_SECURE_NO_WARNINGS 1	//�������ֱ��ʹ��scanf������
#pragma warning(disable:6031)		//���scanf����ֵ�����Ե�����

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "../Headers/BinarySortTree.h"

int main() {
	BinarySortTreePtr bst = NULL;
	int choice,count;
	ElemType value = 0;
	
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
			BST_init(&bst);
			printf("�������!\n");
			break;
		case 2:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			while (1) {		//��֤����������������
				printf("������һ��������");
				if (scanf("%d", &value)) {
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

			BST_insert(bst, value);
			printf("�������!\n");
			break;
		case 3:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("��Ϊ��!\n");
				break;
			}
			while (1) {		//��֤��ѯ������������
				printf("������Ҫ��ѯ��������");
				if (scanf("%d", &value)) {
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
			BST_search(bst, value);
			break;
		case 4:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("��Ϊ��!\n");
				break;
			}
			while (1) {		//��֤ɾ��������������
				printf("������Ҫɾ����������");
				if (scanf("%d", &value)) {
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

			BST_delete(&bst, value);
			break;
		case 5:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("��Ϊ��!\n");
				break;
			}
			printf("�ǵݹ� �������:\n");
			BST_preorderI(bst, visit);
			printf("\n");
			printf("�ݹ�   �������:\n");
			BST_preorderR(bst->root, visit);
			printf("\n");
			break;
		case 6:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("��Ϊ��!\n");
				break;
			}
			printf("�ǵݹ� �������:\n");
			BST_inorderI(bst, visit);
			printf("\n");
			printf("�ݹ�   �������:\n");
			BST_inorderR(bst->root, visit);
			printf("\n");
			break;
		case 7:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("��Ϊ��!\n");
				break;
			}
			printf("�ǵݹ� �������:\n");
			BST_postorderI(bst, visit);
			printf("\n");
			printf("�ݹ�   �������:\n");
			BST_postorderR(bst->root, visit);
			printf("\n");
			break;
		case 8:
			if (bst == NULL) {
				printf("�������ڣ����ȴ�����!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("��Ϊ��!\n");
				break;
			}
			printf("�������:\n");
			BST_levelOrder(bst, visit);
			printf("\n");
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


void menu() {
	printf("+---------------���������������˵�--------------+\n");
	printf("|		[1]������			|\n");
	printf("|		[2]��������			|\n");
	printf("|		[3]��������			|\n");
	printf("|		[4]ɾ������			|\n");
	printf("|		[5]�������			|\n");
	printf("|		[6]�������			|\n");
	printf("|		[7]�������			|\n");
	printf("|		[8]�������			|\n");
	printf("|		[9]�˳�				|\n");
	printf("+-----------------------------------------------+\n");
	printf("�������Ӧ���֣�");
}

//��ʼ��
Status BST_init(BinarySortTreePtr* bst) {
	if ((*bst) != NULL) {
		printf("���Ѵ���!\n");
		return false;
	}
	(*bst) = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	if ((*bst) == NULL) {
		printf("�ڴ����ʧ��!\n");
		return false;
	}
	(*bst)->root = NULL;
	return true;
}

//����
Status BST_insert(BinarySortTreePtr bst, ElemType value) {
	//�������
	NodePtr node = (NodePtr)malloc(sizeof(Node));
	if (node == NULL) {
		printf("�ڴ����ʧ��!\n");
		return false;
	}
	node->value = value;
	node->left = node->right = NULL;

	//���ڵ�Ϊ��
	if (bst->root == NULL) {
		bst->root = node;
		return true;
	}

	//�����������������ҵ���ȷ�Ĳ���λ��
	NodePtr curr = bst->root;	//����ָ��
	NodePtr par = NULL;			//���ڵ�ָ��
	while (curr != NULL) {
		par = curr;
		if (value < curr->value) {
			curr = curr->left;
		}
		else if (value > curr->value) {
			curr = curr->right;
		}else {			//ֵ�Ѵ��ڣ�������
			free(node);
			return false;
		}
	}

	if (value < par->value) {
		par->left = node;
	}
	else if (value > par->value) {
		par->right = node;
	}
	return true;
}

//����
Status BST_search(BinarySortTreePtr bst, ElemType value) {
	NodePtr curr = bst->root;	//����ָ��
	int flag = 0; //0������  1����
	while (curr != NULL) {
		if (value < curr->value) {
			curr = curr->left;
		}
		else if (value > curr->value) {
			curr = curr->right;
		}
		else {
			flag = 1;
			break;
		}
	}
	if (flag) {			//����
		printf("���ݴ���!\n");
		return true;
	}
	printf("���ݲ�����!\n");
	return false;		//������
}

//ɾ��
Status BST_delete(BinarySortTreePtr* bst, ElemType value) {
	
	//�����������������ҵ���ȷ��λ��
	NodePtr curr = (*bst)->root;	//����ָ��
	NodePtr par = NULL;			//���ڵ�ָ��

	while (curr != NULL) {
		if (value < curr->value) {
			par = curr;
			curr = curr->left;
		}
		else if (value > curr->value) {
			par = curr;
			curr = curr->right;
		}
		else if (value == curr->value) {
			break;
		}
	}
	if (curr == NULL) {
		printf("Ҫɾ�������ݲ�����!\n");
		return false;	//������
	}


	//Ҷ�ӽ��
	if (curr->left == NULL && curr->right == NULL) {
		if (par == NULL) {
			free(curr);
			(*bst)->root = NULL;
		}
		else if (par->left == curr) {
			free(curr);
			par->left = NULL;
		}
		else if (par->right == curr) {
			free(curr);
			par->right = NULL;
		}
	}
	//ֻ��һ�����ӵĽ��
	else if (curr->left == NULL || curr->right == NULL) {
		if (curr->left == NULL) {	//ֻ���Һ���
			if (par == NULL) {		//currΪ���ڵ�
				(*bst)->root = curr->right;
			}
			else if (par->left == curr) {	//currΪpar����ڵ�
				par->left = curr->right;
			}
			else if (par->right == curr) {	//currΪpar���ҽڵ�
				par->right = curr->right;
			}
		}
		else if (curr->right == NULL) {	//ֻ������
			if (par == NULL) {
				curr = curr->left;
			}
			else if (par->left == curr) {	//currΪpar����ڵ�
				par->left = curr->left;
			}
			else if (par->right == curr) {	//currΪpar���ҽڵ�
				par->right = curr->left;
			}
		}
		free(curr);
	}
	else {	//���������ӣ���ֱ�Ӻ��
		NodePtr behindMin = curr->right;	//����������С�ڵ�
		NodePtr behindPar = curr;			//����������С�ڵ�ĸ��ڵ�
		while (behindMin->left != NULL) {
			behindPar = behindMin;
			behindMin = behindMin->left;
		}
		curr->value = behindMin->value;

		if (behindMin == behindPar->left) {
			behindPar->left = behindMin->right;
			free(behindMin);
		}
		else if (behindMin == behindPar->right) {
			behindPar->right = behindMin->right;
			free(behindMin);
		}
	}
	printf("ɾ���ɹ�!\n");
	return true;
}

//����������ǵݹ飩
Status BST_preorderI(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Stack* stack = NULL;
	initStack(&stack);
	NodePtr curr = bst->root;

	while (curr != NULL || !isEmpty(stack)) {
		if (curr != NULL) {
			visit(curr);
			if (curr->right != NULL) {
				push(stack, curr->right);		//�Һ�����ջ
			}	
			curr = curr->left;					//�������ߣ�ֱ��Ϊ��
		}
		else {
			curr = pop(stack);					//�ߵ����ˣ����ϸ���ջ���Һ��Ӵ�
		}
	}
	return true;
}

//����������ݹ飩
Status BST_preorderR(NodePtr Node, void (*visit)(NodePtr node)) {
	if (Node == NULL)	return true;
	visit(Node);
	BST_preorderR(Node->left, visit);
	BST_preorderR(Node->right, visit);
	return true;
}

//����������ǵݹ飩
Status BST_inorderI(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Stack* stack = NULL;
	initStack(&stack);
	NodePtr curr = bst->root;

	while (curr != NULL || !isEmpty(stack)) {
		if (curr != NULL) {
			push(stack, curr);
			curr = curr->left;					//�������ߣ�ֱ��Ϊ��
		}
		else {
			curr = pop(stack);					//�ߵ����ˣ����ϸ���ջ��
			visit(curr);						//���ʵ�ǰ�ڵ�
			curr = curr->right;					//��������
		}
	}
	return true;
}

//����������ݹ飩
Status BST_inorderR(NodePtr Node, void (*visit)(NodePtr node)) {
	if (Node == NULL)	return true;
	BST_inorderR(Node->left, visit);
	visit(Node);
	BST_inorderR(Node->right, visit);
	return true;
}

//����������ǵݹ飩
Status BST_postorderI(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Stack* stack = NULL;
	initStack(&stack);
	NodePtr curr = bst->root;
	NodePtr last = NULL;

	while (curr != NULL || !isEmpty(stack)) {
		while (curr != NULL) {
			push(stack, curr);
			curr = curr->left;
		}
		curr = getTop(stack);
		if (curr->right == NULL || curr->right == last) {	//�����ǰ�ڵ��������Ϊ�գ������Ѿ������ʹ��ˣ�����ʵ�ǰ
			visit(curr);
			last = curr;		//��¼�ϴη��ʵĽڵ�
			pop(stack);
			curr = NULL;
		}
		else {
			curr = curr->right;								//���û����������������
		}
	}
}

//����������ݹ飩
Status BST_postorderR(NodePtr Node, void (*visit)(NodePtr node)) {
	if (Node == NULL)	return true;
	BST_postorderR(Node->left, visit);
	BST_postorderR(Node->right, visit);
	visit(Node);
	return true;
}

//�������
Status BST_levelOrder(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Queue* q = NULL;
	initQueue(&q);
	NodePtr curr = bst->root;
	
	//���ڵ����
	inQueue(q, curr);
	
	while (!isEmptyQ(q)) {
		curr = outQueue(q);	//���Ӳ����ʵ�ǰ�ڵ�
		visit(curr);

		// �����ǰ�ڵ������ӽڵ㣬�������
		if (curr->left != NULL) {
			inQueue(q, curr->left);
		}
		// �����ǰ�ڵ������ӽڵ㣬�������
		if (curr->right != NULL) {
			inQueue(q, curr->right);
		}
	}
	return true;
}


void visit(NodePtr node) {
	if (node != NULL) {
		printf("%d ", node->value);
	}
}

//˳��ջ��ʼ��
Status initStack(Stack** stack) {
	if ((*stack) != NULL)	return false;	//ջ�Ѵ���
	(*stack) = (Stack*)malloc(sizeof(Stack));
	if ((*stack) == NULL) {
		printf("�ڴ����ʧ��!\n");
		return false;
	}
	(*stack)->top = -1;
	return true;
}

//˳��ջΪ���ж�
Status isEmpty(Stack* stack) {
	if (stack == NULL)	return false;	//ջ������
	if (stack->top == -1)	return true;
	else return false;
}

//˳��ջ��ջ
Status push(Stack* stack, NodePtr node) {
	if (stack == NULL)	return false;	//ջ������
	if (stack->top == MAX - 1) {
		printf("ջ��!\n");
		return false;
	}
	stack->top++;
	stack->stack[stack->top] = node;
}

//˳��ջ��ջ
NodePtr pop(Stack* stack) {
	if (stack == NULL)	return false;	//ջ������
	if (isEmpty(stack)) {
		printf("ջΪ��!\n");
		return NULL;
	}
	NodePtr node = stack->stack[stack->top];
	stack->top--;
	return node;
}

//��ȡջ���ڵ�
NodePtr getTop(Stack* stack) {
	if (stack == NULL)	return false;	//ջ������
	if (isEmpty(stack)) {
		printf("ջΪ��!\n");
		return NULL;
	}
	NodePtr node = stack->stack[stack->top];
	return node;
}

//��ʼ��
Status initQueue(Queue** q) {
	if ((*q) != NULL)	return false;

	(*q) = (Queue*)malloc(sizeof(Queue));
	if ((*q) == NULL) {
		printf("�ڴ����ʧ��!\n");
		return false;
	}

	(*q)->front = (*q)->rear = NULL;

	return true;
}

//Ϊ���ж�
Status isEmptyQ(Queue* q) {
	if (q == NULL)	return false;	//���в�����
	if (q->front == NULL)	return true;
	else return false;
}

//���
Status inQueue(Queue* q, NodePtr node) {
	if (q == NULL)	return false;	//���в�����
	QNode* newQNode = (QNode*)malloc(sizeof(QNode));
	newQNode->data = node;
	newQNode->next = NULL;
	if (q->front == NULL) {
		q->front = newQNode;
		q->rear = newQNode;
	}
	else {
		q->rear->next = newQNode;
		q->rear = newQNode;
	}
	return true;
}

//����
NodePtr outQueue(Queue* q) {
	if (q == NULL)	return NULL;	//���в�����
	if (q->front == NULL) {
		printf("����Ϊ��!\n");
		return NULL;
	}
	QNode* temp = q->front;
	NodePtr node = temp->data;
	q->front = q->front->next;
	free(temp);
	if (q->front == NULL) {		//���ΨһԪ���Ѿ������еĻ������ö�βָ��Ϊ��
		q->rear == NULL;
	}
	return node;
}


