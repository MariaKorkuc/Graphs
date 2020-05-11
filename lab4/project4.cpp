
#include "project4.h"
#define MAX_TRIALS 100

int** Matrixh;

int min(int a, int b){
   return (a<b)?a:b;
}

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

    int** adjM;

    do{
        adjM = makeAdjacencyMatrix(n);
        float r;
        int count;
        int stop;

        for(int i=0; i<n; i++)
        {
            count = 0;
            stop = 0;
            while(!count && stop < MAX_TRIALS)
            {
                stop++;
                for(int j=0; j<n; j++)
                {
                    if(i==j) continue;

                    r = r_prob();

                    if(r<p)
                    {
                        if(!adjM[j][i])
                        {
                            adjM[i][j] = 1;
                            count++;
                        }
                    }
                }
            }
            if(stop >= MAX_TRIALS)
            {
                std::cout<<"stop\n";
            }
            
        }
    }while(componentsWithKosaraju(adjM, n) != 1);

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

    int** matrix = randomDiGraph(size);
    //std::cout<<"test"<<std::endl;
    /*
    do{
            matrix = randomDiGraph(size);
    }while(componentsWithKosaraju(matrix, size) != 1);
    */

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

    Matrixh = new int*[size];
    for (int i = 0; i < size; i++)
    {
        Matrixh[i] = new int[size];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            Matrixh[i][j] = 0;}}
    

    int e = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(matrix[i][j] == 1){
                edges[e][0] = i;
                edges[e][1] = j;
                edges[e][2] = (rand() % 13) - 3;
                //edges[e][2] = (rand() % 10) + 1;
                std::cout << "Edge: " << i << " -> " << j << " Weight: " << edges[e][2] << std::endl;
                Matrixh[i][j] = edges[e][2];
                e++;
            }
        }
    }

    BellmanFord(edges, E, size);
    Johnson(edges, size, e);

    

}

bool boolBellmanFord(int edges[][3], int E, int V, int start, int* distanc)
{
    int vertex;
    int u, v, weight;
    int distances[V];

    vertex = start;

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
            return false;
        }

    }

    for(int i = 0; i < V; i++){
        distanc[i] = distances[i];
    }

    return true;
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

void Johnson(int edges[][3], int size, int e){


    int edges2[e + size][3];

        for(int i = 0; i < e; i++){
        for (int j = 0; j < 3; j++){
            edges2[i][j] = edges[i][j];
        }
    }

    for (int i = 0; i < size; i++)
    {
        edges2[e + i][0] = size;
        edges2[e + i][1] = i;
        edges2[e + i][2] = 0;
    }    

    int* distanc = new int[size + 1]; 


    if(boolBellmanFord(edges2, e + size, size + 1, size, distanc))
    {
        int *h = new int[size + 1];

        for(int i = 0; i < size + 1; i++){
            h[i] = distanc[i];
        }     

        for(int i = 0; i < e + size; i++){
                //edges2[i][3] = edges2[i][3] + h[edges2[i][0]] - h[edges2[i][1]];
        }

        int D[size][size];

        for(int i = 0; i  < size; i++){
            dijkstra(Matrixh, size + 1, i, distanc);
            for(int j = 0; j < size; j++){
                D[i][j] = distanc[j] - h[i] + h[j];
            }
        }

        std::cout<<"\n";
        for(int i = 0; i  < size; i++){
            for(int j = 0; j < size; j++){
                std::cout<<D[i][j]<<" ";
            }
        std::cout<<"\n";
        }

    }
    else
        std::cout << "Graph contains negative cycle." << std::endl;


    return;
}
