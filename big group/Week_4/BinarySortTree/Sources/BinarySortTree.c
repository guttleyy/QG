#define _CRT_SECURE_NO_WARNINGS 1	//解决不能直接使用scanf的问题
#pragma warning(disable:6031)		//解决scanf返回值被忽略的问题

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
		system("cls");      //系统清屏
		menu();             //显示菜单
		scanf("%d", &choice);//输入操作对应数字

		//清空缓冲区
		scanf("%*[^\n]"); // 丢弃输入行中非数字的部分
		getchar(); // 消耗掉换行符，防止下一次scanf()读取上一次留下的换行符
		system("cls");		//系统清屏

		switch (choice) {
		case 1:
			BST_init(&bst);
			printf("创建完成!\n");
			break;
		case 2:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			while (1) {		//保证入树的数据是整数
				printf("请输入一个整数：");
				if (scanf("%d", &value)) {
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

			BST_insert(bst, value);
			printf("插入完成!\n");
			break;
		case 3:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("树为空!\n");
				break;
			}
			while (1) {		//保证查询的数据是整数
				printf("请输入要查询的整数：");
				if (scanf("%d", &value)) {
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
			BST_search(bst, value);
			break;
		case 4:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("树为空!\n");
				break;
			}
			while (1) {		//保证删除的数据是整数
				printf("请输入要删除的整数：");
				if (scanf("%d", &value)) {
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

			BST_delete(&bst, value);
			break;
		case 5:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("树为空!\n");
				break;
			}
			printf("非递归 先序遍历:\n");
			BST_preorderI(bst, visit);
			printf("\n");
			printf("递归   先序遍历:\n");
			BST_preorderR(bst->root, visit);
			printf("\n");
			break;
		case 6:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("树为空!\n");
				break;
			}
			printf("非递归 中序遍历:\n");
			BST_inorderI(bst, visit);
			printf("\n");
			printf("递归   中序遍历:\n");
			BST_inorderR(bst->root, visit);
			printf("\n");
			break;
		case 7:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("树为空!\n");
				break;
			}
			printf("非递归 后序遍历:\n");
			BST_postorderI(bst, visit);
			printf("\n");
			printf("递归   后序遍历:\n");
			BST_postorderR(bst->root, visit);
			printf("\n");
			break;
		case 8:
			if (bst == NULL) {
				printf("树不存在，请先创建树!\n");
				break;
			}
			if (bst->root == NULL) {
				printf("树为空!\n");
				break;
			}
			printf("层序遍历:\n");
			BST_levelOrder(bst, visit);
			printf("\n");
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


void menu() {
	printf("+---------------二叉排序树操作菜单--------------+\n");
	printf("|		[1]创建树			|\n");
	printf("|		[2]插入数据			|\n");
	printf("|		[3]查找数据			|\n");
	printf("|		[4]删除数据			|\n");
	printf("|		[5]先序遍历			|\n");
	printf("|		[6]中序遍历			|\n");
	printf("|		[7]后序遍历			|\n");
	printf("|		[8]层序遍历			|\n");
	printf("|		[9]退出				|\n");
	printf("+-----------------------------------------------+\n");
	printf("请输入对应数字：");
}

//初始化
Status BST_init(BinarySortTreePtr* bst) {
	if ((*bst) != NULL) {
		printf("树已存在!\n");
		return false;
	}
	(*bst) = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
	if ((*bst) == NULL) {
		printf("内存分配失败!\n");
		return false;
	}
	(*bst)->root = NULL;
	return true;
}

//插入
Status BST_insert(BinarySortTreePtr bst, ElemType value) {
	//创建结点
	NodePtr node = (NodePtr)malloc(sizeof(Node));
	if (node == NULL) {
		printf("内存分配失败!\n");
		return false;
	}
	node->value = value;
	node->left = node->right = NULL;

	//根节点为空
	if (bst->root == NULL) {
		bst->root = node;
		return true;
	}

	//遍历二叉排序树，找到正确的插入位置
	NodePtr curr = bst->root;	//遍历指针
	NodePtr par = NULL;			//父节点指针
	while (curr != NULL) {
		par = curr;
		if (value < curr->value) {
			curr = curr->left;
		}
		else if (value > curr->value) {
			curr = curr->right;
		}else {			//值已存在，不插入
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

//查找
Status BST_search(BinarySortTreePtr bst, ElemType value) {
	NodePtr curr = bst->root;	//遍历指针
	int flag = 0; //0不存在  1存在
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
	if (flag) {			//存在
		printf("数据存在!\n");
		return true;
	}
	printf("数据不存在!\n");
	return false;		//不存在
}

//删除
Status BST_delete(BinarySortTreePtr* bst, ElemType value) {
	
	//遍历二叉排序树，找到正确的位置
	NodePtr curr = (*bst)->root;	//遍历指针
	NodePtr par = NULL;			//父节点指针

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
		printf("要删除的数据不存在!\n");
		return false;	//不存在
	}


	//叶子结点
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
	//只有一个孩子的结点
	else if (curr->left == NULL || curr->right == NULL) {
		if (curr->left == NULL) {	//只有右孩子
			if (par == NULL) {		//curr为根节点
				(*bst)->root = curr->right;
			}
			else if (par->left == curr) {	//curr为par的左节点
				par->left = curr->right;
			}
			else if (par->right == curr) {	//curr为par的右节点
				par->right = curr->right;
			}
		}
		else if (curr->right == NULL) {	//只有左孩子
			if (par == NULL) {
				curr = curr->left;
			}
			else if (par->left == curr) {	//curr为par的左节点
				par->left = curr->left;
			}
			else if (par->right == curr) {	//curr为par的右节点
				par->right = curr->left;
			}
		}
		free(curr);
	}
	else {	//有两个孩子，找直接后继
		NodePtr behindMin = curr->right;	//右子树的最小节点
		NodePtr behindPar = curr;			//右子树的最小节点的父节点
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
	printf("删除成功!\n");
	return true;
}

//先序遍历（非递归）
Status BST_preorderI(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Stack* stack = NULL;
	initStack(&stack);
	NodePtr curr = bst->root;

	while (curr != NULL || !isEmpty(stack)) {
		if (curr != NULL) {
			visit(curr);
			if (curr->right != NULL) {
				push(stack, curr->right);		//右孩子入栈
			}	
			curr = curr->left;					//向左下走，直到为空
		}
		else {
			curr = pop(stack);					//走到底了，回上个入栈的右孩子处
		}
	}
	return true;
}

//先序遍历（递归）
Status BST_preorderR(NodePtr Node, void (*visit)(NodePtr node)) {
	if (Node == NULL)	return true;
	visit(Node);
	BST_preorderR(Node->left, visit);
	BST_preorderR(Node->right, visit);
	return true;
}

//中序遍历（非递归）
Status BST_inorderI(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Stack* stack = NULL;
	initStack(&stack);
	NodePtr curr = bst->root;

	while (curr != NULL || !isEmpty(stack)) {
		if (curr != NULL) {
			push(stack, curr);
			curr = curr->left;					//向左下走，直到为空
		}
		else {
			curr = pop(stack);					//走到底了，回上个入栈处
			visit(curr);						//访问当前节点
			curr = curr->right;					//向右下走
		}
	}
	return true;
}

//中序遍历（递归）
Status BST_inorderR(NodePtr Node, void (*visit)(NodePtr node)) {
	if (Node == NULL)	return true;
	BST_inorderR(Node->left, visit);
	visit(Node);
	BST_inorderR(Node->right, visit);
	return true;
}

//后序遍历（非递归）
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
		if (curr->right == NULL || curr->right == last) {	//如果当前节点的右子树为空，或者已经被访问过了，则访问当前
			visit(curr);
			last = curr;		//记录上次访问的节点
			pop(stack);
			curr = NULL;
		}
		else {
			curr = curr->right;								//如果没有则向右子树遍历
		}
	}
}

//后序遍历（递归）
Status BST_postorderR(NodePtr Node, void (*visit)(NodePtr node)) {
	if (Node == NULL)	return true;
	BST_postorderR(Node->left, visit);
	BST_postorderR(Node->right, visit);
	visit(Node);
	return true;
}

//层序遍历
Status BST_levelOrder(BinarySortTreePtr bst, void (*visit)(NodePtr node)) {
	Queue* q = NULL;
	initQueue(&q);
	NodePtr curr = bst->root;
	
	//根节点入队
	inQueue(q, curr);
	
	while (!isEmptyQ(q)) {
		curr = outQueue(q);	//出队并访问当前节点
		visit(curr);

		// 如果当前节点有左子节点，将其入队
		if (curr->left != NULL) {
			inQueue(q, curr->left);
		}
		// 如果当前节点有右子节点，将其入队
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

//顺序栈初始化
Status initStack(Stack** stack) {
	if ((*stack) != NULL)	return false;	//栈已存在
	(*stack) = (Stack*)malloc(sizeof(Stack));
	if ((*stack) == NULL) {
		printf("内存分配失败!\n");
		return false;
	}
	(*stack)->top = -1;
	return true;
}

//顺序栈为空判断
Status isEmpty(Stack* stack) {
	if (stack == NULL)	return false;	//栈不存在
	if (stack->top == -1)	return true;
	else return false;
}

//顺序栈入栈
Status push(Stack* stack, NodePtr node) {
	if (stack == NULL)	return false;	//栈不存在
	if (stack->top == MAX - 1) {
		printf("栈满!\n");
		return false;
	}
	stack->top++;
	stack->stack[stack->top] = node;
}

//顺序栈出栈
NodePtr pop(Stack* stack) {
	if (stack == NULL)	return false;	//栈不存在
	if (isEmpty(stack)) {
		printf("栈为空!\n");
		return NULL;
	}
	NodePtr node = stack->stack[stack->top];
	stack->top--;
	return node;
}

//获取栈顶节点
NodePtr getTop(Stack* stack) {
	if (stack == NULL)	return false;	//栈不存在
	if (isEmpty(stack)) {
		printf("栈为空!\n");
		return NULL;
	}
	NodePtr node = stack->stack[stack->top];
	return node;
}

//初始化
Status initQueue(Queue** q) {
	if ((*q) != NULL)	return false;

	(*q) = (Queue*)malloc(sizeof(Queue));
	if ((*q) == NULL) {
		printf("内存分配失败!\n");
		return false;
	}

	(*q)->front = (*q)->rear = NULL;

	return true;
}

//为空判断
Status isEmptyQ(Queue* q) {
	if (q == NULL)	return false;	//队列不存在
	if (q->front == NULL)	return true;
	else return false;
}

//入队
Status inQueue(Queue* q, NodePtr node) {
	if (q == NULL)	return false;	//队列不存在
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

//出队
NodePtr outQueue(Queue* q) {
	if (q == NULL)	return NULL;	//队列不存在
	if (q->front == NULL) {
		printf("队列为空!\n");
		return NULL;
	}
	QNode* temp = q->front;
	NodePtr node = temp->data;
	q->front = q->front->next;
	free(temp);
	if (q->front == NULL) {		//如果唯一元素已经出队列的话，就让队尾指针为空
		q->rear == NULL;
	}
	return node;
}


