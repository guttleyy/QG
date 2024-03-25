#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAX_SIZE 100

//利用两个顺序栈


//操作数栈
typedef struct {
    double data[MAX_SIZE];
    int top;
} NumberStack;

void initSNum(NumberStack* ns);//初始化
int pushSNum(NumberStack* ns, double num);//入栈
int popSNum(NumberStack* ns);//出栈
double getEleTopSNum(NumberStack* ns);//获取最顶上的元素（不出栈）
double popEleTopSNum(NumberStack* ns);//获取最顶上的元素（出栈）
int isEmptySNum(NumberStack* ns);//判断是否为空


//操作符栈
typedef struct {
    char data[MAX_SIZE];
    int top;
} OperationStack;

void initSOpt(OperationStack* os);//初始化
int pushSOpt(OperationStack* os, char opt);//入栈
int popSOpt(OperationStack* os);//出栈
char getEleTopSOpt(OperationStack* os);//获取最顶上的元素（不出栈）
char popEleTopSOpt(OperationStack* os);//获取最顶上的元素（出栈）
int isEmptySOpt(OperationStack* os);//判断是否为空


//与计算相关的函数
int opt(char signal);//计算优先级
double caculatorTwo(double v1, double v2, char signal);//计算栈顶两元素
int valid(char express[]);//表达式合法性判断

//核心计算函数
int cacul(OperationStack* os, NumberStack* ns);//将输入的中缀表达式转换成后缀表达式，并计算

void menu();//菜单




#endif 