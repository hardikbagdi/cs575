#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define DEBUG
int no_of_vertices = -1;
int size_of_heap;
int adj_matrix[10][10];
//DS for graph representation
struct edge{
	int source, dest, weight;
};
struct graph{
	int no_of_vertices,no_of_edges;
	struct edge* edges;
};
struct set{
	int root;
	int height;
};
//DS to hold cost and vertex for prim's
struct cost_vertex{
	int cost;
	int vertex;
};
void init_graph(){
	int i,j,temp;
	no_of_vertices = rand()%6 + 5;
	for(i=0;i<no_of_vertices;i++){
		for(j=0;j<=i;j++){
			if(i==j){
				adj_matrix[i][j] = 0;
			}
			else{
				temp = rand() % 10 + 1;
				adj_matrix[i][j] = temp;
				adj_matrix[j][i] = temp;
			}
		}
	}
}
void printGraph(){
	int i,j;
	printf("\nNumber of vertices: %d\n", no_of_vertices);
	printf("Adjacency matrix:\n");
	for (i = 0; i < no_of_vertices; i++)
	{
		for (j= 0; j < no_of_vertices; j++)
		{
			printf("%2d ", adj_matrix[i][j]);
		}
		printf("\n");
	}
}
//used for dijkstra
int min_key(int  *key , int *mst){
	int min = INT_MAX, min_index,i;
	for(i=0;i<no_of_vertices;i++){
		if(mst[i] == 0 && key[i] < min){
			min = key[i];
			min_index = i;
		}
	}
	return min_index;
}
//print MST for prim
void printMST(int *parent){
	int i,total=0;
	// printf("\nparent array:\n");
	// for(i=0;i<no_of_vertices;i++){
	// 	printf(" %d ",parent[i] );
	// }
	printf("\nMST edges:\n");
	//parent[0] will always be zero and hence starting from second index
	for(i=1;i<no_of_vertices;i++){
		printf("Edge: %d - %d\t Weight: %d\n",i,parent[i],adj_matrix[i][parent[i]]);
		// total +=adj_matrix[i][parent[i]];
	}
	//printf("total: %d\n",total );
}
// Heap DS for Prim's
void swap(struct cost_vertex* arr, int i, int j){
	struct cost_vertex temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
void min_heapify(struct cost_vertex* arr, int size, int current){
	int left = 2*current+1;
	int right = left+1;
	int smallest = current;
	if(left < size && arr[left].cost < arr[smallest].cost){
		smallest = left;
	}
	if(right < size && arr[right].cost < arr[smallest].cost){
		smallest = right;
	}
	if(smallest!= current){
		swap(arr,smallest,current);
		min_heapify(arr,size,smallest); //sinking
	}
}
void heapSort(struct cost_vertex* arr, int size){
	int i,j,current_size_heap;
	size_of_heap = size;
	for(i = size/2; i>=0;i--){
		min_heapify(arr,size,i);
	}
///	printheap(arr);
}
//arr reference. i is the element whose key has been reduced
void decrease_key(struct cost_vertex* arr, int i){
	int parent = ((i-1)/2);
//	printf("(%d) is parent of %d\n",parent,i );
	if(arr[parent].cost > arr[i].cost){
		swap(arr,parent,i);
	}
	else{
		return;
	}
	if(i==0){
		return;
	}
	else{
		decrease_key(arr,parent);
	}
}
//
int delete_min(struct cost_vertex *heap){
	int min = heap[0].vertex;
	heap[0] = heap[--size_of_heap];
	min_heapify(heap,size_of_heap,0);
	return min;
}
int find_and_update_cost(struct cost_vertex *arr,int vertex_to_find,int new_cost){
	int i=0;
	for(i=0;i<size_of_heap;i++){

		if(arr[i].vertex == vertex_to_find){
			arr[i].cost = new_cost;
			return i;
		}
	}
}
void printheap(struct cost_vertex *heap){
int i;
	printf("vertex");
		for(i=0;i<size_of_heap;i++){
			printf("%d ", heap[i].vertex);
		}
		printf("\n==cost");
		for(i=0;i<size_of_heap;i++){
			printf("%d ", heap[i].cost);
		}
}
int find_vertex_index(struct cost_vertex *heap,int vertex_to_find){
	int i;
	for(i=0;i<size_of_heap;i++){
		if(heap[i].vertex == vertex_to_find){
			return i;
		}
	}
}
//using heap
void primMST(){
	int i,j,u;
	int heap_loc_to_reduce;
	int parent[no_of_vertices];
	struct cost_vertex heap[no_of_vertices];
	int mst[no_of_vertices];
	memset(parent,-1,no_of_vertices*sizeof(int));
	memset(mst,0,no_of_vertices*sizeof(int)); //0 false, 1 true
	for( i=0;i<no_of_vertices;i++){
		heap[i].vertex = i;
		heap[i].cost = INT_MAX;
	}
//	printheap(heap);
	//set starting point at vertex 0
	heap[0].cost = 0;
	heapSort(heap,no_of_vertices);
	parent[0] = -1;
	while( size_of_heap!=0){
		
		u = delete_min(heap);
	//	printf("\n Delete Min:%d\n",u );
	//	printheap(heap);
		for(j=0; j< no_of_vertices; j++){
			if(adj_matrix[u][j] != 0 &&
				adj_matrix[u][j] < heap[find_vertex_index(heap,j)].cost && mst[j]==0){
				parent[j] = u;
				heap_loc_to_reduce = find_and_update_cost(heap,j,adj_matrix[u][j]);

				decrease_key(heap,heap_loc_to_reduce);
			//	printf("\ndecrease_key Loc is %d, new cost is %d\n",heap_loc_to_reduce,adj_matrix[u][j] );
			//	printheap(heap);
			}
		}
		mst[u] = 1;
	}
	printMST(parent);
}
//using array
void primMST2(){
	int i,j,u;
	int parent[no_of_vertices];
	int key[no_of_vertices];
	int mst[no_of_vertices];
	memset(parent,0,no_of_vertices*sizeof(int));
	memset(mst,0,no_of_vertices*sizeof(int)); //0 false, 1 true
	//memset(key,0,no_of_vertices*sizeof(int));
	for( i=0;i<no_of_vertices;i++)
		key[i] = INT_MAX;
	//set starting point at vertex 0
	key[0] = 0;
	parent[0] = -1;
	for( i=0; i < no_of_vertices-1 ; i++){
		u = min_key(key,mst);
		for(j=0; j< no_of_vertices; j++){
			if(adj_matrix[u][j] != 0 && mst[j] == 0 &&
				adj_matrix[u][j] < key[j]){

				parent[j] = u;
				key[j] = adj_matrix[u][j];
			}
		}
		mst[u] = 1;
	}
	printMST(parent);
}
struct graph* createGraph(int v,int e){
	struct graph* g = NULL;
	g = (struct graph*)malloc(sizeof(struct graph));
	if(g == NULL){
		return NULL;
	}
	g-> no_of_vertices = v;
	g-> no_of_edges= e;
	g-> edges = (struct edge*)malloc(sizeof(struct edge)*e);
	return g;
}

int find3(struct set *sets, int i)
{
    
    if (sets[i].root != i)
        sets[i].root = find3(sets, sets[i].root);
 
    return sets[i].root;
}

void union3(struct set *sets, int a, int b)
{
    int a_root = find3(sets, a);
    int b_root = find3(sets, b);
    if (sets[a_root].height < sets[b_root].height)
        sets[a_root].root = b_root;
    else if (sets[a_root].height > sets[b_root].height)
        sets[b_root].root = a_root;
    else
    {
        sets[b_root].root = a_root;
        sets[a_root].height++;
    }
}
void print_edges(struct edge* edges, int n){
	int i;
	printf("Source Dest Weight\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\n", edges[i].source,edges[i].dest,edges[i].weight);
	}
}
void convert_adjmatrix_to_edges(struct graph* graph){
	// printf("converting\n");
	int i=0,j=0,k=0;
	for(i=0;i<no_of_vertices;i++){
		for(j=0;j<i;j++){
			
			{
				graph->edges[k].source = i; 
				graph->edges[k].dest =  j;
				graph->edges[k].weight =  adj_matrix[i][j];
				//printf("%d\n",adj_matrix[i][j]);
				k++;
			}
		}
	}
}
int comparator(const void* x,const void* y){
	int x_weight = ((struct edge*)x)->weight;
	int y_weight = ((struct edge*)y)->weight;
	return x_weight > y_weight;
}
void kruskalMST(){
	int i,j,k;
	int root_a,root_b;
	struct edge current_edge;
	struct graph* graph = createGraph(no_of_vertices,(no_of_vertices*(no_of_vertices-1))/2);
	if(graph == NULL){
		printf("Memory allocation failed\n");
		exit(-1);
	}
	convert_adjmatrix_to_edges(graph);
	//print_edges(graph->edges,graph->no_of_edges);
	struct edge MST[no_of_vertices];
	qsort(graph->edges,graph->no_of_edges,sizeof(struct edge),comparator);
	//printf("Sorting Completed\n");
	// print_edges(graph->edges,graph->no_of_edges);
	struct set sets[graph->no_of_vertices];
	for(i=0;i<graph->no_of_vertices;i++){
		sets[i].root = i;
		sets[i].height	 = 0;
	}
	j=0; //iterate through sorted edges
	k=0; //result array
	for(i=0;i<graph->no_of_edges &&  j < (graph->no_of_vertices-1);i++){ //iterate for MST
		current_edge = graph->edges[i];
		root_a = find3(sets,current_edge.source);
		root_b = find3(sets,current_edge.dest);
		
		if(root_a != root_b){
			MST[j] = current_edge;
			union3(sets,root_a,root_b);
		//	printf("%d adding an edge source:%d\tdest:\t%d\tweight:  %d\n",
		//		j,current_edge.source,current_edge.dest,current_edge.weight);
			j++;
		//	fflush(stdout);
		}
	}
	printf("Edges in MST\n");
	print_edges(MST,no_of_vertices-1);
}

