#define _CRT_SECURE_NO_WARNINGS 1	//�������ֱ��ʹ��scanf������
#pragma warning(disable:6031)		//���scanf����ֵ�����Ե�����

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
	// ʹ�õ�ǰʱ����Ϊ����
	srand(time(NULL));//��֤ÿ��������������ǲ�ͬ��
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
			while(1){
				printf("��������Ҫ���ɵ�������:");
				scanf("%lld", &size);
				if (size > 0) {
					break;
				}
				printf("������һ��������!\n");
				printf("����������!\n");
				system("pause");
				system("cls");
			}
			arr = (int*)malloc(size * sizeof(int));
			if (arr == NULL) {
				printf("�ڴ����ʧ�ܣ�\n");
			}
			createRandomArr(arr, size);
			filename = "testdata.txt";
			saveArrayToFile(arr, size, filename);
			break;
		case 2:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			readArrayFromFile(arr, size, filename);
			printf("�����Ѷ�ȡ!\n");
			break;
		case 3:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			if (arr == NULL) {
				printf("���ȶ�ȡ�ļ�����!\n");
				break;
			}
			InsertSort(arr, size);
			printf("�������!\n");
			break;
		case 4:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			if (arr == NULL) {
				printf("���ȶ�ȡ�ļ�����!\n");
				break;
			}
			MergeSortIn(arr, size);
			printf("�������!\n");
			break;
		case 5:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			if (arr == NULL) {
				printf("���ȶ�ȡ�ļ�����!\n");
				break;
			}
			QuickSort(arr, 0, size - 1);
			printf("�������!\n");
			break;
		case 6:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			if (arr == NULL) {
				printf("���ȶ�ȡ�ļ�����!\n");
				break;
			}
			CountSort(arr, size);
			printf("�������!\n");
			break;
		case 7:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			if (arr == NULL) {
				printf("���ȶ�ȡ�ļ�����!\n");
				break;
			}
			RadixCountSort(arr, size);
			printf("�������!\n");
			break;
		case 8:
			if (size == 0) {
				printf("���ȱ�������!\n");
				break;
			}
			if (arr == NULL) {
				printf("����Ϊ��!\n");
				break;
			}
			PrintArr(arr, size);
			break;
		case 9:
			printf("����һ��\n����������\n");
			long long int dataSize[] = { 10000,50000,200000 };
			for (int i = 0; i < 3; i++) {
				test1(dataSize[i]);
			}
			printf("\n");
			break;
		case 10:
			printf("���Զ���\n����С��������\n");
			test2(100);
			break;
		case 11:
			size = 10;
			arr = (int*)malloc(size * sizeof(int));
			if (arr == NULL) {
				printf("�ڴ����ʧ�ܣ�\n");
			}
			getColourArr(arr, size);
			PrintArr(arr, size);
			ColourSort(arr, size);
			printf("�������!\n");
			PrintArr(arr, size);
			break;
		case 12:
			while (1) {
				printf("��������Ҫ���ɵ�������(1-1000):");
				scanf("%lld", &size);
				if (size > 0 && size <= 1000) {
					break;
				}
				printf("������һ�� 1-1000 ��������!\n");
				printf("����������!\n");
				system("pause");
				system("cls");
			}
			arr = (int*)malloc(size * sizeof(int));
			if (arr == NULL) {
				printf("�ڴ����ʧ�ܣ�\n");
			}
			createRandomArr(arr, size);
			printf("����Ϊ:\n");
			PrintArr(arr, size);
			while (1) {
				printf("��������Ҫ�ڼ�С����:");
				scanf("%d", &k);
				if (k > 0 && k <= size) {
					break;
				}
				printf("������ 1-%d ��������!\n",size);
				printf("����������!\n");
				system("pause");
				system("cls");
			}
			int result = QuickSelect(arr, 0, size - 1, k);
			printf("�����е� %d С������%d\n", k, result);
			break;
		case 13:
			exit(0);
		default:
			printf("�����ڸ����֣�����������!\n");
		}
		system("pause");	//��ͣ
	}

}


void menu() {
	printf("+------------����-----------+\n");
	printf("|	[1]�����������     |\n");
	printf("|	[2]��ȡ�ļ�����     |\n");
	printf("|	[3]��������	    |\n");
	printf("|	[4]�鲢����	    |\n");
	printf("|	[5]��������	    |\n");
	printf("|	[6]��������	    |\n");
	printf("|	[7]��������	    |\n");
	printf("|	[8]չʾ����	    |\n");
	printf("|	[9]������������	    |\n");
	printf("|	[10]С����������    |\n");
	printf("|	[11]��ɫ����	    |\n");
	printf("|	[12]���ҵ�kС����   |\n");
	printf("|	[13]�˳�	    |\n");
	printf("+---------------------------+\n");
	//printf("\n");
	printf("�������Ӧ���֣�");
}



