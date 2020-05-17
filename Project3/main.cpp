#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"
#include <random>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define inf 9999

std::vector<int> components(int* seq, int size);
void components_R(int nr, int v, int** adjM, std::vector<int>& comp, int size);
void dijkstra(int** ,int ,int );
void dijkstra(int** ,int ,int, int* );


int main()
{
    srand (time(nullptr));
    int size;
    bool flag = true;
    std::cout<<"----------------------------- 1 ------------------------------------"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Set number of vertices:";
    std::cin>>size;
    int seq[size];
    while(flag) {

        std::uniform_real_distribution<double> b(0, size);
        for (int i = 0; i < size; ++i) {
            seq[i] = rand() % size;
        }

        if (!GraphSeq_check(seq, size)) {
            continue;
        }
        else {
            std::vector<int> comp = components(seq,size);
            int max = *std::max_element(comp.begin(),comp.end());
            if(max == 1)
                flag = false;
        }
    }

    std::vector<int> comp = components(seq,size);
    int max = *std::max_element(comp.begin(),comp.end());
    int greatest_count = 0;
    int greatest;
    int count;

    for(int n=1; n<=max; n++)
    {
        count = std::count(comp.begin(),comp.end(),n);
        if(greatest_count < count)
        {
            greatest_count = count;
            greatest = n;
        }

        std::cout<<n<<") ";

        for(int i=0; i<size;i++)
        {
            if(comp[i] == n)
            {
                std::cout<<i+1<<" ";
            }
        }
        std::cout<<std::endl;
    }
    int** adjM = GraphSeq_to_AdjacencyMatrix(seq,size);
    std::cout<<"Greatest component: number "<<greatest<<std::endl;
    printAdjacencyMatrix(adjM, size);

    int** importanceMatrix = makeAdjacencyMatrix(size);
    for(int i =0; i< size; ++i){
        for(int j=i;j<size; ++j){
            if(adjM[i][j] == 1){
                importanceMatrix[i][j] = importanceMatrix[j][i] = rand()%10 +1;
            }
        }
    }

    printAdjacencyMatrix(importanceMatrix, size);

    std::cout<<std::endl;
    std::cout<<"----------------------------- 2 ------------------------------------"<<std::endl;
    std::cout<<std::endl;
    int initVertex = 0;
    std::cout<<"Choose init vertex: ";
    std::cin>>initVertex;
    dijkstra(importanceMatrix, size, initVertex);
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"----------------------------- 3 ------------------------------------"<<std::endl;
    int** distanceMatrix = makeAdjacencyMatrix(size);

    for(int i = 0; i < size; ++i){
        dijkstra(importanceMatrix, size, i, distanceMatrix[i]);
    }
    printAdjacencyMatrix(distanceMatrix,size);
    return 0;
}

int minimumDistance(const int *dist, int size, const bool *visited){
    int min_index = 0;
    int min = INT_MAX;
    for (int v = 0; v < size; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void printParent(int parent[], int i){
    if (parent[i] == - 1)
        return;
    printParent(parent, parent[i]);
    printf(" -> %d", i);
}

void printWithPath(int dist[], int size, int parent[], int initVertex){
    std::cout<<std::setw(6)<<"Vertex";
    std::cout<<std::setw(10)<<"Distance";
    std::cout<<std::setw(10)<<"Path";
    std::cout<<std::endl;
    for (int i = 0; i < size; i++){
        if(i != initVertex) {
            std::cout << std::setw(0) << initVertex << "->" << i;
            std::cout << std::setw(6) << dist[i];
            std::cout << std::setw(12) << initVertex << "";
            printParent(parent, i);
            std::cout << std::endl;
        }
    }
}

void dijkstra(int **importanceMatrix, int size, int initVertex){
    int dist[size];
    bool visited[size];
    int parent[size];
    for (int i = 0; i < size; i++){
        parent[initVertex] = -1;
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[initVertex] = 0;

    for (int i = 0; i < size - 1; i++){

        int u = minimumDistance(dist, size, visited);
        visited[u] = true;

        for (int v = 0; v < size; v++) {
            if (!visited[v] && importanceMatrix[u][v] && dist[u] + importanceMatrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + importanceMatrix[u][v];
            }
        }
    }

    printWithPath(dist, size, parent, initVertex);
}



void dijkstra(int** importanceMatrix,int size,int initVertex, int* distanceMatrix) {
    int dist[size];
    bool visited[size];
    for (int i = 0; i < size; i++){
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[initVertex] = 0;

    for (int i = 0; i < size - 1; i++){

        int u = minimumDistance(dist, size, visited);
        visited[u] = true;

        for (int v = 0; v < size; v++) {
            if (!visited[v] && importanceMatrix[u][v] && dist[u] + importanceMatrix[u][v] < dist[v]) {

                dist[v] = dist[u] + importanceMatrix[u][v];
            }
        }
    }

    for(int i = 0; i < size; ++i){
        distanceMatrix[i] = dist[i];
    }

}

std::vector<int> components(int* seq, int size)
{
    int nr = 0;
    if(!GraphSeq_check(seq, size))
    {
        std::cout<<"Cannot create a graph from this sequence\n";
        exit(EXIT_FAILURE);
    }
    std::vector<int> comp(size);
    std::fill(comp.begin(), comp.end(), -1);
    int** adjM = GraphSeq_to_AdjacencyMatrix(seq,size);
    for(int i=0; i<size; i++)
    {
        if(comp[i] == -1)
        {
            nr++;
            comp[i] = nr;
            components_R(nr,i,adjM,comp,size);
        }
    }

    return comp;

}

void components_R(int nr, int v, int** adjM, std::vector<int>& comp, int size)
{
    for(int i=0; i<size; i++)
    {
        if(adjM[v][i] && comp[i] == -1)
        {
            comp[i] = nr;
            components_R(nr,i,adjM,comp,size);
        }
    }
}