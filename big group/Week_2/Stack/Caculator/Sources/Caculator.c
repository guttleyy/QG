#define _CRT_SECURE_NO_WARNINGS 1	//�������ֱ��ʹ��scanf������
#pragma warning(disable:6031)		//���scanf����ֵ�����Ե�����

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
        system("cls");      //ϵͳ����
        menu();             //��ʾ�˵�
        scanf("%d", &choice);//���������Ӧ����

        //��ջ�����
        scanf("%*[^\n]");	//�����������з����ֵĲ���
        getchar();			//���ĵ����з�����ֹ��һ��scanf()��ȡ��һ�����µĻ��з�
        system("cls");		//ϵͳ����

        switch (choice) {
        case 1:
            flag = cacul(os, ns);
            while (flag == 0) {
                printf("�﷨��������������!\n");
                system("pause");	//��ͣ
                system("cls");      //ϵͳ����
                flag = cacul(os, ns);
            }
            break;
        case 2:
            exit(0);
        default:
            printf("�����ڸ����֣�����������!\n");
        }
        system("pause");	//��ͣ
    }

    return 0;
}



//���ʽ�Ϸ����ж�
int valid(char express[]) {
    //��ջ�����ж����������Ƿ�ƥ��
    OperationStack* opts = (OperationStack*)malloc(sizeof(OperationStack));
    initSOpt(opts);
    int len = strlen(express);

    //�����ַ���
    int i;
    for (i = 0; i < len; i++) {
        char c = express[i];
        //1.�ж��Ƿ��зǷ��ַ�
        if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == '.'
            || (c >= '0' && c <= '9') || c == '(' || c == ')')) {
            printf("���зǷ��ַ�!\n");
            return 0; //���ʽ���Ϸ�
        }


        //2.�ж����������Ƿ�ƥ��
        /*
        ������
            ������������ջ
            ���������ţ���ջ��Ԫ�س�ջ
         ��1�������������ʽ������ջ��Ϊ�գ�˵�������������࣬ȱ������
         ��2����������������ţ�����ջΪ�գ�˵��ȱ������
        */
        if (c == '('){

            //�����������������֮ǰ�����в�����
            if (i > 0) {
                char prev = express[i - 1];
                if (prev >= '0' && prev <= '9') {
                    printf("�����������������֮ǰ�����в�����!\n");
                    return 0;
                }
            }

            if (i < (len - 1)) {
                // �������� () ���Ϸ�
                if (express[i + 1] == ')') {
                    printf("����Ϊ��!\n");
                    return 0;
                }
                // �����ź��治���ǳ���������Ĳ�����
                // �Ƿ���(+9-2)
                else if (express[i + 1] == '+' || express[i + 1] == '*' || express[i + 1] == '/') {
                    printf("�����ź��治���ǲ�����!\n");
                    return 0;
                }
            }
            pushSOpt(opts, c);
        }
        else if (c == ')') {

            //�����������������֮ǰ�����в�����
            if (i < (len - 1)) {
                char next = express[i + 1];
                if (next >= '0' && next <= '9') {
                    printf("�����������������֮ǰ�����в�����!\n");
                    return 0;
                }
            }

            //�����������ţ�����ջΪ�գ�˵��ȱ������
            if (isEmptySOpt(opts)) {
                printf("ȱ��������!\n");
                return 0;
            }
            popEleTopSOpt(opts);
        }


        //3.�������Ƿ�����
        else if (c == '+' || c == '-' || c == '*' || c == '/' ) {
            //������ǰ����Ϊ�� 
            //�Ƿ���9+5*
            if (i == 0 || i == (len - 1)) {
                printf("������ǰ����Ϊ��!\n");
                return 0;
            }

            else if (i < (len - 1)){
                char next = express[i + 1];
                //������ǰ����Ϊ������
                //�Ƿ���9++5
                if (next == '+' ||next == '*' || next == '/') {
                    printf("������ǰ����Ϊ������!\n");
                    return 0;
                }

                //������������������
                //�Ƿ���(2+9*)
                else if (next == ')') {
                    printf("������������������!\n");
                    return 0;
                }

                //���������'-'ֱ�ӵ�������
                else if (next == '-'){
                    printf("������������������!\n");
                    return 0;
                }
            }
        }
        
        
    }

    //��������ʽ������ջ��Ϊ�գ�˵�������������࣬ȱ������
    if (!isEmptySOpt(opts)) {
        printf("ȱ��������!\n");
        return 0;
    }
    return 1;
}




