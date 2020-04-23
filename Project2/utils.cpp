#include "utils.h"

#include <iostream>
#include <iomanip>
#include <fstream>

int** makeAdjacencyMatrix(const int n){
    int** adjacencyMatrix = new int*[n];
    for(int i = 0; i < n; ++i ) {
        adjacencyMatrix[i] = new int[n];
    }
    for( int i = 0; i < n; ++i ) {
        for (int j = 0; j < n; ++j) {
            adjacencyMatrix[i][j] = 0;
        }
    }
    return adjacencyMatrix;
}

int** makeIncidenceMatrix(const int n, const int m){
    int** incidenceMatrix = new int*[n];
    for(int i = 0; i < n; ++i ) {
        incidenceMatrix[i] = new int[m];
    }
    for( int i = 0; i < n; ++i ) {
        for (int j = 0; j < m; ++j) {
            incidenceMatrix[i][j] = 0;
        }
    }
    return incidenceMatrix;
}

std::list<int>* makeAdjacencyList(const int n){
    std::list<int>* adjacencyList;
    adjacencyList = new std::list<int>[n];
    return adjacencyList;
}


void printAdjacencyMatrix( int** matrix, const int n){
    std::cout << std::endl;

    for(int i = 0; i<=n; ++i){
        if(i == 0){
            std::cout << std::setw(4) <<"\\";
        }
        else {
            std::cout << std::setw(3) << "v" << i-1;
        }
    }
    std::cout<<std::endl;
    for( int i = 0; i < n; ++i ) {
        std::cout << std::setw ( 3 ) <<"v"<< i;
        for (int j = 0; j < n; ++j) {
            if(j < 10)
                std::cout <<std::setw ( 4 )<< matrix[i][j];
            else if(j<100)
                std::cout <<std::setw ( 5 )<< matrix[i][j];
        }
        std::cout<<std::endl;
    }
}


void printIncidenceMatrix( int** matrix, const int n, const int m){
    for(int i = 0; i<=m; ++i){
        if(i == 0){
            std::cout << std::setw(4) <<"\\";
        }
        else {
            std::cout << std::setw(3) << "e" << i;
        }
    }
    std::cout<<std::endl;
    for( int i = 0; i < n; ++i ) {
        std::cout << std::setw ( 3 ) <<"v"<< i;
        for (int j = 0; j < m; ++j) {
            if(j<10) {
                std::cout << std::setw(4) << matrix[i][j];
            }
            else if(j<100){
                std::cout <<std::setw ( 5 )<< matrix[i][j];
            }
        }
        std::cout<<std::endl;
    }
}

void printAdjacencyList( std::list<int>* list, const int n){
    for( int i = 0; i < n; ++i ) {
        std::cout << "v"<<i<<": ";
        for (int x : list[i]) {
            std::cout << std::setw(3)<<"v" << x ;
        }
        std::cout<<std::endl;
    }
}



void matrix_to_file(int* seq, int n, std::string filename)
{
    int** adjM = GraphSeq_to_AdjacencyMatrix(seq, n);
    matrix_to_file(adjM,n,filename);
}


void matrix_to_file(int** adjM, int n, std::string filename)
{
    std::ofstream out(filename);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-1; j++)
        {
            out << adjM[i][j] << " ";
        }

        out << adjM[i][n-1];
        if(i != n-1) out << std::endl;
    }
}




float r_prob()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

bool file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}



//Maciek projekt2, zad1
bool GraphSeq_check(int *seq, int size)
{
    int* seq_copy = new int[size];
    for(int i = 0; i < size; i++)
        seq_copy[i] = seq[i];

    int odd = 0;
    for(int i = 0; i < size; i++)
    {
        if(seq_copy[i] % 2 == 1) odd++;
    }

    // If number of odd elements in the sequence is odd - it's not graphical sequence
    if(odd % 2 == 1)
    {
        return false;
    }

    while(true)
    {
        std::sort(seq_copy, seq_copy+size, std::greater<int>());

        // If all elements in the sequence are 0 - it's graphical sequence
        bool zeros = true;
        for(int i = 0; i < size; i++)
        {
            if(seq_copy[i] != 0)
            {
                zeros = false;
                break;
            }
        }
        if(zeros == true) return true;

        // If there is negative element in the sequence - it's not graphical sequence
        bool negative = false;
        for(int i = 1; i < size; i++)
        {
            if(seq_copy[i] < 0)
            {
                negative = true;
                break;
            }
        }
        if(negative == true || seq_copy[0] < 0 || seq_copy[0] >= size) return false;


        for(int i = 1; i <= seq_copy[0]; i++)
        {
            seq_copy[i] -= 1;
        }
        seq_copy[0] = 0;

    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_seq(int** seq, int size)
{
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
            if (seq[j][1] < seq[j+1][1])
            {
                swap(&seq[j][0], &seq[j+1][0]);
                swap(&seq[j][1], &seq[j+1][1]);
            }
        }
    }
}

