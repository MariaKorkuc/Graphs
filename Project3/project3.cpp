#include "project3.h"

int** ConsistentRandomGraph(int size)
{
    bool flag = true;

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

    return importanceMatrix;
}


void Dijkstra(int **importanceMatrix, int size, int initVertex){
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

        int u = MinimumDistance(dist, size, visited);
        visited[u] = true;

        for (int v = 0; v < size; v++) {
            if (!visited[v] && importanceMatrix[u][v] && dist[u] + importanceMatrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + importanceMatrix[u][v];
            }
        }
    }

    PrintWithPath(dist, size, parent, initVertex);
}


void Dijkstra(int** importanceMatrix,int size,int initVertex, int* distanceMatrix) {
    int dist[size];
    bool visited[size];
    for (int i = 0; i < size; i++){
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    dist[initVertex] = 0;

    for (int i = 0; i < size - 1; i++){

        int u = MinimumDistance(dist, size, visited);
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


void PrintWithPath(int dist[], int size, int parent[], int initVertex){
    std::cout<<std::setw(6)<<"Vertex";
    std::cout<<std::setw(10)<<"Distance";
    std::cout<<std::setw(10)<<"Path";
    std::cout<<std::endl;
    for (int i = 0; i < size; i++){
        if(i != initVertex) {
            std::cout << std::setw(0) << initVertex << "->" << i;
            std::cout << std::setw(6) << dist[i];
            std::cout << std::setw(12) << initVertex << "";
            PrintParent(parent, i);
            std::cout << std::endl;
        }
    }
}

void PrintParent(int parent[], int i){
    if (parent[i] == - 1)
        return;
    PrintParent(parent, parent[i]);
    printf(" -> %d", i);
}


int MinimumDistance(const int *dist, int size, const bool *visited){
    int min_index = 0;
    int min = INT_MAX;
    for (int v = 0; v < size; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void PrintCentrumAndMinmax(int **distanceMatrix, int size){
    int * sum_distance = new int[size];
    int * min_distance = new int[size];


    for(int j = 0; j < size; j++){
        sum_distance[j] = 0;
        min_distance[j] = distanceMatrix[j][0];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            sum_distance[i] += distanceMatrix[i][j];
            if(distanceMatrix[i][j] >= min_distance[i]) min_distance[i] = distanceMatrix[i][j];
        }
    }

    int center = 0;
    int minmax = 0;

    for(int i = 0; i < size; i++){
        if(sum_distance[i] <= sum_distance[center]) center = i;
        if(min_distance[i] <= min_distance[minmax]) minmax = i;
    }

    std::cout<<"Center = "<<center<<" (Sum of distances: "<<sum_distance[center]<<")\n";
    std::cout<<"Center minimax= "<<minmax<<" (Distance from the farthest: "<<min_distance[minmax]<<")\n";


}

int** KruskalMST(int **importanceMatrix, int size) {

    int mincost = 0;
    int parent[size];
    int edges = 0;

    int** MST = new int*[size];
    for(int i = 0; i < size; ++i)
        MST[i] = new int[size];

    for (int i = 0; i < size; i++)
        parent[i] = i;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(importanceMatrix[i][j] == 0 ) importanceMatrix[i][j] = INT_MAX;
            MST[i][j] = 0;
        }
    }

    while (edges < size - 1) {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (Find(parent, i) != Find(parent, j) && importanceMatrix[i][j] < min) {
                    min = importanceMatrix[i][j];
                    a = i;
                    b = j;
                }
            }
        }

        Union(parent, a, b);
        printf("Edge %d:(%d, %d) cost:%d \n", edges++, a, b, min);
        MST[a][b] = MST[b][a] = 1;
        mincost += min;
    }
    printf("\n Minimum cost= %d \n", mincost);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(importanceMatrix[i][j] > 10 ) importanceMatrix[i][j] = 0;
        }
    }

    return MST;
}

int Find(int parent[], int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void Union(int parent[], int i, int j)
{
    int a = Find(parent, i);
    int b = Find(parent, j);
    parent[a] = b;
}


// DRAWING

void DrawGraph(int** matrix, int size, int** MST, bool withMST){
    initwindow(1200,1000);
    int xc = 600;
    int yc = 500;
    const double M_PI = 3.14159265358979323846;

    char node[10];

    settextstyle(8 , 0 , 6);
    setcolor(15);

    for(int i = 0; i < size; i++)
    {
        sprintf(node, "%d", i);
        circle(xc + 350 * cos(2*M_PI/size * i), yc + 350 * sin(2*M_PI/size * i), 5);
        outtextxy(xc + 400 * cos(2*M_PI/size * i), yc + 400 * sin(2*M_PI/size * i), node);
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(matrix[i][j] != 0)
            {
                int X1 = xc + 350 * cos(2*M_PI/size * i);
                int X2 = xc + 350 * cos(2*M_PI/size * j);
                int Y1 = yc + 350 * sin(2*M_PI/size * i);
                int Y2 = yc + 350 * sin(2*M_PI/size * j);

                line(X1, Y1, X2, Y2);

                if(withMST == true){
                    if(MST[i][j] == 1){
                        setcolor(2);
                        setlinestyle(0, 1, 4);
                        line(X1, Y1, X2, Y2);
                        setlinestyle(0, 1, 1);
                        setcolor(15);
                    }
                }


                setcolor(4);
                settextstyle(10, 0, 3);
                sprintf(node, "%d", matrix[i][j]);
                outtextxy((X1 + X2)/2, (Y1+Y2)/2, node);
                setcolor(15);
            }
        }
    }
}
