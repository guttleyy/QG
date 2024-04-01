#define _CRT_SECURE_NO_WARNINGS 1	//解决不能直接使用scanf的问题
#pragma warning(disable:6031)		//解决scanf返回值被忽略的问题

#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


int main() {
	menuControl();
	return 0;
}

void menuControl() {
	int choice;
	long long int size = 0;
	int k;
	int* arr = NULL;
	char* filename = NULL;
	// 使用当前时间作为种子
	srand(time(NULL));//保证每次随机生成数组是不同的
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
			while(1){
				printf("请输入需要生成的数据量:");
				scanf("%lld", &size);
				if (size > 0) {
					break;
				}
				printf("请输入一个正整数!\n");
				printf("请重新输入!\n");
				system("pause");
				system("cls");
			}
			arr = (int*)malloc(size * sizeof(int));
			if (arr == NULL) {
				printf("内存分配失败！\n");
			}
			createRandomArr(arr, size);
			filename = "testdata.txt";
			saveArrayToFile(arr, size, filename);
			break;
		case 2:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			readArrayFromFile(arr, size, filename);
			printf("数据已读取!\n");
			break;
		case 3:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			if (arr == NULL) {
				printf("请先读取文件数据!\n");
				break;
			}
			InsertSort(arr, size);
			printf("排序完成!\n");
			break;
		case 4:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			if (arr == NULL) {
				printf("请先读取文件数据!\n");
				break;
			}
			MergeSortIn(arr, size);
			printf("排序完成!\n");
			break;
		case 5:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			if (arr == NULL) {
				printf("请先读取文件数据!\n");
				break;
			}
			QuickSort(arr, 0, size - 1);
			printf("排序完成!\n");
			break;
		case 6:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			if (arr == NULL) {
				printf("请先读取文件数据!\n");
				break;
			}
			CountSort(arr, size);
			printf("排序完成!\n");
			break;
		case 7:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			if (arr == NULL) {
				printf("请先读取文件数据!\n");
				break;
			}
			RadixCountSort(arr, size);
			printf("排序完成!\n");
			break;
		case 8:
			if (size == 0) {
				printf("请先保存数据!\n");
				break;
			}
			if (arr == NULL) {
				printf("数组为空!\n");
				break;
			}
			PrintArr(arr, size);
			break;
		case 9:
			printf("测试一：\n大数据量下\n");
			long long int dataSize[] = { 10000,50000,200000 };
			for (int i = 0; i < 3; i++) {
				test1(dataSize[i]);
			}
			printf("\n");
			break;
		case 10:
			printf("测试二：\n大量小数据量下\n");
			test2(100);
			break;
		case 11:
			size = 10;
			arr = (int*)malloc(size * sizeof(int));
			if (arr == NULL) {
				printf("内存分配失败！\n");
			}
			getColourArr(arr, size);
			PrintArr(arr, size);
			ColourSort(arr, size);
			printf("排序完成!\n");
			PrintArr(arr, size);
			break;
		case 12:
			while (1) {
				printf("请输入需要生成的数据量(1-1000):");
				scanf("%lld", &size);
				if (size > 0 && size <= 1000) {
					break;
				}
				printf("请输入一个 1-1000 的正整数!\n");
				printf("请重新输入!\n");
				system("pause");
				system("cls");
			}
			arr = (int*)malloc(size * sizeof(int));
			if (arr == NULL) {
				printf("内存分配失败！\n");
			}
			createRandomArr(arr, size);
			printf("数组为:\n");
			PrintArr(arr, size);
			while (1) {
				printf("请输入需要第几小的数:");
				scanf("%d", &k);
				if (k > 0 && k <= size) {
					break;
				}
				printf("请输入 1-%d 的正整数!\n",size);
				printf("请重新输入!\n");
				system("pause");
				system("cls");
			}
			int result = QuickSelect(arr, 0, size - 1, k);
			printf("数组中第 %d 小的数是%d\n", k, result);
			break;
		case 13:
			exit(0);
		default:
			printf("不存在该数字，请重新输入!\n");
		}
		system("pause");	//暂停
	}

}


