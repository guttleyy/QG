#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAX_SIZE 100

//��������˳��ջ


//������ջ
typedef struct {
    double data[MAX_SIZE];
    int top;
} NumberStack;

void initSNum(NumberStack* ns);//��ʼ��
int pushSNum(NumberStack* ns, double num);//��ջ
int popSNum(NumberStack* ns);//��ջ
double getEleTopSNum(NumberStack* ns);//��ȡ��ϵ�Ԫ�أ�����ջ��
double popEleTopSNum(NumberStack* ns);//��ȡ��ϵ�Ԫ�أ���ջ��
int isEmptySNum(NumberStack* ns);//�ж��Ƿ�Ϊ��


//������ջ
typedef struct {
    char data[MAX_SIZE];
    int top;
} OperationStack;

void initSOpt(OperationStack* os);//��ʼ��
int pushSOpt(OperationStack* os, char opt);//��ջ
int popSOpt(OperationStack* os);//��ջ
char getEleTopSOpt(OperationStack* os);//��ȡ��ϵ�Ԫ�أ�����ջ��
char popEleTopSOpt(OperationStack* os);//��ȡ��ϵ�Ԫ�أ���ջ��
int isEmptySOpt(OperationStack* os);//�ж��Ƿ�Ϊ��


//�������صĺ���
int opt(char signal);//�������ȼ�
double caculatorTwo(double v1, double v2, char signal);//����ջ����Ԫ��
int valid(char express[]);//���ʽ�Ϸ����ж�

//���ļ��㺯��
int cacul(OperationStack* os, NumberStack* ns);//���������׺���ʽת���ɺ�׺���ʽ��������

void menu();//�˵�




#endif 