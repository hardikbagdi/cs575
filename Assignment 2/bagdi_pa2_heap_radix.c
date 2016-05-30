#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#undef DEBUG
int doVisualization = -1;
int is_radix = 0;

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


void printDialog(){
	printf("\nSelect sorting method\n");
	printf("1. Heap Sort\n");
	printf("2. Radix Sort\n");
	printf("3. Exit\n");
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
	if(x<=0 || x>=4)
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
	 	if(is_radix)
	 		randomNumber %= 1000;
	 	if(doVisualization)
	 		randomNumber %= 15;
	 	arr[i] = randomNumber;
	 }
}

void checkForExit(int x){
	if(x==3){
		printf("\nExiting...\n");
		exit(0);
	}
}
int get_max(int* arr, int size){
	int max = -1 ,i;
	for( i=0 ; i < size; i++){
		if(arr[i] > max)
			max = arr[i];
	}
	return max;
}
void counting_sort(int* arr, int size, int div_by){
	int temp_arr[size];
	int count[10];
	memset(count,0,sizeof(count));
	int i,j;
	for(i = 0 ; i<size ; i++){
		count[(arr[i]/div_by)%10]++;
	}
	for(i = 1 ; i<10; i++){
		count[i] +=count[i-1];
	}
	for(i = size-1 ; i >=0 ; i--){
		temp_arr[count[(arr[i]/div_by)%10] -1 ] = arr[i];
		count[(arr[i]/div_by)%10]--;
	}
	for(i=0;i<size;i++)
		arr[i] = temp_arr[i];
}
void min_heapify(int* arr, int size, int current){
	int left = 2*current+1;
	int right = left+1;
	int smallest = current;
	if(left < size && arr[left] > arr[smallest]){
		smallest = left;
	}
	if(right < size && arr[right] > arr[smallest]){
		smallest = right;
	}
	if(smallest!= current){
		swap(arr,smallest,current);
		min_heapify(arr,size,smallest); //sinking
	}
}
void heapSort(int* arr, int size){
	if(validateSortingInputs(arr, size))
		return;
	int i,j,current_size_heap;
	for(i = size/2; i>=0;i--){
		min_heapify(arr,size,i);
	}
	current_size_heap = size -1;
	for(i = current_size_heap ; i >0 ;i--){
		swap(arr,0,i);
		min_heapify(arr,i,0);
		//i--;
		if(doVisualization){
			printArray(arr,size);
			printArrayVisualization(arr,size);
		}
	}

}
void radixSort(int* arr, int size){
	if(validateSortingInputs(arr, size))
		return;
	int div_by = 1;
	int max = get_max(arr, size);
	for(div_by =1 ; max/div_by > 0 ; div_by *= 10){
		counting_sort(arr, size , div_by);
		if(doVisualization){
			printArray(arr,size);
			printArrayVisualization(arr,size);
		}
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
		if(choice == 2){
			is_radix = 1;
		}
		else{
			is_radix = 0;
		}
		initArray(array,n);
		printf("Randomized Array\n");
		printArray(array,n);
		if(doVisualization)
			printArrayVisualization(array,n);
		
		switch(choice){
			case 1:
					heapSort(array,n);
					break;
			case 2:
					radixSort(array,n);
					break;
			case 3:
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

