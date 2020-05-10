
#include "project4.h"


int** randomDiGraph(int& n)
{
    std::cout<<"Insert number of vertices: ";
    std::cin>>n;

    float p = 0;

    srand(time(NULL));

    do{
        std::cout<<"\nInsert probability (0-1): ";
        std::cin>>p;
    }while(p<0.0 || p>1.0);

    int** adjM = makeAdjacencyMatrix(n);
    float r;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==j) continue;

            r = r_prob();

            if(r<p)
            {
                adjM[i][j] = 1;
            }
        }
    }

    std::list<int>* lista = DiAdjacencyToList(adjM,n);

    std::cout<<"Adjacency matrix: \n";
    printAdjacencyMatrix(adjM, n);
    std::cout<<"\nAdjacency list: \n";
    printAdjacencyList(lista, n);
    delete [] lista;

    return adjM;

}


int componentsWithKosaraju(int **adjM, int n)
{

    std::vector<int> comp = Kosaraju(adjM,n);

    int max = *std::max_element(comp.begin(),comp.end());

    std::cout<<"Graph's components: \n";
    for(int k=1; k<=max; k++)
    {
        std::cout<<k<<") ";

        for(int i=0; i<n;i++)
        {
            if(comp[i] == k)
            {
                std::cout<<i+1<<" ";
            }
        }
        std::cout<<std::endl;
    }

    return max;

}

void Exercise4()
{
    srand((unsigned) time(0));
    int size;

    int** matrix;


    do{
            matrix = randomDiGraph(size);

    }while(componentsWithKosaraju(matrix, size) != 1);

    int E = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(matrix[i][j] == 1){
                E++;
            }
        }
    }

    // Matrix of edges with start-end-weight information for simplicity
    int edges[E][3];

    int e = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(matrix[i][j] == 1){
                edges[e][0] = i;
                edges[e][1] = j;
                edges[e][2] = (rand() % 15) - 5;
                e++;
            }
        }
    }
   

    BellmanFord(edges, E, size);

}



void BellmanFord(int edges[][3], int E, int V)
{
    int vertex;
    int u, v, weight;
    int distances[V];

    std::cout<<"Insert vertex number:";
    std::cin>>vertex;

    for (int i = 0; i < V; i++){
        distances[i] = INT_MAX;
    }

    distances[vertex] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int e = 0; e < E; e++) {
            u = edges[e][0];
            v = edges[e][1];
            weight = edges[e][2];
            if((distances[u] != INT_MAX) && (distances[u] + weight < distances[v])){
                distances[v] = distances[u] + weight;
            }

        }
    }

    // Checking for negative-weight cycles
    for(int e = 0; e < E; e++){
        u = edges[e][0];
        v = edges[e][1];
        weight = edges[e][2];

        if((distances[u] != INT_MAX) && (distances[u] + weight < distances[v])){
            std::cout << "Graph contains negative cycle." << std::endl;
            return;
        }

    }

    for(int i = 0; i < V; i++){
        std::cout << "Vertex " << i << " -> cost = " << distances[i] << std::endl;
    }

    return;
}
