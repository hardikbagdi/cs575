#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define DEBUG
int doVisualization = -1;


int compare(int i,int j){
	if(i < j)
		return 1;
	return 0;
}

void swap(int* arr, int i, int j){
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void printArray(int *arr, int size){
	validateSortingInputs(arr,size);
	int i=0;
	printf("\n");
	for(i=0 ; i<size ; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}
void printArrayVisualization(int* arr, int size){
	validateSortingInputs(arr,size);
	int i=0;
	int current=0;
	printf("\n");
	for(i=0;i<size;i++){
		current=arr[i];
		if(current == 0){
			printf("0\n");
			continue;
		}
		while(current-->0){
			printf("*");
		}
		printf("\n");
	}
	printf("\n");
}

int validateSortingInputs(int* arr, int size){
	if(arr == NULL){
		printf("\nPlease provide an array to sort\n");
		return 1;
	}
	if(size<=0){
		printf("\nPlease provide proper size\n");
		return 1;
	}
	return 0;
}


// exchange sort starts
void exchangeSort(int* arr, int size){
	if(validateSortingInputs(arr, size)){
		return;
	}
	int i,j;
	for(i=0 ; i<size ; i++){
		for(j = i+1 ; j<size ; j++){
			if(compare(arr[j],arr[i])){
				swap(arr,i,j);
			}
		}
		if(doVisualization){
			printf("\nPass %d\n", i+1);
			printArrayVisualization(arr,size);
		}
	}
}
// exchange sort ends

// insertion sort starts
void insertionSort(int* arr, int size){
	if(validateSortingInputs(arr, size))
		return;
	int i,j,key;
	for(i =1 ; i<size ; i++){
		key = arr[i];
		j=i-1;
		while(j>=0 && compare(key,arr[j])){
			arr[j+1] = arr[j];
			j--;
		}
		arr[j+1] = key;
		if(doVisualization){
			printf("\nPass %d\n", i);
			printArrayVisualization(arr,size);
		}
	}
	
}
// insertion sort ends

// mergesort sort starts
void merge(int *arr , int left , int mid , int right){
	int size1 = mid - left +1;
	int size2 = right- mid;
	int leftCopy[size1];
	int rightCopy[size2];
	int i,j,k;
	for(i=0 ; i < size1 ; i ++ )
		leftCopy[i] = arr[left+i];
	for(i=0 ; i < size2 ; i ++ )
		rightCopy[i] = arr[mid+1+i];

	i=0,j=0,k=left;
	while ( i < size1 && j < size2){
		if(compare(leftCopy[i], rightCopy[j])){
			arr[k++] = leftCopy[i++];
		}
		else{
			arr[k++] = rightCopy[j++];
		}
	}
	while(i < size1){
		arr[k++] = leftCopy[i++];
	}
	while(j < size2){
		arr[k++] = rightCopy[j++];
	}
}
void mergesort_recursive(int *arr  , int l, int r,int size){
	if(l<r){
		int mid = l + ((r-l)/2);
		mergesort_recursive(arr,l,mid,size);
		mergesort_recursive(arr,mid+1,r,size);	
		merge(arr,l,mid,r);
		if(doVisualization){
			printArrayVisualization(arr,size);
		}
#ifdef DEBUG
	printArray(arr,size);
#endif
	}
}
void mergeSort(int* arr, int size){
	if(validateSortingInputs(arr, size))
		return;
	mergesort_recursive(arr, 0,size-1,size);
}
// mergesort sort ends

// quicksort sort starts
int partition(int *arr, int left, int right){
	int range = right - left+1;
	int pivot = left + rand() % range;
	swap(arr, left, pivot);

	int key = arr[left];
	int i=left,j=right+1;
	while(1){
		while(compare(arr[++i], key)){
			if(i==right)
				break;
		}
		while(compare(key, arr[--j])){
			if(j==left)
				break;
		}
		if(i >= j){
			break;
		}
		swap(arr, i ,j);
	}
	swap(arr,j,left);
	return j;
}
void quickSort_recursive(int* arr, int left, int right,int size){
	if(left >= right)
		return;
	int pivot = partition(arr, left , right);
#ifdef DEBUG
	printf("Left %d, right %d, Pivot is : %d\n",left, right, pivot);
	printArray(arr,size);
#endif
	if(doVisualization){
		//printf("Pivot: %d\n",pivot);
		printArrayVisualization(arr,size);
	}
	quickSort_recursive(arr, left, pivot-1, size);
	quickSort_recursive(arr, pivot+1, right, size);
}
void quickSort(int* arr, int size){
	if(validateSortingInputs(arr, size))
		return;
	quickSort_recursive(arr,0,size-1,size);
}
// quicksort sort ends

void printDialog(){
	printf("\nSelect sorting method\n");
	printf("1. Exchange Sort\n");
	printf("2. Insertion Sort\n");
	printf("3. Merge Sort\n");
	printf("4. Randomized Quick Sort\n");
	printf("5. Exit\n");
	printf("Enter  choice\n");
}

int getInput(){
	int x = -1;
	char ch;
	if(scanf("%d",&x)!=1){
		while ((ch = getchar()) != '\n' && ch != EOF);
		printf("Please enter a number\n");
		return getInput();
	}
	return x;
}

int validateChoice(int x){
	if(x<=0 || x>=6)
		return 1;
	return 0;
}
int validateSortSize(int x){
	if(x<1 || x>1000)
		return 1;
	return 0;
}

void initArray(int* arr, int size){
	 int i = 0;
	 int range; // TODO confirm range for >20
	 int randomNumber;
	 for(i=0;i<size;i++){
	 	randomNumber = rand();
	 	if(doVisualization)
	 		randomNumber %= 15;
	 	arr[i] = randomNumber;
	 }
}

void checkForExit(int x){
	if(x==5){
		printf("\nExiting...\n");
		exit(0);
	}
}
int main(){
	int n = -1; //sorting size
	int choice = -1; //sorting size
	int array[1000];
	srand (time(NULL));
	while(1){
		printDialog();
		choice = getInput();
#ifdef DEBUG		
		printf("\n\n%d\n",choice );
#endif
		if(validateChoice(choice)){
			printf("\nInvalid choice.\nLet's start over!\n");
			continue;
		}
		checkForExit(choice);
		printf("\nEnter number of elements to sort:");
		n = getInput();
#ifdef DEBUG		
		printf("\n\n%d\n",n );
#endif
		if(validateSortSize(n)){
			printf("\nRange between 1 to 1000.\nLet's start over!!\n");
			continue;
		}
		if(n <= 20){
			doVisualization = 1;
		}
		else{
			doVisualization = 0;
		}
		initArray(array,n);
		printf("Randomized Array\n");
		printArray(array,n);
		if(doVisualization)
			printArrayVisualization(array,n);
		
		switch(choice){
			case 1:
					exchangeSort(array,n);
					break;
			case 2:
					insertionSort(array,n);
					break;
			case 3:
					mergeSort(array,n);
					break;
			case 4:
					quickSort(array,n);
					break;
			case 5:
					printf("not possible\n");
					exit(0);
					break;
			default:
					printf("not possible\n");
					break;
		}
		printf("Sorted Array\n");
		printArray(array,n);
	}

	return 0;
}