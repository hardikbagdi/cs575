#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
//#define DEBUG
// #define DEBUG3
#define THRESHOLD_SIZE 3
typedef struct s_large_integer{
int sign; // 0 means positive, 1 means negative
int size;
int *number;
}large_integer;

int get_random_digit(){
	return rand() % 10;
}

large_integer* create_large_integer(int size){
	large_integer* l = malloc(sizeof(large_integer));
	if(l == NULL){
		printf("Malloc failed\n");
		exit(0);
	}
	l->sign = 0; //positive by default
	l->size = size;
	l-> number = malloc(size*sizeof(int));
	return l;
}

void delete_large_integer(large_integer* l){
	free(l->number);
	free(l);
	return;
}
void print_large_integer(large_integer* l){
	printf("\n");
	if(l->sign == 1){
		printf("-");
	}
	else{
		printf("+");
	}
	int s = (l->size )-1;
	while(s>=0){
		printf("%d", l->number[s--]);
	}
}

large_integer* generate_random_large_integer(int size){
	int s = size - 1;
	large_integer* l = create_large_integer(size);
	while(s >=0){
		l->number[s--] = get_random_digit();
	}
	if(l->number[size -1 ] == 0){
		l->number[size -1 ]++;
	}
	l-> sign = (rand() % 2) == 1 ;
	return l;
}
int count_digits(int number){
	return (int) log10((double)number) + 1;
}
int convert_to_int(large_integer* l){
	int n = 0;
	int s = (l->size) - 1;
	while(s>=0){
		n = n*10 + (l->number[s--]);
	}
	//printf("\nNumber: %d",n );
	return n;
}
large_integer* convert_to_large_integer_2(int number){
	int size = count_digits(number);
#ifdef DEBUG
	printf("convertin %d to large_integer\n", number);
#endif
	int i = 0;
	large_integer* l_for_0 = create_large_integer(4);
	if(number == 0){
		l_for_0->size= 4;
		for( i = 0;i<4;i++)
			l_for_0->number[i] = 0;
		return l_for_0;
	}
	large_integer* l = create_large_integer(size);
	while(i < size){
		l->number[i++] = number%10;
		number /= 10;
	}
#ifdef DEBUG
	printf("returning from convert_to_large_integer_2\n");
#endif
	return l;
}

large_integer* convert_to_large_integer_3(int number){
	int size = count_digits(number);
#ifdef DEBUG
	printf("convertin %d to large_integer\n", number);
#endif
	int i = 0;
	large_integer* l_for_0 = create_large_integer(4);
	if(number == 0){
		l_for_0->size= 6;
		for( i = 0;i<6;i++)
			l_for_0->number[i] = 0;
		return l_for_0;
	}
	large_integer* l = create_large_integer(size);
	while(i < size){
		l->number[i++] = number%10;
		number /= 10;
	}
#ifdef DEBUG
	printf("returning from convert_to_large_integer_2\n");
#endif
	return l;
}

large_integer* simple_multiplication(large_integer* li1, large_integer* li2){
	int a = convert_to_int(li1);
	int b = convert_to_int(li2);
	//printf("\n multiplying %d and %d\n", a,b);
	int c = a*b;
	large_integer* product = convert_to_large_integer_2(c);
	return product;
}
large_integer* simple_multiplication_3(large_integer* li1, large_integer* li2){
	int a = convert_to_int(li1);
	int b = convert_to_int(li2);
	//printf("\n multiplying %d and %d\n", a,b);
	int c = a*b;
	large_integer* product = convert_to_large_integer_2(c);
	return product;
}

void split_2(large_integer* l , large_integer** x1, large_integer** y1){
	int size   = l->size;
	int split_size  = size/2;
#ifdef DEBUG
	printf("Splitting\n");print_large_integer(l);
	printf("into\n");
#endif
	large_integer* x = create_large_integer(split_size);
	large_integer* y = create_large_integer(split_size);
	int i=0;
	while(i<split_size){
		x->number[i] = l->number[split_size+i];
		y->number[i] = l->number[i];
		i++;
	}
#ifdef DEBUG
	printf("pritnin from split_2\n");
	print_large_integer(x);
	print_large_integer(y);
	printf("exiting split_2\n");
#endif
	*x1 = x;
	*y1 = y;
}
void split_3(large_integer* l , large_integer** x1, large_integer** y1, large_integer** z1){
	int size   = l->size;
	int split_size  = size/3;
	large_integer* x = create_large_integer(split_size);
	large_integer* y = create_large_integer(split_size);
	large_integer* z = create_large_integer(split_size);
	int i=0;
	while(i<split_size){
		x->number[i] = l->number[split_size+split_size+i];
		y->number[i] = l->number[split_size+i];
		z->number[i] = l->number[i];
		i++;
	}
#ifdef DEBUG3
	print_large_integer(x);
	print_large_integer(y);
	print_large_integer(z);
#endif
	*x1 = x;
	*y1 = y;
	*z1 = z;
}