void menu() {
	printf("+------------排序-----------+\n");
	printf("|	[1]生成随机数据     |\n");
	printf("|	[2]读取文件数据     |\n");
	printf("|	[3]插入排序	    |\n");
	printf("|	[4]归并排序	    |\n");
	printf("|	[5]快速排序	    |\n");
	printf("|	[6]计数排序	    |\n");
	printf("|	[7]基数排序	    |\n");
	printf("|	[8]展示数据	    |\n");
	printf("|	[9]大数据量测试	    |\n");
	printf("|	[10]小数据量测试    |\n");
	printf("|	[11]颜色排序	    |\n");
	printf("|	[12]查找第k小的数   |\n");
	printf("|	[13]退出	    |\n");
	printf("+---------------------------+\n");
	//printf("\n");
	printf("请输入对应数字：");
}



// 将数组保存到文件
void saveArrayToFile(int arr[], int n, char* filename) {
	FILE* file = fopen(filename, "w+");
	if (file == NULL) {
		printf("无法打开!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fprintf(file, "%d\n", arr[i]);
	}
	printf("数据已保存到文件:%s\n", filename);
	fclose(file);
}

// 从文件读取数据到数组
void readArrayFromFile(int arr[], int n, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fscanf(file, "%d", &arr[i]);
	}

	fclose(file);
}


//测试一
//输出上述排序函数在不同的大数据量下的用时，有三个层次(10000、50000、200000)
void test1(long long int size) {

	int* arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		printf("内存分配失败！\n");
	}

	//// 使用当前时间作为种子
	//srand(time(NULL));//保证每次随机生成数组是不同的

	//插入排序
	createRandomArr(arr, size);
	clock_t startIS = clock();
	InsertSort(arr, size);
	clock_t endIS = clock();
	double timeIS = (double)(endIS - startIS) / CLOCKS_PER_SEC;
	printf("InsertSort took %.6f seconds to sort %d data\n",timeIS,size);

	//归并排序
	createRandomArr(arr, size);
	clock_t startMS = clock();
	MergeSortIn(arr, size);
	clock_t endMS = clock();
	double timeMS = (double)(endMS - startMS) / CLOCKS_PER_SEC;
	printf("MergeSort took %.6f seconds to sort %d data\n", timeMS, size);

	
	//快速排序
	createRandomArr(arr, size);
	clock_t startQS = clock();
	QuickSort(arr, 0, size - 1);
	clock_t endQS = clock();
	double timeQS = (double)(endQS - startQS) / CLOCKS_PER_SEC;
	printf("QuickSort took %.6f seconds to sort %d data\n", timeQS, size);
	

	//计数排序
	createRandomArr(arr, size);
	clock_t startCS = clock();
	CountSort(arr, size);
	clock_t endCS = clock();
	double timeCS = (double)(endCS - startCS) / CLOCKS_PER_SEC;
	printf("CountSort took %.6f seconds to sort %d data\n", timeCS, size);

	//基数计数排序
	createRandomArr(arr, size);
	clock_t startRS = clock();
	RadixCountSort(arr, size);
	clock_t endRS = clock();
	double timeRS = (double)(endRS - startRS) / CLOCKS_PER_SEC;
	printf("RadixCountSort took %.6f seconds to sort %d data\n", timeRS, size);

	printf("\n");
}