int** GraphSeq_to_AdjacencyMatrix(const int* seq_graph, int size)
{

    int** adjMatrix = new int*[size];
    int** seq = new int*[size];

    for(int i = 0; i < size; i++)
    {
        seq[i] = new int[2];
        seq[i][0] = i;
        seq[i][1] = seq_graph[i];
        adjMatrix[i] = new int[size];
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    while(true)
    {
        sort_seq(seq, size);

        if(seq[0][1] == 0)
            break;

        int x,y,j = 1;

        while(seq[0][1] > 0)
        {
            x = seq[0][0];
            y = seq[j][0];

            if(seq[j][1] != 0 && adjMatrix[x][y] != 1 && adjMatrix[y][x] != 1)
            {
                adjMatrix[x][y] = 1;
                adjMatrix[y][x] = 1;
                seq[0][1]--;
                seq[j][1]--;
            }

            j++;
        }
    }

    return adjMatrix;
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


int count_components(int** adjM, int n)
{
    int seq[n];
    int count;

    for(int i=0; i<n;i++)
    {   
        count = 0;
        for(int j=0; j<n;j++)
        {
            if(adjM[i][j]) count++;
        }
        seq[i] = count;
    }

    std::vector<int> comp = components(seq,n);
    return *std::max_element(comp.begin(),comp.end());
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




bool isPossible(int n, int k){
    if(n >= k + 1 && (n * k) % 2 == 0) return true;
    return false;
}

 int** GenerateRegularGraph(int n, int k){
    int ** graph = new int*[n];
    for(int i = 0; i < n; i++)
    {
        graph[i] = new int[k];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < k/2; j++){
            // std::cout<<"*j*j*\n";
            graph[i][j] = (i + j + 1) % n;
            // std::cout<<graph[i][j]<<"\n";
            if(i - j - 1 >= 0)
                graph[i][k - j - 1] = i - j - 1;
            else
                graph[i][k - j - 1] = n + i - j - 1;
            // std::cout<<"graph[i][k - j - 1] = "<<graph[i][k - j - 1]<<"\n";
        }
        if(k % 2 != 0) graph[i][k/2] = (i + n/2) % n;
    }
    
    return graph;
 }


 bool CanAdd(int n, int** graph, int* cycle, int p, int v){
    if(graph[v][cycle[p - 1]] == 0)
        return 0;
    for(int i = 0; i < p; i++){
        if(cycle[i] == v) return 0;
    }
    return 1;
}

bool fun1(int n, int** graph, int* cycle, int p){
    //sprawdza czy w cyklu sa wszystkie wierzcholki jesli tak to sprawdza czy ostatni ma polaczenie z pierwszym
    if(p == n){
        if(graph[cycle[0]][cycle[n - 1]] == 1)
            return 1;
        else
            return 0; 
    }
    //sprawdza czy mozna dodac kolejny wiercholek oprocz zerwoego bo on juz jest
    //jesli mozna to dodaje i uruchamia funkcje dla kolejnego wierzcholka
    for(int i = 1; i < n; i++){
        if(CanAdd(n, graph, cycle, p, i)){
            cycle[p] = i;
            if(fun1(n, graph, cycle, p + 1))
                return 1;
            cycle[p] = -1;
        }
    }
    return 0;
}

int* Hamilton(int n, int** graph){
    int* cycle = new int[n];
    for(int i = 0; i < n; i++)
        cycle[i] = -1;

    cycle[0] = 0;

    if(fun1(n, graph, cycle, 1) == 1)
        return cycle;
    else{
        delete[] cycle;
        return nullptr;}
}