
//��������
void InsertSort(int arr[], long long int size);


//�鲢����
//���
void MergeSortIn(int arr[], long long int size);
//�ݹ黮��
void MergeSort(int arr[], int tempArr[], long long int left, long long int right);
//�ϲ�
void Merge(int arr[], int tempArr[], long long int left, long long int mid, long long int right);


//�������򣨵ݹ飩
void QuickSort(int arr[], long long int start, long long int end);


//��������
void CountSort(int arr[], long long int size);


//������������
void RadixCountSort(int arr[], long long int size);

//��ȡλ��
int GetDigit(int num);

//��ȡ���ֵ
int GetMax(int arr[], long long int size);
//��ȡ��Сֵ
int GetMin(int arr[], long long int size);

//�����������
void createRandomArr(int arr[], long long int size);

//��ӡ����
void PrintArr(int arr[], long long int size);

//����һ
//��������������ڲ�ͬ�Ĵ��������µ���ʱ�����������(10000��50000��200000)
void test1(long long int size);

//���Զ�
//��������������ڴ���С�������µ�������ʱ(��100������*100k������)
void test2(long long int size);

// �����鱣�浽�ļ�
void saveArrayToFile(int arr[], int n, char* filename);
// ���ļ���ȡ���ݵ�����
void readArrayFromFile(int arr[], int n, char* filename);

//���˵�
void menu();

void menuControl();


//��ȡ��ɫ����
void getColourArr(int arr[], int size);

//Ӧ����һ����ɫ����
void ColourSort(int arr[], int size);

//Ӧ���������һ�������������ҵ���KС����
// �������������ҵ��� k С����
int QuickSelect(int arr[], int start, int end, int k);