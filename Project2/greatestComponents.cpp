#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h> 
#include "utils.h"


std::vector<int> components(int* seq, int size);
void components_R(int nr, int v, int** adjM, std::vector<int>& comp, int size);


int main()
{
    int seq [] = {4,2,2,3,2,1,4,2,2,2,2};
    int size = (sizeof(seq)/sizeof(int));

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

    std::cout<<"Greatest component: number "<<greatest<<std::endl;


    return 0;
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