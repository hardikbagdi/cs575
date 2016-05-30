#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#undef DEBUG

int compare(int i,int j){
	if(i < j)
		return 1;
	return 0;
}

void checkForExit(int x){
	if(x==3){
		printf("\nExiting...\n");
		exit(0);
	}
}
void printDialog(){
	printf("\nSelect option\n");
	printf("1. Original Algorithm (n*k space)\n");
	printf("2. Modified Algorithm (k space)\n");
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
int validateInputs(int n, int k){
	if(n < 0 || k < 0)
		return 1;
	if(compare(n,k))
		return 1;
	return 0;
}
int validateChoice(int x){
	if(x<=0 || x>=4)
		return 1;
	return 0;
}
int min(int a, int b){
	if(a >b)
		return b;
	return a;
}
int original_bc(int n, int k){
	int matrix[n+1][k+1];
	int i,j;
	for(i=0;i<=n;i++){
		for(j=0;j<=min(i,k);j++){
			if(j ==0 || j == i)
				matrix[i][j] =1;
			else
				matrix[i][j] = matrix[i-1][j-1] + matrix[i-1][j];
		}
	}
	return matrix[n][k];
}
int optimized_bc(int n, int k){
	int matrix[k+1];
	int i,j;
memset(matrix,0,sizeof(int)*(k+1));	
matrix[0]=1;
	for(i=1;i<=n;i++){
		for( j=min(i,k);j>0;j--)
			matrix[j] = matrix[j] + matrix[j-1];
	}
	return matrix[k];
}
int main(){
	int n = -1;
	int k = -1; 
	int answer= -1;
	int choice = -1;
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
		printf("\nEnter value of n:");
		n = getInput();
		printf("\nEnter value of k:");
		k = getInput();
#ifdef DEBUG		
		printf("\nn: %d\n",n );
		printf("k: %d\n",k );
#endif
		if(validateInputs(n,k)){
			printf("n and k should be positive and\nn should be greater than k\n");
			continue;
		}
		
		switch(choice){
			case 1:	answer = original_bc(n,k);
					break;
			case 2: answer = optimized_bc(n,k);
					break;
		}
		printf("Binomial Coefficient: %d\n",answer);
	}

	return 0;
}

