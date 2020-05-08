#include <iostream>
#include <cstdio>
#include <vector>
#include <time.h>
#include <unordered_set>
#include "utils.h"
#include "RandomGraph.h"

//using namespace std;

//returns number of ends for particular edge using incidency matrix
int check_col(int** incM,const int n, int num);

//returns number of neighbours for particular vertice using incidency matrix
int check_row(int** matrix, const int m, int num);


// int main()
// {
//     srand(time(NULL));
//    char choice;

//    do{
//        std::cout<<"Choose model of random graph: "<<std::endl<<"Type 'p' for G(n,p) graph, 'm'  for G(n,m) graph: ";
//        choice = getchar();

//        if(choice == 'p')
//        {
//            make_probability_graph();
//        }
//        else if(choice == 'm')
//        {
//            make_random_graph();
//        }
//        else
//        {
//            std::cout<<"Choose available option"<<std::endl;
//        }
//    }while(choice != 'p' && choice != 'm');

//    return 0;
// }

//create graph, where probability of existence of each edge is p
//we display adjecency matrix of random graph
void make_probability_graph()
{
    srand(time(NULL));
    int n=0;
    float p;
    std::cout<<std::endl<<"Insert number of vertices: ";
    std::cin>>n;
    std::cout<<std::endl;
    std::cout<<"Insert probability (0 <= p <= 1): ";
    std::cin>>p;
    std::cout<<std::endl;

    if(n<=0)
    {
        std::cout<<"Wrong number of vertices!\n";
        exit(EXIT_FAILURE);
    }

    if(p>1 || p<0)
    {
        std::cout<<"Impossible probability!\n";
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

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const &pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};

struct pair_key
{
	template <class T1, class T2>
	bool operator () (std::pair<T1, T2> const &pair1, std::pair<T1, T2> const &pair2) const
	{
		return (pair1.first == pair2.first && pair1.second == pair2.second) || (pair1.first == pair2.second && pair1.second == pair2.first);
	}
};


//create a random graph of n vertices and m edges
//we display incidence matrix of the graph
void make_random_graph()
{
    srand(time(NULL));
    int n,m;
    std::cout<<std::endl<<"Insert number of vertices: ";
    std::cin>>n;
    std::cout<<std::endl;
    std::cout<<"Insert number of edges: ";
    std::cin>>m;
    std::cout<<std::endl;

    if(n<=0 || m<0)
    {
        std::cout<<"Impossible number of vertices or edges!\n";
        exit(EXIT_FAILURE);
    }

    //maximum number of edges in undirected graph - n(n-1)/2
    if(m > n*(n-1)/2)
    {
        std::cout<<"Too many edges\n";
        exit(EXIT_FAILURE);
    }

    int** incM = makeIncidenceMatrix(n, m);

    std::unordered_set<std::pair<int,int>,pair_hash,pair_key> edges;
    int f,s;

    for(int i=0; i<m; i++)
    {
        do{
            f = rand()%n;
            s = rand()%n;
        }while(f==s);

        auto inserted = edges.insert(std::pair<int,int>(f,s));
        
        if(!inserted.second) i--;
    }

    int count = 0;
    for(auto edge : edges)
    {
        incM[edge.first][count] = 1;
        incM[edge.second][count] = 1;
        count++;
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
