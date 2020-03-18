#include <iostream>
#include "utils.h"
#include <time.h>
#include <vector>
#include <math.h>
#define STOP 100

/*
function checking if edge between two vertices is a bridge
arguments: adjacency matrix, size - number of vertices
v - index of first vertex,
u - index of second vertex
*/
bool is_bridge(int** adjM, int size, int v,int u);

/* arguments: adjacency matrix, n - number of vertices, 
v - current vertex, which neighbour we're looking for,
nr - number of neighbour we're looking for (e.g. in case previous is a bridge) */
int next_neighbour(int** adjM,int n,int v,int& nr);
void addEdge(int v, int u, int** adjM);
void removeEdge(int v, int u, int** adjM);


int main()
{
    int n;
    std::cout<<"Insert number of vertices: ";
    std::cin>>n;

    // n=8;

    int max_edge_level = n - 1;

    // int seq[] = {4, 2, 6, 2, 6, 2, 4, 2};
    int seq[n];
    int step = 0;

    do{

        for(int i=0; i<n; i++)
        {
            seq[i] = 2*(rand()%(static_cast<int>(ceil(max_edge_level/2.))));
        }
            step++;

    }while(!GraphSeq_check(seq, n) && step != STOP);

    if(step == STOP)
    {
        std::cout<<"Too many attempts for a random sequence. Try again\n";
        exit(EXIT_FAILURE);
    }

    std::cout<<"Your sequence:\n";
    for(int i=0; i<n;i++)
    {
        std::cout<<seq[i]<<" ";
    }
    std::cout<<std::endl;

    int** adjM = GraphSeq_to_AdjacencyMatrix(seq, n);
    printAdjacencyMatrix(adjM, n);
    std::vector<int> cykl;
    std::vector<bool> visited(n);
    std::fill(visited.begin(), visited.end(), false);

    int v = 0;
    cykl.push_back(v+1);

    int next;
    int nr;
    int check = 0;
    

    do
    {
        nr = 0;
        do{ 
            nr++;
            // std::cout<<"v = "<<v<<"\nnr before = "<<nr<<"\n";
            next = next_neighbour(adjM,n,v,nr);
            // std::cout<<"nr after = "<<nr<<"\n";
        }while(nr != -1 && is_bridge(adjM,n,v,next));

        //if there is no neighbour left, break the loop
        if(next == -1) break;

        //add neighbour to cycle (adding +1 only for difference in indexing in the end)
        cykl.push_back(next+1);

        //remove the edge we just crossed
        removeEdge(v,next,adjM);

        //go to the next neighbour and make it current vertex
        v = next;

        check++;

        if(check%20 == 0) std::cout<<check<<std::endl;

    }while(check != STOP);


    if(check == STOP)
    {
        std::cout<<"Time frame error\n";
        exit(EXIT_FAILURE);
    }

    std::cout<<"Euler's cycle:\n";
    for(int j=0; j<cykl.size(); j++)
    {
        std::cout<<cykl[j]<<" ";
    }
    std::cout<<std::endl;

    //printAdjacencyMatrix(adjM, n);

    return 0;
}

int next_neighbour(int** adjM,int n,int v,int& nr)
{
    if(nr == 0)
    {
        return -1;
    }

    int count = 0;
    int i=-1;

    //we need to get to the nr-th neighbour (count) 
    //and we need to keep i in n bounds 
    while(count < nr)
    {
        i++;
        if(i==n) break;
        if(adjM[v][i]) count++;
    }
    // if (v==4) std::cout<<"count = "<<count<<"i = "<<i<<"\n"; 

    //in case nt-th neighbour doesn't exist
    if(i==n)
    {
        nr--;
        //we go back to the previous neighbour
        i = next_neighbour(adjM,n,v,nr);
        //we need to let know if the nr-th neighbour is not found
        nr = -1;
    } 

    //return the index of found neighbour
    return i;
}

bool is_bridge(int** adjM, int size, int v, int u)
{
    bool ans = false;
    //counting components before removing current edge
    int count_first = count_components(adjM,size);
    removeEdge(v,u,adjM);
    //-||- after
    int count_second = count_components(adjM,size);
    
    //if number of components is different => the edge is a bridge
    if(count_first != count_second) ans = true;
    addEdge(v,u,adjM);

    return ans;
}

void addEdge(int v, int u, int** adjM)
{
    adjM[v][u] = 1;
    adjM[u][v] = 1;
}

void removeEdge(int v,int u,int** adjM)
{
    adjM[v][u] = 0;
    adjM[u][v] = 0;
}