//测试二
//输出上述排序函数在大量小数据量下的排序用时(如100个数据*100k次排序)
void test2(long long int size) {

	int* arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		printf("内存分配失败！\n");
	}

	//// 使用当前时间作为种子
	//srand(time(NULL));//保证每次随机生成数组是不同的

	double timeIS=0.0,timeMS=0.0, timeQS=0.0, timeCS=0.0, timeRS=0.0;
	int repeatTime = 100000;
	for (int i = 0; i < repeatTime; i++) {
		//插入排序
		createRandomArr(arr, size);
		clock_t startIS = clock();
		InsertSort(arr, size);
		clock_t endIS = clock();
		timeIS += (double)(endIS - startIS) / CLOCKS_PER_SEC;
		

		//归并排序
		createRandomArr(arr, size);
		clock_t startMS = clock();
		MergeSortIn(arr, size);
		clock_t endMS = clock();
		timeMS += (double)(endMS - startMS) / CLOCKS_PER_SEC;
		


		//快速排序
		createRandomArr(arr, size);
		clock_t startQS = clock();
		QuickSort(arr, 0, size - 1);
		clock_t endQS = clock();
		timeQS += (double)(endQS - startQS) / CLOCKS_PER_SEC;
		


		//计数排序
		createRandomArr(arr, size);
		clock_t startCS = clock();
		CountSort(arr, size);
		clock_t endCS = clock();
		timeCS += (double)(endCS - startCS) / CLOCKS_PER_SEC;
		

		//基数计数排序
		createRandomArr(arr, size);
		clock_t startRS = clock();
		RadixCountSort(arr, size);
		clock_t endRS = clock();
		timeRS += (double)(endRS - startRS) / CLOCKS_PER_SEC;
		
	}


	printf("InsertSort took %.6f seconds to sort %d data %d times\n", timeIS, size, repeatTime);
	printf("MergeSort took %.6f seconds to sort %d data %d times\n", timeMS, size, repeatTime);
	printf("QuickSort took %.6f seconds to sort %d data %d times\n", timeQS, size, repeatTime);
	printf("CountSort took %.6f seconds to sort %d data %d times\n", timeCS, size, repeatTime);
	printf("RadixCountSort took %.6f seconds to sort %d data %d times\n", timeRS, size, repeatTime);
}




//生成随机数组
void createRandomArr(int arr[], long long int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 1000;	//0-999的整数
	}
}


//插入排序
void InsertSort(int arr[], long long int size) {
	int i, j;
	for (i = 1; i < size; i++) {
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			else {
				break;
			}
		}
	}
}

//归并排序
//入口
void MergeSortIn(int arr[], long long int size) {
	//创建临时数组，用于合并
	int* tempArr = (int*)malloc(size * sizeof(int));
	if (tempArr == NULL) {
		printf("内存分配失败！\n");
	}
	else {
		MergeSort(arr, tempArr, 0, size - 1);
		free(tempArr);
	}
}

//递归划分
void MergeSort(int arr[], int tempArr[], long long int left, long long int right) {
	
	//元素还有两个及以上，接着划分
	if (left < right) {
		//找中间点
		int mid = (left + right) / 2;
		//递归划分左半边
		MergeSort(arr, tempArr, left, mid);
		//递归划分右半边
		MergeSort(arr, tempArr, mid + 1, right);
		//合并排序好的部分
		Merge(arr, tempArr, left, mid, right);
	}
}

//合并
void Merge(int arr[], int tempArr[], long long int left, long long int mid, long long int right) {
	int l = left;
	int r = mid + 1;
	int i = left;

	//合并
	while (l <= mid && r <= right) {
		if (arr[l] < arr[r]) {
			tempArr[i++] = arr[l++];
		}
		else {
			tempArr[i++] = arr[r++];
		}
	}

	//右半区合并完，左半区还有元素
	while (r > right && l <= mid) {
		tempArr[i++] = arr[l++];
	}

	//左半区合并完，右半区还有元素
	while (l > mid && r <= right) {
		tempArr[i++] = arr[r++];
	}

	//将临时数组复制到原数组
	while (left <= right) {
		arr[left] = tempArr[left];
		left++;
	}
}

//快速排序（递归）
void QuickSort(int arr[], long long int start, long long int end) {
	if (start >= end) {
		return;
	}

	long long int i = start, j = end;
	int baseNumber = arr[(start + end) / 2]; // 选择中间元素作为基准数

	// 划分数组
	while (i <= j) {

		// 从右向左找到第一个小于等于基准数的值
		while (arr[j] > baseNumber) {
			j--;
		}

		// 从左向右找到第一个大于等于基准数的值
		while (arr[i] < baseNumber) {
			i++;
		}
		
		// 交换两个值
		if (i <= j) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}

	// 递归排序左右两个子数组
	QuickSort(arr, start, j);
	QuickSort(arr, i, end);
}




//计数排序(优化)
//普通计数排序局限性过大：
//	1.不能统计负数
//  2.空间浪费
//优化：
//	1.找到最大值与最小值
//	2.相对映射：计数的时候，将每个数据减去最小值作为数组下标，还原时，加上最小值即可

