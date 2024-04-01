
//插入排序
void InsertSort(int arr[], long long int size);


//归并排序
//入口
void MergeSortIn(int arr[], long long int size);
//递归划分
void MergeSort(int arr[], int tempArr[], long long int left, long long int right);
//合并
void Merge(int arr[], int tempArr[], long long int left, long long int mid, long long int right);


//快速排序（递归）
void QuickSort(int arr[], long long int start, long long int end);


//计数排序
void CountSort(int arr[], long long int size);


//基数计数排序
void RadixCountSort(int arr[], long long int size);

//获取位数
int GetDigit(int num);

//获取最大值
int GetMax(int arr[], long long int size);
//获取最小值
int GetMin(int arr[], long long int size);

//生成随机数组
void createRandomArr(int arr[], long long int size);

//打印数组
void PrintArr(int arr[], long long int size);

//测试一
//输出上述排序函数在不同的大数据量下的用时，有三个层次(10000、50000、200000)
void test1(long long int size);

//测试二
//输出上述排序函数在大量小数据量下的排序用时(如100个数据*100k次排序)
void test2(long long int size);

// 将数组保存到文件
void saveArrayToFile(int arr[], int n, char* filename);
// 从文件读取数据到数组
void readArrayFromFile(int arr[], int n, char* filename);

//主菜单
void menu();

void menuControl();


//获取颜色数组
void getColourArr(int arr[], int size);

//应用题一：颜色排序
void ColourSort(int arr[], int size);

//应用题二：在一个无序序列中找到第K小的数
// 在无序序列中找到第 k 小的数
int QuickSelect(int arr[], int start, int end, int k);