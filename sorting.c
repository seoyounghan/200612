/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>//입출력 전처리기
#include <stdlib.h>//입출력 함수 포함 전처리기
#include <time.h>//시간 관련 함수 포함하는 전처리기

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE	//배열의 사이즈와 hash table 사이즈 동일

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);	//초기화 함수
int freeArray(int *a);	//할당 해제 함수
void printArray(int *a);	//array해제 함수

int selectionSort(int *a);	//
int insertionSort(int *a);	//
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));	//랜덤값 사용을 위해 선언

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)//초기화 함수
{
	int *temp = NULL;//임시로 담을 값

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)//배열 해제
{
	if(a != NULL)
		free(a);//a를 동적 할당 해제 해준다
	return 0;
}

void printArray(int *a)//a를 프린팅
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}//a가 아무것도 없는 경우 프린트 할 수 없다고 알려줌
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);//배열의 인덱스값 프린팅
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);//배열의 원소들 프린팅
	printf("\n");
}


int selectionSort(int *a)//선택 정렬
{//최소값 비교를 통해 인덱스0부터 순서대로 최소값을 넣어줌
	int min;//가장 작은 값
	int minindex;//가장 작은 값의 인덱스
	int i, j;//반복문에서 사용

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬 전 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;//i부터 대입
		min = a[i];//가장 작은 값 임의로 지정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])//만약에 최소값보다 더 작은 값이 존재하면
			{
				min = a[j];//최소값 변경
				minindex = j;//인덱스도 변경
			}
		}
		a[minindex] = a[i];//최소값 자리에 있던 값 변경
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬된 a 프린팅
	return 0;
}

int insertionSort(int *a)//삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬되기 전 a 프린팅

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];//원소값 저장
		j = i;//인덱스 값 저장
		while (a[j-1] > t && j > 0)//t가 a의 원소보다 큰 동안 반복
		{
			a[j] = a[j-1];//j번째 값과 그 전 원소의 값을 변경
			j--;//j
		}
		a[j] = t;//다음값으로 넘겨줌
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬된 a값 프린팅

	return 0;
}

int bubbleSort(int *a)//버블 정렬
{//양 옆 값 확인을 통해 정렬해나감
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//a 프린팅

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j])//정렬이 되지 않은 경우
			{//j-1과j의 원소 값 변경을 해서 정렬해줌
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}//반복문을 이중으로 사용해서 모든 값이 다 비교될 수 있도록 해줌

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬된a 프린팅

	return 0;
}

int shellSort(int *a)//셸 정렬
{//2차원 배열을 통해 정렬
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬되지 않은 a 프린팅

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//h는 반씩 나누어짐
	{
		for (i = 0; i < h; i++)//h번 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)//인덱스는 h-1보다 크고 값은 v보다 큰 경우 반복
				{
					a[k] = a[k-h];//k-h값과 변경
					k -= h;//인덱스 변경
				}
				a[k] = v;//v 값 넣어줌
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬이 된 a 프린팅

	return 0;
}

int quickSort(int *a, int n)//퀵 정렬
{//피봇을 기준으로 정렬
	int v, t;
	int i, j;

	if (n > 1)//원소가 존재 하는 경우
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)//무한반복
		{
			while(a[++i] < v);//i를 늘리며 v보다 작은 경우 반복
			while(a[--j] > v);//j를 줄이면서 v보다 큰 경우 반복

			if (i >= j) break;//만약 i가 j보다 커지면 피봇 기준을 지키기 위해 멈춘다.
			t = a[i];//a[i]와 a[j]값 변경
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];//a[i]와 a[n-1]값 변경
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);//퀵 정렬을 남은 원소 대상으로 해줌
		quickSort(a+i+1, n-i-1);//퀵정렬을 피봇을 변경해서 반복한다
	}


	return 0;
}

int hashCode(int key) {//해시 코드 리턴 함수
   return key % MAX_HASH_TABLE_SIZE;//키값을 반환
}

int hashing(int *a, int **ht)//헤슁 함수
{
	int *hashtable = NULL;//임시로 널값을 넣음

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;//해시테이블 값 -1로 선언

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;//키값과 코드값 인덱스값 -1로 선언
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];//키값을 받음
		hashcode = hashCode(key);//해쉬 코드값 설정
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)//해쉬코드에 대한 키값이 설정되지 않았으면
		{
			hashtable[hashcode] = key;//설정해줌
		} else 	{

			index = hashcode;//인덱스 변경

			while(hashtable[index] != -1)//값이 없으면 반복
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//인덱스 값을 하나씩 늘리며 넣어줌
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;//키값 할당
		}
	}

	return 0;
}

int search(int *ht, int key)//키값을 이용해 찾기
{
	int index = hashCode(key);//해쉬코드를 인덱스 값으로 받음

	if(ht[index] == key)//키값과 배열 값이 같으면
		return index;//인덱스값 리턴

	while(ht[++index] != key)//키값과 배열값이 다르면 반복
	{
		index = index % MAX_HASH_TABLE_SIZE;//인덱스 값 할당해줌
	}
	return index;//인덱스 리턴 
}