large_integer* multiply_large_integer_10(large_integer* l, int shift){
#ifdef DEBUG
	print_large_integer(l);
	printf("size(%d) shifting by %d\n",l->size,shift);
#endif
	int final_size = (l->size)+shift;
	large_integer* shifted = create_large_integer(final_size);
	int i=0;
	while(i<shift){
		shifted->number[i++] = 0;
	}
	i=0;
	while(i < (l->size)){
		shifted->number[i+shift] = l->number[i]; 
		i++;
	}
#ifdef DEBUG
	printf("new number:\n");
	print_large_integer(shifted);
	printf("returnign from shift\n");
#endif
	return shifted;
}
large_integer* add_large_integer(large_integer* l1, large_integer* l2){
	//size of both the numbers will be different
	int sum=0,common_size=-1,i=0, carry=0;
	large_integer* longer;
	//allocate the larger
 	int size = 0;
 	if(l1->size >= l2->size){
 		size = l1->size +1;
 		longer = l1;
 	}
 	else{
 		size = l2->size +1;
 		longer = l2;
 	}
 	large_integer* sum_large_integer = create_large_integer(size);
	if(l1->size >= l2-> size){
		common_size = l2->size;
	}
	else{
		common_size = l1
		->size;
	}
	//do this for the common size
	while(i < common_size){
		sum = l1->number[i] + l2->number[i]+carry;
		sum_large_integer->number[i] = sum % 10;
		carry = sum/10;
		i++;
	}
	while(i < size-1){
		sum = longer->number[i]+carry;
		sum_large_integer->number[i] = sum % 10;
		carry = sum/10;
		i++;
	}
	if(carry){
		sum_large_integer->number[i] = carry;
		carry = 0;
	}
	else{
		sum_large_integer->number[i] = 0;
		if(sum_large_integer->size >0)
			sum_large_integer->size -=1;
	}
	return sum_large_integer;

}
large_integer* do_large_integer_multiplication_2(large_integer* u, large_integer* v){
	if(u->size <= THRESHOLD_SIZE){
		return simple_multiplication(u,v);
	}
	large_integer *x, *y, *w ,*z, *p1, *p2 ,*p3 ,*p4,*p5,*p6,*p7,*p8,*product;
	split_2(u,&x,&y);
	split_2(v,&w,&z);
	if(u->size != v->size){
		printf("not equal\n");
		exit(0);
	}
	// printf("printing after split_2\n");
	// print_large_integer(x);
	// print_large_integer(y);
	// print_large_integer(w);
	// print_large_integer(z);
	// fflush(stdout);
	///first time
	p1 = do_large_integer_multiplication_2(x,w);
#ifdef DEBUG
	printf("multiplying \n");
	print_large_integer(x);
	print_large_integer(w);
	printf("result is:\n");
	printf("before shifting\n");
	print_large_integer(p1);
#endif
	p6 = multiply_large_integer_10(p1,u->size);
	//second term
	p2 = do_large_integer_multiplication_2(x,z);
	p3 = do_large_integer_multiplication_2(w,y);
	p5 = add_large_integer(p2,p3);
#ifdef DEBUG
	printf("\n2 mid:");
	print_large_integer(p2);
	print_large_integer(p3);
	printf("before shifting(add of 2 mid)\n");
	print_large_integer(p5);
#endif
	p7 = multiply_large_integer_10(p5,(u->size)/2);
	//third term
	p4 = do_large_integer_multiplication_2(y,z);

	p8 = add_large_integer(p6,p7);
	// printf("added above to sum \n");
	// print_large_integer(p8);
	product = add_large_integer(p8,p4);
	delete_large_integer(p1);
	delete_large_integer(p2);
	delete_large_integer(p3);
	delete_large_integer(p4);
	delete_large_integer(p5);
	delete_large_integer(p6);
	delete_large_integer(p7);
	delete_large_integer(p8);
	return product;
}
large_integer* do_large_integer_multiplication_3(large_integer* u, large_integer* v){
	int quantum = (u->size)/3;
	if(u->size <= THRESHOLD_SIZE){
		return simple_multiplication_3(u,v);
	}
	//printf("inside mul 3\n");
	large_integer *x, *y, *w ,*z,*a,*b, *c, *p1, *p2 ,*p3 ,*p4,*p5,*p6,*p7,*p8,*product;
	large_integer *p9,*p10,*p11,*p12,*p13,*p14,*p15,*p16,*p17,*p18,*p19,*p20,*p21;
	split_3(u,&x,&y,&z);
	split_3(v,&a,&b,&c);
#ifdef DEBUG3
	print_large_integer(x);
	print_large_integer(y);
	print_large_integer(z);
	print_large_integer(a);
	print_large_integer(b);
	print_large_integer(c);
#endif
	if(u->size != v->size){
		printf("not equal\n");
		exit(0);
	}
	p1 = do_large_integer_multiplication_3(a,x);
	p2 = multiply_large_integer_10(p1,4*quantum); //first
	p3 = do_large_integer_multiplication_3(a,y);
	p4 = do_large_integer_multiplication_3(b,x);
	p5 = add_large_integer(p3,p4);
	p6 = multiply_large_integer_10(p5,3*quantum);//second
	p7 = do_large_integer_multiplication_3(b,y);
	p14 = do_large_integer_multiplication_3(a,z);
	p15 = do_large_integer_multiplication_3(c,x);
	p16 = add_large_integer(p7,p14);
	p17 = add_large_integer(p16,p15);
	p8 = multiply_large_integer_10(p17,2*quantum); //third
	p9 = do_large_integer_multiplication_3(b,z);
	p10 = do_large_integer_multiplication_3(c,y);
	p11 = add_large_integer(p9,p10);
	p12= multiply_large_integer_10(p11,quantum); //fourth
	p13 = do_large_integer_multiplication_3(c,z);//fifth

	p18 = add_large_integer(p2,p6);
	p19 = add_large_integer(p18,p8);
	p20 = add_large_integer(p19,p12);
	p21 = add_large_integer(p20,p13);

	return p21;
}
void set_sign(large_integer* li1, large_integer* li2, large_integer* product){
	product->sign = 0;
	if(li1->sign == 1 && li2->sign == 1){
		return;
	}
	if(li1->sign){
		product->sign = 1;
		return;
	}
	if(li2->sign){
		product->sign = 1;
	}
}
void lim_2(int size){
	large_integer* li1 = generate_random_large_integer(size);
	large_integer* li2 = generate_random_large_integer(size);

	
	print_large_integer(li1);
	print_large_integer(li2);

	large_integer* product = do_large_integer_multiplication_2(li1,li2);
	set_sign(li1,li2,product);
	printf("\nProduct:");
	print_large_integer(product);

	delete_large_integer(li1);
	delete_large_integer(li2);
	delete_large_integer(product);
}
void lim_3(int size){
	large_integer* li1 = generate_random_large_integer(size);
	large_integer* li2 = generate_random_large_integer(size);

	print_large_integer(li1);
	print_large_integer(li2);

	large_integer* product = do_large_integer_multiplication_3(li1,li2);
	set_sign(li1,li2,product);
	printf("\nProduct:");
	print_large_integer(product);
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
void printDialog(){
	printf("\nPlease input the number of digits in largeinteger for multiplication\n");
	printf("(-1 to exit)\n");
}
int power_of_two(int x){
	while((x%2) == 0 && x > 1)
		x /= 2;
	if(x == 1)
		return 1;
	return 0;
}
int power_of_three(int x){
	while((x%3) == 0 && x > 1)
		x /= 3;
	if(x == 1)
		return 1;
	return 0;
}
//determine power of 2 or 3 or not
int validateInputs(int x){
	if(x<=0)
		return 1;
	if(power_of_two(x)){
		return 2;
	}
	if(power_of_three(x)){
		return 3;
	}
	return 1;
}
void checkForExit(int x){
	if(x==-1){
		printf("\nExiting...\n");
		exit(0);
	}
}
void handle_specialCase(){
	int x = rand() %10,
	 y = rand() % 10;
	printf("Number 1: %d\n",x);
	printf("Number 2: %d\n",y );
	printf("Answer: %d\n", x*y);
}
int main(){
	int choice = -1;
	int user_input_size = -1; //multiplication size
	srand (time(NULL));
	while(1){
		printDialog();
		// user_input_size =64;
		user_input_size = getInput();
		checkForExit(user_input_size);
		if(user_input_size == 1){
			handle_specialCase();
			continue;
		}
		choice = validateInputs(user_input_size);
			
		switch(choice){
			case 1:
					printf("\nPlease input a number in power of 2 or 3\n");
					break;
			case 2:
					lim_2(user_input_size);
					break;
			case 3:
					lim_3(user_input_size);
					break;
			default:
					printf("not possible\n");
					break;
		}
		choice = -1;
	}

	return 0;
}