// �����鱣�浽�ļ�
void saveArrayToFile(int arr[], int n, char* filename) {
	FILE* file = fopen(filename, "w+");
	if (file == NULL) {
		printf("�޷���!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fprintf(file, "%d\n", arr[i]);
	}
	printf("�����ѱ��浽�ļ�:%s\n", filename);
	fclose(file);
}

// ���ļ���ȡ���ݵ�����
void readArrayFromFile(int arr[], int n, char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("�޷���!\n");
		exit(1);
	}

	for (int i = 0; i < n; i++) {
		fscanf(file, "%d", &arr[i]);
	}

	fclose(file);
}


//����һ
//��������������ڲ�ͬ�Ĵ��������µ���ʱ�����������(10000��50000��200000)
void test1(long long int size) {

	int* arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
	}

	//// ʹ�õ�ǰʱ����Ϊ����
	//srand(time(NULL));//��֤ÿ��������������ǲ�ͬ��

	//��������
	createRandomArr(arr, size);
	clock_t startIS = clock();
	InsertSort(arr, size);
	clock_t endIS = clock();
	double timeIS = (double)(endIS - startIS) / CLOCKS_PER_SEC;
	printf("InsertSort took %.6f seconds to sort %d data\n",timeIS,size);

	//�鲢����
	createRandomArr(arr, size);
	clock_t startMS = clock();
	MergeSortIn(arr, size);
	clock_t endMS = clock();
	double timeMS = (double)(endMS - startMS) / CLOCKS_PER_SEC;
	printf("MergeSort took %.6f seconds to sort %d data\n", timeMS, size);

	
	//��������
	createRandomArr(arr, size);
	clock_t startQS = clock();
	QuickSort(arr, 0, size - 1);
	clock_t endQS = clock();
	double timeQS = (double)(endQS - startQS) / CLOCKS_PER_SEC;
	printf("QuickSort took %.6f seconds to sort %d data\n", timeQS, size);
	

	//��������
	createRandomArr(arr, size);
	clock_t startCS = clock();
	CountSort(arr, size);
	clock_t endCS = clock();
	double timeCS = (double)(endCS - startCS) / CLOCKS_PER_SEC;
	printf("CountSort took %.6f seconds to sort %d data\n", timeCS, size);

	//������������
	createRandomArr(arr, size);
	clock_t startRS = clock();
	RadixCountSort(arr, size);
	clock_t endRS = clock();
	double timeRS = (double)(endRS - startRS) / CLOCKS_PER_SEC;
	printf("RadixCountSort took %.6f seconds to sort %d data\n", timeRS, size);

	printf("\n");
}


