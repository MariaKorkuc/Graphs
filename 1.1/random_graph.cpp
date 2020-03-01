#include <iostream>
#include <cstdio>
#include <vector>
#include "utils.h"

using namespace std;

void make_probability_graph();
void make_random_graph();

//returns number of ends for particular edge using incidency matrix
int check_col(int** incM,const int n, int num);

//returns number of neighbours for particular vertice using incidency matrix
int check_row(int** matrix, const int m, int num);


int main()
{
    char choice;

    do{
        cout<<"Choose model of random graph: "<<endl<<"Type 'p' for G(n,p) graph, 'm'  for G(n,m) graph: ";
        choice = getchar();

        if(choice == 'p')
        {
            make_probability_graph();
        }
        else if(choice == 'm')
        {
            make_random_graph();
        }
        else
        {
            cout<<"Choose available option"<<endl;
        }
    }while(choice != 'p' && choice != 'm');

    return 0;
}

//create graph, where probability of existence of each edge is p
//we display adjecency matrix of random graph
void make_probability_graph()
{
    int n=0;
    float p;
    cout<<endl<<"Insert number of vertices: ";
    cin>>n;
    cout<<endl;
    cout<<"Insert probability (0 <= p <= 1): ";
    cin>>p;
    cout<<endl;

    if(n<=0)
    {
        cout<<"Wrong number of vertices!\n";
        exit(EXIT_FAILURE);
    }

    if(p>1 || p<0)
    {
        cout<<"Impossible probability!\n";
        exit(EXIT_FAILURE);
    }

    int** adjM = makeAdjacencyMatrix(n);

    float q;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i!=j)
            {
                //in simple graphs we fill only one half of the adjecency matrix, the rest is analogical
                if(j>i)
                {
                    //get random float from 0.0 to 1.0
                    q = r_prob();

                    if(q<p)
                    {
                        adjM[i][j] = 1;
                    }
                }
                else
                {
                    adjM[i][j] = adjM[j][i];
                }
            }
        }
    }

    printAdjacencyMatrix(adjM,n);

    for( int i = 0; i < n; ++i )
        delete[] adjM[i];

}



//create a random graph of n vertices and m edges
//we display incidence matrix of the graph
void make_random_graph()
{
    int n,m;
    cout<<endl<<"Insert number of vertices: ";
    cin>>n;
    cout<<endl;
    cout<<"Insert number of edges: ";
    cin>>m;
    cout<<endl;

    if(n<=0 || m<0)
    {
        cout<<"Impossible number of vertices or edges!\n";
        exit(EXIT_FAILURE);
    }

    //maximum number of edges in undirected graph - n(n-1)/2
    if(m > n*(n-1)/2)
    {
        cout<<"Too many edges\n";
        exit(EXIT_FAILURE);
    }

    int** incM = makeIncidenceMatrix(n, m);
    int r,r2;
    int count;

    for(int i=0; i<n; i++)
    {
        int j=0;
        while(j<m)
        {
            r = rand()%2;
            
            //check how many ends current edge already has
            count = check_col(incM,n,j);

            //make sure each verticle has at most n-1 neighbours
            if(check_row(incM,m,i) >= (n-1)) break;

            if(count < 2)
            {
                //each edge must have exactly 2 ends
                if(i == n-1)
                {
                    if(count == 1)
                    {
                        incM[i][j] = 1;
                    }  
                    else
                    {
                        do{
                            r2 = rand()%(n-1);
                        }while(check_row(incM,m,r2) >= (n-1));

                        incM[i][j] = 1;
                        incM[r2][j] = 1;
                    }
                }
                else if(r)
                {
                    incM[i][j] = 1;
                }
                
            }

            j++;
        }
            
    }

    printIncidenceMatrix(incM, n, m);
    for( int i = 0; i < n; ++i )
        delete[] incM[i];
}

int check_col(int** incM,const int n, int num)
{
    int count = 0;
    for(int i=0; i<n; i++)
    {
        if(incM[i][num]) count++;
    }

    return count;
}

int check_row(int** matrix, const int m, int num)
{
    int count = 0;
    for(int j=0; j<m; j++)
    {
        if(matrix[num][j]) count++;
    }

    return count;
}