//����
//���������׺���ʽת���ɺ�׺���ʽ��������
int cacul(OperationStack* os, NumberStack* ns) {
    char express[MAX_SIZE];
    printf("������һ�����ʽ:");
    scanf("%s", express);
    if (!valid(express)) return 0;  //���ʽ�Ϸ����ж�
    initSOpt(os);
    initSNum(ns);
    int len = strlen(express);      //����ñ��ʽ�ĳ���
    int i, j;
    printf("��׺���ʽΪ:");
    for (i = 0; i < len; i++) {     //�������ʽ

        //����
        if (express[i] == '+' || express[i] == '*' || express[i] == '/' ||
            (express[i] == '-' && express[i - 1] >= '0' && express[i - 1] <= '9' && i != 0)){
            //�ж���һ�����ţ������Ǹ���

            //
            if (isEmptySOpt(os)) {          //������ջΪ�գ�ֱ�ӽ�������ջ
                pushSOpt(os, express[i]);   
                continue;                   //������һ���ж�
            }
            char topEle = getEleTopSOpt(os);//������ջ��Ϊ��
            if (topEle == '(') {            
                pushSOpt(os, express[i]);   //�����Ϊ�����ţ�ֱ����ջ
                continue;
            }
            while (opt(topEle) >= opt(express[i])) {//���ȼ����������
                printf("%c ", popEleTopSOpt(os));   //�������Ϊ��׺���ʽ��һ���ַ�
                double v1 = popEleTopSNum(ns);
                double v2 = popEleTopSNum(ns);
                double result = caculatorTwo(v1, v2, topEle);//������˵�����������
                pushSNum(ns, result);               //��������ٴ���ջ
                topEle = getEleTopSOpt(os);
            }
            pushSOpt(os, express[i]);               //��������ջ
        }
        else if (express[i] == '(') {
            pushSOpt(os, express[i]);               //������ֱ����ջ
        }
        else if (express[i] == ')') {
            char topEle = popEleTopSOpt(os);
            while (topEle != '(') {                 //ȡ��������Ϊֹ
                printf("%c ", topEle);
                double v1 = popEleTopSNum(ns);
                double v2 = popEleTopSNum(ns);
                double result = caculatorTwo(v1, v2, topEle);//��������������
                pushSNum(ns, result);               //���ֱ����ջ
                topEle = popEleTopSOpt(os);         
            }

        }

        //����
        else {
            char num[MAX_SIZE];                     //���ڴ洢һ����
            int index = 0;                          
            printf("%c", express[i]);               
            num[index++] = express[i];              //�����ַ�������
            int flag = 0;                           //�����ж��Ƿ񵽱��ʽ�ַ�����ĩβ
            for (j = 1; i + j < len; j++) {         
                if ((express[i + j] >= '0' && express[i + j] <= '9') || express[i + j] == '.') {//����С��
                    printf("%c", express[i + j]);   
                    num[index++] = express[i + j];  
                    if (i + j == (len-1)) {         
                        flag = 1;                   //��ĩβ
                    }
                }
                else {
                    i = i + j - 1;                  //��i�ƶ������������һλ���ִ����Դ��ж���һ���ַ�
                    printf(" ");
                    break;
                }
            }
            num[index++] = '\0';
            double value = atof(num);               //atof�������ַ���ת����double���͵���
            pushSNum(ns, value);                    //��������������ջ
            if (flag) {
                printf(" ");
                break;
            }
        }
    }
    while (!isEmptySOpt(os)) {                      //��������ջ�еķ��Ŷ�ȡ��
        char topEle = popEleTopSOpt(os);            
        printf("%c ", topEle);                      
        double v1 = popEleTopSNum(ns);
        double v2 = popEleTopSNum(ns);
        double result = caculatorTwo(v1, v2, topEle);//ÿ��ȡ������ֱ�Ӽ���
        pushSNum(ns, result);
    }

    
    printf("\n= %.2lf", popEleTopSNum(ns));
    return 1;
}




//���˵�
void menu() {
    printf("+-------------���׼�����-----------------+\n");
    printf("|                                        |\n");
    printf("|		[1]����                  |\n");
    printf("|		[2]�˳�			 |\n");
    printf("|                                        |\n");
    printf("+----------------------------------------+\n");
    printf("�������Ӧ���֣�");
}




//����ջ����Ԫ��
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


//�������ȼ�
int opt(char signal) {
    if (signal == '+' || signal == '-') {
        return 1;
    }
    else if (signal == '*' || signal == '/') {
        return 2;
    }
}



//������ջ

//��ʼ��
void initSNum(NumberStack* ns) {
    ns->top = -1;
}

//��ջ
int pushSNum(NumberStack* ns, double num) {
    if (ns->top < MAX_SIZE - 1) {
        ns->data[(ns->top) + 1] = num;
        ns->top++;
        return 1;
    }
    return 0;
}

//��ջ
int popSNum(NumberStack* ns) {
    if (ns->top == -1) {
        return 0;
    }

    ns->data[ns->top] = '\0';
    ns->top--;
    return 1;
}

//��ȡ��ϵ�Ԫ�أ�����ջ��
double getEleTopSNum(NumberStack* ns) {
    if (ns->top == -1) {
        return '\0';
    }
    double n = ns->data[ns->top];
    return n;
}

//��ȡ��ϵ�Ԫ�أ���ջ��
double popEleTopSNum(NumberStack* ns) {
    if (ns->top == -1) {
        return '\0';
    }
    double n = ns->data[ns->top];
    ns->data[ns->top] = '\0';
    ns->top--;
    return n;
}

//�ж��Ƿ�Ϊ��
int isEmptySNum(NumberStack* ns) {
    if (ns->top >= 0)
        return 0;
    return 1;
}






//������ջ

//��ʼ��
void initSOpt(OperationStack* os) {
    os->top = -1;
}

//��ջ
int pushSOpt(OperationStack* os, char opt) {
    if (os->top < MAX_SIZE - 1) {
        os->data[(os->top) + 1] = opt;
        os->top++;
        return 1;
    }
    return 0;
}

//��ջ
int popSOpt(OperationStack* os) {
    if (os->top == -1) {
        return 0;
    }

    os->data[os->top] = '\0';
    os->top--;
    return 1;
}

//��ȡ��ϵ�Ԫ�أ�����ջ��
char getEleTopSOpt(OperationStack* os) {
    if (os->top == -1) {
        return '\0';
    }
    char e = os->data[os->top];
    return e;
}

//��ȡ��ϵ�Ԫ�أ���ջ��
char popEleTopSOpt(OperationStack* os) {
    if (os->top == -1) {
        return '\0';
    }
    char e = os->data[os->top];
    os->data[os->top] = '\0';
    os->top--;
    return e;
}

//�ж��Ƿ�Ϊ��
int isEmptySOpt(OperationStack* os) {
    if (os->top >= 0) {
        return 0;
    }
    return 1;
}