//���Զ�
//��������������ڴ���С�������µ�������ʱ(��100������*100k������)
void test2(long long int size) {

	int* arr = (int*)malloc(size * sizeof(int));
	if (arr == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
	}

	//// ʹ�õ�ǰʱ����Ϊ����
	//srand(time(NULL));//��֤ÿ��������������ǲ�ͬ��

	double timeIS=0.0,timeMS=0.0, timeQS=0.0, timeCS=0.0, timeRS=0.0;
	int repeatTime = 100000;
	for (int i = 0; i < repeatTime; i++) {
		//��������
		createRandomArr(arr, size);
		clock_t startIS = clock();
		InsertSort(arr, size);
		clock_t endIS = clock();
		timeIS += (double)(endIS - startIS) / CLOCKS_PER_SEC;
		

		//�鲢����
		createRandomArr(arr, size);
		clock_t startMS = clock();
		MergeSortIn(arr, size);
		clock_t endMS = clock();
		timeMS += (double)(endMS - startMS) / CLOCKS_PER_SEC;
		


		//��������
		createRandomArr(arr, size);
		clock_t startQS = clock();
		QuickSort(arr, 0, size - 1);
		clock_t endQS = clock();
		timeQS += (double)(endQS - startQS) / CLOCKS_PER_SEC;
		


		//��������
		createRandomArr(arr, size);
		clock_t startCS = clock();
		CountSort(arr, size);
		clock_t endCS = clock();
		timeCS += (double)(endCS - startCS) / CLOCKS_PER_SEC;
		

		//������������
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




//�����������
void createRandomArr(int arr[], long long int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 1000;	//0-999������
	}
}


//��������
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

//�鲢����
//���
void MergeSortIn(int arr[], long long int size) {
	//������ʱ���飬���ںϲ�
	int* tempArr = (int*)malloc(size * sizeof(int));
	if (tempArr == NULL) {
		printf("�ڴ����ʧ�ܣ�\n");
	}
	else {
		MergeSort(arr, tempArr, 0, size - 1);
		free(tempArr);
	}
}

//�ݹ黮��
void MergeSort(int arr[], int tempArr[], long long int left, long long int right) {
	
	//Ԫ�ػ������������ϣ����Ż���
	if (left < right) {
		//���м��
		int mid = (left + right) / 2;
		//�ݹ黮������
		MergeSort(arr, tempArr, left, mid);
		//�ݹ黮���Ұ��
		MergeSort(arr, tempArr, mid + 1, right);
		//�ϲ�����õĲ���
		Merge(arr, tempArr, left, mid, right);
	}
}

//�ϲ�
void Merge(int arr[], int tempArr[], long long int left, long long int mid, long long int right) {
	int l = left;
	int r = mid + 1;
	int i = left;

	//�ϲ�
	while (l <= mid && r <= right) {
		if (arr[l] < arr[r]) {
			tempArr[i++] = arr[l++];
		}
		else {
			tempArr[i++] = arr[r++];
		}
	}

	//�Ұ����ϲ��꣬���������Ԫ��
	while (r > right && l <= mid) {
		tempArr[i++] = arr[l++];
	}

	//������ϲ��꣬�Ұ�������Ԫ��
	while (l > mid && r <= right) {
		tempArr[i++] = arr[r++];
	}

	//����ʱ���鸴�Ƶ�ԭ����
	while (left <= right) {
		arr[left] = tempArr[left];
		left++;
	}
}

//�������򣨵ݹ飩
void QuickSort(int arr[], long long int start, long long int end) {
	if (start >= end) {
		return;
	}

	long long int i = start, j = end;
	int baseNumber = arr[(start + end) / 2]; // ѡ���м�Ԫ����Ϊ��׼��

	// ��������
	while (i <= j) {

		// ���������ҵ���һ��С�ڵ��ڻ�׼����ֵ
		while (arr[j] > baseNumber) {
			j--;
		}

		// ���������ҵ���һ�����ڵ��ڻ�׼����ֵ
		while (arr[i] < baseNumber) {
			i++;
		}
		
		// ��������ֵ
		if (i <= j) {
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}

	// �ݹ�������������������
	QuickSort(arr, start, j);
	QuickSort(arr, i, end);
}




//��������(�Ż�)
//��ͨ������������Թ���
//	1.����ͳ�Ƹ���
//  2.�ռ��˷�
//�Ż���
//	1.�ҵ����ֵ����Сֵ
//	2.���ӳ�䣺������ʱ�򣬽�ÿ�����ݼ�ȥ��Сֵ��Ϊ�����±꣬��ԭʱ��������Сֵ����

void CountSort(int arr[], long long int size) {
	int i = 0;
	int max = GetMax(arr, size);
	int min = GetMin(arr, size);

	//����Χ���������ֵ����Сֵ֮��
	//����ռ��˷ѵ�����
	int range = max - min + 1;
	
	//Ϊ�����������ռ�
	int* countArr = (int*)malloc(sizeof(int) * range);
	if (countArr == NULL) {
		printf("�ڴ����ʧ��!\n");
		return;
	}
	
	for (i = 0; i < range; i++) {
		countArr[i] = 0;			//�����������ֵ��Ϊ0
	}
	for (i = 0; i < size; i++) {
		countArr[arr[i] - min]++;	//���ӳ�䣬�����������
	}

	//������ȶ������⣬����ֱ��ȡ��
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
	
	//�ۼӼ������飬���ڽ������������ȶ�������
	for (i = 1; i < range; i++) {
		countArr[i] += countArr[i - 1];
	}


	//��ʱ����
	int* tempArr = (int*)malloc(sizeof(int) * size);
	if (tempArr == NULL) {
		printf("�ڴ����ʧ��!\n");
		free(countArr);
		return;
	}

	//���򣬽�ԭ�����Ԫ�طŵ���Ӧ��λ��
	for (i = size - 1; i >= 0; i--) {
		tempArr[--countArr[arr[i] - min]] = arr[i];
	}

	//������������Ż�ԭ����
	for (i = 0; i < size; i++) {
		arr[i] = tempArr[i];
	}
	free(countArr);
	
}


//������������
void RadixCountSort(int arr[], long long int size) {
	int i;
	int exp = 1;
	int max = GetMax(arr, size);
	int digit = GetDigit(max);

	int* tempArr = (int*)malloc(sizeof(int) * size);
	if (tempArr == NULL) {
		printf("�ڴ����ʧ��!\n");
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

//��ȡλ��
int GetDigit(int num) {
	int digit = 0;
	while (num > 0) {
		num = num / 10;
		digit++;
	}
	return digit;
}

//��ȡ���ֵ
int GetMax(int arr[], long long int size) {
	int max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

//��ȡ��Сֵ
int GetMin(int arr[], long long int size) {
	int min = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

//��ӡ����
void PrintArr(int arr[], long long int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

//��ȡ��ɫ����
void getColourArr(int arr[], int size) {
	// ʹ�õ�ǰʱ����Ϊ����
	srand(time(NULL));//��֤ÿ��������������ǲ�ͬ��
	for (int i = 0; i < size; i++) {
		arr[i] = rand() % 3;	//0-2������
	}
}

//Ӧ����һ����ɫ����
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
			//֮��������Ҫp1����ƶ�������Ϊp0ǰ�����ݶ�����ȷ�����λ��
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

//Ӧ���������һ�������������ҵ���KС����
//���ֺ���
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


