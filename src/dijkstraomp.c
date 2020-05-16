#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

int minDistance(int dist[], int sptSet[], int V)
{
	// Initialize min value
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

int *dijkstra(int **graph, int src, int V)
{
	int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = 0;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.

		int u = minDistance(dist, sptSet, V);

		// Mark the picked vertex as processed
		sptSet[u] = 1;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	int *ansArray;
	ansArray = (int *)malloc(V * sizeof(int));
	for (int i = 0; i < V; i++)
	{
		ansArray[i] = dist[i];
	}
	return ansArray;
}

int **initGraf(int n)
{
	srand(13517143);
	int random, **graf;

	graf = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; ++i)
		graf[i] = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			random = rand() % 100;
			if (i == j)
			{
				graf[i][i] = 0;
			}
			else
			{
				graf[i][j] = random;
				graf[j][i] = random;
			}
		}
	}
	return graf;
}
void printGraf(int **graf, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d\t", graf[i][j]);
		}
		printf("\n");
	}
}
void freeMatrix(int **matrix,int n){
	for(int i=0;i<n;i++){
		free(matrix[i]);
	}
	free(matrix);
}

int main(int argc, char *argv[])
{
	int thread_count = strtol(argv[1], NULL, 10);
	int node_count = strtol(argv[2],NULL,10);
	int **graf,**answerMatrix,*arrayTemp;
	graf= initGraf(node_count);
	double start; 
	double end; 
	start = omp_get_wtime(); 
	
	answerMatrix= (int **)malloc(node_count * sizeof(int *));
	#pragma omp parallel num_threads(thread_count)
	#pragma omp for
	for(int i =0;i<node_count;i++){
		arrayTemp=dijkstra(graf,i,node_count); 
		answerMatrix[i]=arrayTemp;
	}
	for(int i=0;i<node_count;i++){
		for(int j=0;j<node_count;j++){
			printf("%d \t",answerMatrix[i][j]);
		}
		printf("\n");
	}
	end = omp_get_wtime(); 
	printf("~Work took %f seconds\n~", (end - start)*1000000);
	freeMatrix(answerMatrix,node_count);
	freeMatrix(graf,node_count);


	
}