void CountSort(int arr[], long long int size) {
	int i = 0;
	int max = GetMax(arr, size);
	int min = GetMin(arr, size);

	//将范围锁定在最大值与最小值之间
	//解决空间浪费的问题
	int range = max - min + 1;
	
	//为计数数组分配空间
	int* countArr = (int*)malloc(sizeof(int) * range);
	if (countArr == NULL) {
		printf("内存分配失败!\n");
		return;
	}
	
	for (i = 0; i < range; i++) {
		countArr[i] = 0;			//将计数数组的值赋为0
	}
	for (i = 0; i < size; i++) {
		countArr[arr[i] - min]++;	//相对映射，解决负数问题
	}

	//不解决稳定性问题，可以直接取出
	/*
		int j = 0;
		for (int i = 0; i < range; i++){
			while (countArr[i]--){
				arr[j] = i + min;
				j++;
			}
		}
		free(countArr);
	*/
	
	//累加计数数组，用于解决计数排序的稳定性问题
	for (i = 1; i < range; i++) {
		countArr[i] += countArr[i - 1];
	}


	//临时数组
	int* tempArr = (int*)malloc(sizeof(int) * size);
	if (tempArr == NULL) {
		printf("内存分配失败!\n");
		free(countArr);
		return;
	}

	//倒序，将原数组的元素放到对应的位置
	for (i = size - 1; i >= 0; i--) {
		tempArr[--countArr[arr[i] - min]] = arr[i];
	}

	//将排序后的数组放回原数组
	for (i = 0; i < size; i++) {
		arr[i] = tempArr[i];
	}
	free(countArr);
	
}


//基数计数排序
void RadixCountSort(int arr[], long long int size) {
	int i;
	int exp = 1;
	int max = GetMax(arr, size);
	int digit = GetDigit(max);

	int* tempArr = (int*)malloc(sizeof(int) * size);
	if (tempArr == NULL) {
		printf("内存分配失败!\n");
		return;
	}

	while(max / exp > 0){ 
		int countArr[10] = { 0 };
		for (i = 0; i < size; i++) {
			countArr[(arr[i] / exp) % 10]++;
		}
		for (i = 1; i < 10; i++) {
			countArr[i] += countArr[i - 1];
		}
		for (i = size - 1; i >= 0; i--) {
			tempArr[--countArr[(arr[i] / exp) % 10]] = arr[i];
		}
		for (i = 0; i < size; i++) {
			arr[i] = tempArr[i];
		}
		exp *= 10;
	}
}

//获取位数
int GetDigit(int num) {
	int digit = 0;
	while (num > 0) {
		num = num / 10;
		digit++;
	}
	return digit;
}

//获取最大值
int GetMax(int arr[], long long int size) {
	int max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

//获取最小值
int GetMin(int arr[], long long int size) {
	int min = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

//打印数组
void PrintArr(int arr[], long long int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//获取颜色数组
void getColourArr(int arr[], int size) {
	// 使用当前时间作为种子
	srand(time(NULL));//保证每次随机生成数组是不同的
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 3;	//0-2的整数
	}
}

//应用题一：颜色排序
void ColourSort(int arr[], int size) {
	int p0 = 0;
	int p2 = size - 1;
	int p1 = 0;

	while (p1 <= p2) {
		if (arr[p1] == 0) {
			int temp = arr[p1];
			arr[p1] = arr[p0];
			arr[p0] = temp;
			p0++;
			p1++;
			//之所以在这要p1向后移动，是因为p0前的数据都是正确排序的位置
		}
		else if (arr[p1] == 2) {
			int temp = arr[p1];
			arr[p1] = arr[p2];
			arr[p2] = temp;
			p2--;
		}
		else {
			p1++;
		}
	}
}

//应用题二：在一个无序序列中找到第K小的数
//划分函数
int QuickSelect(int arr[], int start, int end,int k) {
	if (start == end && start == k - 1) {
		return arr[start];
	}
	else if (start < end) {
		int pivot = arr[start];
		int i = start, j = end;
		while (i != j) {
			while (j > i && arr[j] >= pivot) {
				j--;
			}
			arr[i] = arr[j];
			while (i < j && arr[i] <= pivot) {
				i++;
			}
			arr[j] = arr[i];
		}
		arr[i] = pivot;
		if (i == k - 1) {
			return arr[i];
		}
		else if (i < k - 1) {
			return QuickSelect(arr, i + 1, end, k);
		}
		else {
			return QuickSelect(arr, start, i - 1, k);
		}
	}

}


