#include <iostream>
#include <iomanip>
#include <list>

void setData(int&, int&);

int** makeAdjacencyMatrix(int);
int** makeIncidenceMatrix(int, int);
std::list<int>* makeAdjacencyList(int);

void encode(int**, int**, std::list<int>*, int, int);

void printAdjacencyMatrix(int**, int);
void printIncidenceMatrix(int**, int, int);
void printAdjacencyList(std::list<int>*, int);

void clear(int**, int**, std::list<int>*, int, int);

int** adjacencyToIncidence(int** , const int&, const int&);
int** incidenceToAdjacency(int** , const int&, const int&);
int** listToAdjacency(std::list<int>*, const int&);
std::list<int>*  adjacencyToList(int** , const int&);
std::list<int>* incidenceToList(int** , const int&, const int&);
int** listToIncidence(std::list<int>* , const int&, const int&);


int main( ){
    int n, m;
    int **adjacencyMatrix, **incidenceMatrix;
    std::list<int>* adjacencyList;


    setData(n,m);

    adjacencyMatrix = makeAdjacencyMatrix(n);
    incidenceMatrix = makeIncidenceMatrix(n,m);
    adjacencyList = makeAdjacencyList(n);


    encode(adjacencyMatrix,incidenceMatrix,adjacencyList,n ,m);


    printAdjacencyMatrix(adjacencyMatrix, n);
    std::cout<<std::endl;

//    These functions are here for testing, they will eventually be placed in other files.
//    If you want to test them, uncomment the code

//    int** A = listToAdjacency(adjacencyList,n);
//    printAdjacencyMatrix(A,n);
//    std::cout<<std::endl;
//
//    int** B = incidenceToAdjacency(incidenceMatrix,n,m);
//    printAdjacencyMatrix(B,n);
//    std::cout<<std::endl;

//    End


    printIncidenceMatrix(incidenceMatrix,  n,  m);
    std::cout<<std::endl;

//    These functions are here for testing, they will eventually be placed in other files.
//    If you want to test them, uncomment the code

//    int** C = adjacencyToIncidence(adjacencyMatrix, n, m);
//    printIncidenceMatrix(C,  n,  m);
//    std::cout<<std::endl;
//
//    int** D = listToIncidence(adjacencyList,n,m);
//    printIncidenceMatrix(D,n,m);
//    std::cout<<std::endl;

//    End

    printAdjacencyList(adjacencyList,  n);
    std::cout<<std::endl;

//    These functions are here for testing, they will eventually be placed in other files.
//    If you want to test them, uncomment the code

//    std::list<int>* list1 = adjacencyToList(adjacencyMatrix,n);
//    printAdjacencyList(list1,  n);
//    std::cout<<std::endl;
//
//    std::list<int>* list2 = incidenceToList(incidenceMatrix,n,m);
//    printAdjacencyList(list2,n);
//    std::cout<<std::endl;

//    End

    clear(adjacencyMatrix, incidenceMatrix, adjacencyList, n, m);
    return 0;
}

void setData(int &n, int &m){
    std::cout<<"Set the number of vertices: ";
    std::cin >> n;
    std::cout << "Set the number of edges: ";
    std::cin >> m;

    if(m > n*(n-1)/2){
        std::cout<<"Error! Too many edges for this number of vertices";
        exit (EXIT_FAILURE);
    }
}

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