//shortest path using dijkstra
void printShortestPaths(int* distance){
	int i;
	printf("Shortest Distances from 0\nVertex\tDistance\n");
	for (i = 0; i < no_of_vertices; ++i)
	{
		printf("%d\t%d\n", i,distance[i]);
	}
}

void dijkstra(){
	int i,j,u;
	int distance[no_of_vertices];
	int shortest_path[no_of_vertices];
	memset(shortest_path,0,no_of_vertices*sizeof(int)); //0 false, 1 true
	for( i=0;i<no_of_vertices;i++)
		distance[i] = INT_MAX;
	//set starting point at vertex 0
	distance[0] = 0;
	for( i=0; i < no_of_vertices-1 ; i++){
		u = min_key(distance,shortest_path);
		shortest_path[u] = 1;
		for(j=0; j< no_of_vertices; j++){
			if(adj_matrix[u][j] != 0 && shortest_path[j] == 0 &&
				distance[u]+adj_matrix[u][j] < distance[j]){
				distance[j] = distance[u]+ adj_matrix[u][j];
			}
		}
	}
	printShortestPaths(distance);
}

void printDialog(){
	printf("\nSelect Algorithm\n");
	printf("1. Prim's MST\n");
	printf("2. Kruskal's MST\n");
	printf("3. Dijkstra's Algorithm\n");
	printf("4. Exit\n");
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
	if(x<=0 || x>=5)
		return 1;
	return 0;
}
void checkForExit(int x){
	if(x==4){
		printf("\nExiting...\n");
		exit(0);
	}
}
int main(){
	int choice = -1; //Algorithm selection
	srand (time(NULL));
	while(1){
		printDialog();
		choice = getInput();		
		if(validateChoice(choice)){
			printf("\nInvalid choice.\nLet's start over!\n");
			continue;
		}
		checkForExit(choice);
		init_graph();
		printGraph();
		switch(choice){
			case 1:
					primMST();
					//primMST2(); using array, was used to verify correctness
					break;
			case 2:
					kruskalMST();
					break;
			case 3:
					dijkstra();
					break;
			default:
					printf("not possible\n");
					break;
		}
	}
	return 0;
}