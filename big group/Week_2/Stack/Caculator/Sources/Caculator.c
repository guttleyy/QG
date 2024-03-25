#define _CRT_SECURE_NO_WARNINGS 1	//解决不能直接使用scanf的问题
#pragma warning(disable:6031)		//解决scanf返回值被忽略的问题

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "../Header/Caculator.h"




int main() {
    OperationStack* os = (OperationStack*)malloc(sizeof(OperationStack));
    NumberStack* ns = (NumberStack*)malloc(sizeof(NumberStack));
    int choice, flag;

    while (1) {
        system("cls");      //系统清屏
        menu();             //显示菜单
        scanf("%d", &choice);//输入操作对应数字

        //清空缓冲区
        scanf("%*[^\n]");	//丢弃输入行中非数字的部分
        getchar();			//消耗掉换行符，防止下一次scanf()读取上一次留下的换行符
        system("cls");		//系统清屏

        switch (choice) {
        case 1:
            flag = cacul(os, ns);
            while (flag == 0) {
                printf("语法错误，请重新输入!\n");
                system("pause");	//暂停
                system("cls");      //系统清屏
                flag = cacul(os, ns);
            }
            break;
        case 2:
            exit(0);
        default:
            printf("不存在该数字，请重新输入!\n");
        }
        system("pause");	//暂停
    }

    return 0;
}



//表达式合法性判断
int valid(char express[]) {
    //该栈用于判断左右括号是否匹配
    OperationStack* opts = (OperationStack*)malloc(sizeof(OperationStack));
    initSOpt(opts);
    int len = strlen(express);

    //遍历字符串
    int i;
    for (i = 0; i < len; i++) {
        char c = express[i];
        //1.判断是否含有非法字符
        if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == '.'
            || (c >= '0' && c <= '9') || c == '(' || c == ')')) {
            printf("含有非法字符!\n");
            return 0; //表达式不合法
        }


        //2.判断左右括号是否匹配
        /*
        方法：
            遇到左括号入栈
            遇到右括号，将栈顶元素出栈
         （1）如果遍历完表达式，发现栈不为空，说明左括号数量多，缺右括号
         （2）如果遍历到右括号，发现栈为空，说明缺左括号
        */
        if (c == '('){

            //括号外的数字与括号之前必须有操作符
            if (i > 0) {
                char prev = express[i - 1];
                if (prev >= '0' && prev <= '9') {
                    printf("括号外的数字与括号之前必须有操作符!\n");
                    return 0;
                }
            }

            if (i < (len - 1)) {
                // 括号相邻 () 不合法
                if (express[i + 1] == ')') {
                    printf("括号为空!\n");
                    return 0;
                }
                // 左括号后面不能是除减号以外的操作符
                // 非法：(+9-2)
                else if (express[i + 1] == '+' || express[i + 1] == '*' || express[i + 1] == '/') {
                    printf("左括号后面不能是操作符!\n");
                    return 0;
                }
            }
            pushSOpt(opts, c);
        }
        else if (c == ')') {

            //括号外的数字与括号之前必须有操作符
            if (i < (len - 1)) {
                char next = express[i + 1];
                if (next >= '0' && next <= '9') {
                    printf("括号外的数字与括号之前必须有操作符!\n");
                    return 0;
                }
            }

            //遍历到右括号，发现栈为空，说明缺左括号
            if (isEmptySOpt(opts)) {
                printf("缺少左括号!\n");
                return 0;
            }
            popEleTopSOpt(opts);
        }


        //3.操作符非法问题
        else if (c == '+' || c == '-' || c == '*' || c == '/' ) {
            //操作符前后不能为空 
            //非法：9+5*
            if (i == 0 || i == (len - 1)) {
                printf("操作符前后不能为空!\n");
                return 0;
            }

            else if (i < (len - 1)){
                char next = express[i + 1];
                //操作符前后不能为操作符
                //非法：9++5
                if (next == '+' ||next == '*' || next == '/') {
                    printf("操作符前后不能为操作符!\n");
                    return 0;
                }

                //操作符后不能是右括号
                //非法：(2+9*)
                else if (next == ')') {
                    printf("操作符后不能是右括号!\n");
                    return 0;
                }

                //操作符后的'-'直接当做负号
                else if (next == '-'){
                    printf("负数请用括号括起来!\n");
                    return 0;
                }
            }
        }
        
        
    }

    //遍历完表达式，发现栈不为空，说明左括号数量多，缺右括号
    if (!isEmptySOpt(opts)) {
        printf("缺少右括号!\n");
        return 0;
    }
    return 1;
}




