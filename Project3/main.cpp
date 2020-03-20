#include <iostream>
#include <vector>
#include <algorithm>
#include "utils.h"
#include <random>
#include <cstdlib>
#include <ctime>

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
    std::cout<<"Podaj rozmiar macierzy:";
    std::cin>>size;
//    int size = rand() % 8 + 3;
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


    std::cout<<std::endl;
    std::cout<<"----------------------------- 2 ------------------------------------"<<std::endl;
    std::cout<<std::endl;
    dijkstra(importanceMatrix, size, 0);
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

void dijkstra(int** importanceMatrix,int size,int initVertex) {
    int cost[size][size],distance[size],path[size];
    int visited[size],count,mindInstance,nextVertex;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(importanceMatrix[i][j]==0)
                cost[i][j]=inf;
            else
                cost[i][j]=importanceMatrix[i][j];
    for(int i=0;i<size;i++) {
        distance[i]=cost[initVertex][i];
        path[i]=initVertex;
        visited[i]=0;
    }
    distance[initVertex]=0;
    visited[initVertex]=1;
    count=1;
    while(count<size-1) {
        mindInstance=inf;
        for(int i=0;i<size;i++)
            if(distance[i]<mindInstance&&!visited[i]) {
                mindInstance=distance[i];
                nextVertex=i;
            }
        visited[nextVertex]=1;
        for(int i=0;i<size;i++)
            if(!visited[i])
                if(mindInstance+cost[nextVertex][i]<distance[i]) {
                    distance[i]=mindInstance+cost[nextVertex][i];
                    path[i]=nextVertex;
                }
        count++;
    }

    for(int i=0;i<size;i++)
        if(i != initVertex) {
            std::cout<<"\nDistance from initial vertex to  vertex number "<< i <<": "<<distance[i];
            std::cout<<"\nPath: "<<i;
            int k;
            k=i;
            do {
                k=path[k];
                std::cout<<"->"<<k;
            }while(k!=initVertex);

        }

}

void dijkstra(int** importanceMatrix,int size,int initVertex, int* distanceMatrix) {
    int cost[size][size],distance[size],path[size];
    int visited[size],count,mindInstance,nextVertex;
    for(int i=0;i<size;i++)
        for(int j=0;j<size;j++)
            if(importanceMatrix[i][j]==0)
                cost[i][j]=inf;
            else
                cost[i][j]=importanceMatrix[i][j];
    for(int i=0;i<size;i++) {
        distance[i]=cost[initVertex][i];
        path[i]=initVertex;
        visited[i]=0;
    }
    distance[initVertex]=0;
    visited[initVertex]=1;
    count=1;
    while(count<size-1) {
        mindInstance=inf;
        for(int i=0;i<size;i++)
            if(distance[i]<mindInstance&&!visited[i]) {
                mindInstance=distance[i];
                nextVertex=i;
            }
        visited[nextVertex]=1;
        for(int i=0;i<size;i++)
            if(!visited[i])
                if(mindInstance+cost[nextVertex][i]<distance[i]) {
                    distance[i]=mindInstance+cost[nextVertex][i];
                    path[i]=nextVertex;
                }
        count++;
    }

    for(int i=0;i<size;i++)
        distanceMatrix[i] = distance[i];

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