// A function that encodes graphs
void encode(int** matrix1, int** matrix2, std::list<int>* list, const int n, const int m){
    std::cout<<"Remember! The vertices are numbered from 0."<<std::endl;
    int v1, v2;
    for(int  i = 0; i < m; ++i ){
        std::cout<<"Set the initial vertex of "<< i + 1 <<" edge: ";
        std::cin >> v1;

        std::cout<<"Set the end vertex "<< i + 1 <<" edge: ";
        std::cin >> v2;

        if(v1 >= n or v2 >= n){
            std::cout << "This edge does not exist. Use valid vertices! Remember that the vertices are numbered from 0. "<<std::endl;
            i--;
        }
        else if(v1 == v2){
            std::cout << "This is a simple graph, no loops are allowed"<<std::endl;
            i--;
        }
        else if(matrix1[v1][v2] != 0){
            std::cout << "This edge exist already!";
            i--;
        }

        else {
            matrix1[v1][v2] = 1;
            matrix1[v2][v1] = 1;

            matrix2[v1][i] = 1;
            matrix2[v2][i] = 1;

            list[v1].push_back(v2);
            list[v2].push_back(v1);
        }
    }
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
            std::cout <<std::setw ( 4 )<< matrix[i][j];
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
                std::cout <<std::setw ( 4 )<< matrix[i][j];
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

void clear(int** matrix1, int** matrix2, std::list<int>* list, const int n, const int m){
    for( int i = 0; i < n; ++i )
        delete[] matrix1[i];
    for( int i = 0; i < m; ++i )
        delete[] matrix2[i];
    delete[] matrix1;
    delete[] matrix2;
    delete[] list;
}



// Functions that convert one encoding into another

int** adjacencyToIncidence(int** adjacency, const int &n, const int &m){
    int cols = n;
    int edge = 0;
    int **incidence = makeIncidenceMatrix(n,m);

    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row <= col; ++row) {
            if (adjacency[col][row]) {
                incidence[row][edge] = incidence[col][edge] = 1;
                ++edge;
            }
        }
    }
    return incidence;
}

int** incidenceToAdjacency(int** incidence, const int &n, const int &m){
    int edges = m;
    int vertices = n;

    int** adjacency = makeAdjacencyMatrix(n);

    for (int edge = 0; edge < edges; ++edge) {
        int a = 0, b = 0, vertex = 0;
        bool flag = false;
        for (; vertex < vertices && !flag; ++vertex) {
            if (incidence[edge][vertex]) {
                a = vertex;
                flag = true;
            }
        }
        flag = false;
        for (; vertex < vertices && !flag; ++vertex) {
            if (incidence[edge][vertex]) {
                b = vertex;
                flag = true;
            }
        }
        adjacency[a][b] = adjacency[b][a] = 1;
    }
    return adjacency;
}

int** listToAdjacency(std::list<int>* list, const int &n){
    int** adjacency = makeAdjacencyMatrix(n);
    for( int i = 0; i < n; ++i ) {
        for (int x : list[i]) {
            adjacency[i][x] = 1;
            adjacency[x][i] = 1;
        }
    }
    return adjacency;
}

std::list<int>* adjacencyToList(int** adjacency, const int& n) {
    std::list<int> *list = makeAdjacencyList(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(adjacency[i][j] == 1)
                list[i].push_back(j);
        }
    }
    return list;
}

std::list<int>* incidenceToList(int** incidence, const int& n, const int& m){
    int edges = m;
    int vertices = n;

    std::list<int>* list = makeAdjacencyList(n);

    for (int edge = 0; edge < edges; ++edge) {
        int a = 0, b = 0, vertex = 0;
        bool flag = false;
        for (; vertex < vertices && !flag; ++vertex) {
            if (incidence[edge][vertex]) {
                a = vertex;
                flag = true;
            }
        }
        flag = false;
        for (; vertex < vertices && !flag; ++vertex) {
            if (incidence[edge][vertex]) {
                b = vertex;
                flag = true;
            }
        }
        list[a].push_back(b);
        list[b].push_back(a);
    }
    return list;
}

int** listToIncidence(std::list<int>* list , const int& n, const int& m){

    int edge = 0;
    int **incidence = makeIncidenceMatrix(n,m);

    for (int i = 0; i < n; ++i) {
        for (int x : list[i]) {
            if (x) {
                incidence[x][edge] = incidence[i][edge] = 1;
                ++edge;
            }
        }
    }
    return incidence;
}