//核心
//将输入的中缀表达式转换成后缀表达式，并计算
int cacul(OperationStack* os, NumberStack* ns) {
    char express[MAX_SIZE];
    printf("请输入一个表达式:");
    scanf("%s", express);
    if (!valid(express)) return 0;  //表达式合法性判断
    initSOpt(os);
    initSNum(ns);
    int len = strlen(express);      //计算该表达式的长度
    int i, j;
    printf("后缀表达式为:");
    for (i = 0; i < len; i++) {     //遍历表达式

        //符号
        if (express[i] == '+' || express[i] == '*' || express[i] == '/' ||
            (express[i] == '-' && express[i - 1] >= '0' && express[i - 1] <= '9' && i != 0)){
            //判断是一个减号，而不是负号

            //
            if (isEmptySOpt(os)) {          //操作符栈为空，直接将符号入栈
                pushSOpt(os, express[i]);   
                continue;                   //进入下一轮判断
            }
            char topEle = getEleTopSOpt(os);//操作符栈不为空
            if (topEle == '(') {            
                pushSOpt(os, express[i]);   //最顶符号为左括号，直接入栈
                continue;
            }
            while (opt(topEle) >= opt(express[i])) {//优先级低于最顶符号
                printf("%c ", popEleTopSOpt(os));   //输出，做为后缀表达式的一个字符
                double v1 = popEleTopSNum(ns);
                double v2 = popEleTopSNum(ns);
                double result = caculatorTwo(v1, v2, topEle);//计算最顶端的两个操作数
                pushSNum(ns, result);               //将结果数再次入栈
                topEle = getEleTopSOpt(os);
            }
            pushSOpt(os, express[i]);               //将符号入栈
        }
        else if (express[i] == '(') {
            pushSOpt(os, express[i]);               //左括号直接入栈
        }
        else if (express[i] == ')') {
            char topEle = popEleTopSOpt(os);
            while (topEle != '(') {                 //取到左括号为止
                printf("%c ", topEle);
                double v1 = popEleTopSNum(ns);
                double v2 = popEleTopSNum(ns);
                double result = caculatorTwo(v1, v2, topEle);//计算两个操作数
                pushSNum(ns, result);               //结果直接入栈
                topEle = popEleTopSOpt(os);         
            }

        }

        //数字
        else {
            char num[MAX_SIZE];                     //用于存储一个数
            int index = 0;                          
            printf("%c", express[i]);               
            num[index++] = express[i];              //将数字放入数组
            int flag = 0;                           //用于判断是否到表达式字符串的末尾
            for (j = 1; i + j < len; j++) {         
                if ((express[i + j] >= '0' && express[i + j] <= '9') || express[i + j] == '.') {//包含小数
                    printf("%c", express[i + j]);   
                    num[index++] = express[i + j];  
                    if (i + j == (len-1)) {         
                        flag = 1;                   //到末尾
                    }
                }
                else {
                    i = i + j - 1;                  //将i移动到该数的最后一位数字处，以此判断下一个字符
                    printf(" ");
                    break;
                }
            }
            num[index++] = '\0';
            double value = atof(num);               //atof将数字字符串转换成double类型的数
            pushSNum(ns, value);                    //将这个数入操作数栈
            if (flag) {
                printf(" ");
                break;
            }
        }
    }
    while (!isEmptySOpt(os)) {                      //将操作符栈中的符号都取出
        char topEle = popEleTopSOpt(os);            
        printf("%c ", topEle);                      
        double v1 = popEleTopSNum(ns);
        double v2 = popEleTopSNum(ns);
        double result = caculatorTwo(v1, v2, topEle);//每次取出，都直接计算
        pushSNum(ns, result);
    }

    
    printf("\n= %.2lf", popEleTopSNum(ns));
    return 1;
}




//主菜单
void menu() {
    printf("+-------------简易计算器-----------------+\n");
    printf("|                                        |\n");
    printf("|		[1]计算                  |\n");
    printf("|		[2]退出			 |\n");
    printf("|                                        |\n");
    printf("+----------------------------------------+\n");
    printf("请输入对应数字：");
}




//计算栈顶两元素
double caculatorTwo(double v1, double v2, char signal) {
    if (signal == '+') {
        return (v2 + v1);
    }
    else if (signal == '-') {
        return (v2 - v1);
    }
    else if (signal == '*') {
        return (v2 * v1);
    }
    else if (signal == '/') {
        return (v2 / v1);
    }
}


//计算优先级
int opt(char signal) {
    if (signal == '+' || signal == '-') {
        return 1;
    }
    else if (signal == '*' || signal == '/') {
        return 2;
    }
}



//操作数栈

//初始化
void initSNum(NumberStack* ns) {
    ns->top = -1;
}

//入栈
int pushSNum(NumberStack* ns, double num) {
    if (ns->top < MAX_SIZE - 1) {
        ns->data[(ns->top) + 1] = num;
        ns->top++;
        return 1;
    }
    return 0;
}

//出栈
int popSNum(NumberStack* ns) {
    if (ns->top == -1) {
        return 0;
    }

    ns->data[ns->top] = '\0';
    ns->top--;
    return 1;
}

//获取最顶上的元素（不出栈）
double getEleTopSNum(NumberStack* ns) {
    if (ns->top == -1) {
        return '\0';
    }
    double n = ns->data[ns->top];
    return n;
}

//获取最顶上的元素（出栈）
double popEleTopSNum(NumberStack* ns) {
    if (ns->top == -1) {
        return '\0';
    }
    double n = ns->data[ns->top];
    ns->data[ns->top] = '\0';
    ns->top--;
    return n;
}

//判断是否为空
int isEmptySNum(NumberStack* ns) {
    if (ns->top >= 0)
        return 0;
    return 1;
}






//操作符栈

//初始化
void initSOpt(OperationStack* os) {
    os->top = -1;
}

//入栈
int pushSOpt(OperationStack* os, char opt) {
    if (os->top < MAX_SIZE - 1) {
        os->data[(os->top) + 1] = opt;
        os->top++;
        return 1;
    }
    return 0;
}

//出栈
int popSOpt(OperationStack* os) {
    if (os->top == -1) {
        return 0;
    }

    os->data[os->top] = '\0';
    os->top--;
    return 1;
}

//获取最顶上的元素（不出栈）
char getEleTopSOpt(OperationStack* os) {
    if (os->top == -1) {
        return '\0';
    }
    char e = os->data[os->top];
    return e;
}

//获取最顶上的元素（出栈）
char popEleTopSOpt(OperationStack* os) {
    if (os->top == -1) {
        return '\0';
    }
    char e = os->data[os->top];
    os->data[os->top] = '\0';
    os->top--;
    return e;
}

//判断是否为空
int isEmptySOpt(OperationStack* os) {
    if (os->top >= 0) {
        return 0;
    }
    return 1;
}