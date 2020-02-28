#include <iostream>
#include <iomanip>
#include <list>


using namespace std;

void setData(int&, int&);

int** makeAdjacencyMatrix(int);
int** makeIncidenceMatrix(int, int);
list<int>* makeAdjacencyList(int);

void fill(int**, int**, list<int>*, int, int);

void printAdjacencyMatrix(int**, int);
void printIncidenceMatrix(int**, int, int);
void printAdjacencyList(list<int>*, int);

void clear(int**, int**, list<int>*, int, int);

int** adjacencyToIncidence(int** , const int&, const int&);
int** incidenceToAdjacency(int** , const int&, const int&);
int** listToAdjacency(list<int>*, const int&);
list<int>*  adjacencyToList(int** , const int&);
list<int>* incidenceToList(int** , const int&, const int&);
int** listToIncidence(list<int>* , const int&, const int&);



int main( ){
    int n, m;
    int **adjacencyMatrix, **incidenceMatrix;
    list<int>* adjacencyList;


    setData(n,m);

    adjacencyMatrix = makeAdjacencyMatrix(n);
    incidenceMatrix = makeIncidenceMatrix(n,m);
    adjacencyList = makeAdjacencyList(n);


    fill(adjacencyMatrix,incidenceMatrix,adjacencyList,n ,m);


    printAdjacencyMatrix(adjacencyMatrix, n);
    cout<<endl;

//    int** A = listToAdjacency(adjacencyList,n);
//    printAdjacencyMatrix(A,n);
//    cout<<endl;
//
//    int** B = incidenceToAdjacency(incidenceMatrix,n,m);
//    printAdjacencyMatrix(B,n);
//    cout<<endl;

    printIncidenceMatrix(incidenceMatrix,  n,  m);
    cout<<endl;

//    int** C = adjacencyToIncidence(adjacencyMatrix, n, m);
//    printIncidenceMatrix(C,  n,  m);
//    cout<<endl;
//
//    int** D = listToIncidence(adjacencyList,n,m);
//    printIncidenceMatrix(D,n,m);
//    cout<<endl;

    printAdjacencyList(adjacencyList,  n);
    cout<<endl;

//    list<int>* list1 = adjacencyToList(adjacencyMatrix,n);
//    printAdjacencyList(list1,  n);
//    cout<<endl;
//
//    list<int>* list2 = incidenceToList(incidenceMatrix,n,m);
//    printAdjacencyList(list2,n);
//    cout<<endl;

    clear(adjacencyMatrix, incidenceMatrix, adjacencyList, n, m);
    return 0;
}

void setData(int &n, int &m){
    cout<<"Set the number of vertices: ";
    cin >> n;
    cout<<"Set the number of edges: ";
    cin >> m;

    if(m > n*(n-1)/2){
        cout<<"Error! Too many edges for this number of vertices";
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

list<int>* makeAdjacencyList(const int n){
    list<int>* adjacencyList;
    adjacencyList = new std::list<int>[n];
    return adjacencyList;
}

void fill(int** matrix1, int** matrix2, list<int>* list, const int n, const int m){
    cout<<"Remember! The vertices are numbered from 0."<<endl;
    int v1, v2;
    for(int  i = 0; i < m; ++i ){
        cout<<"Set the initial vertex of "<< i + 1 <<" edge: ";
        cin >> v1;

        cout<<"Set the end vertex "<< i + 1 <<" edge: ";
        cin >> v2;

        if(v1 >= n or v2 >= n){
            cout << "This edge does not exist. Use valid vertices! Remember that the vertices are numbered from 0. "<<endl;
            i--;
        }
        else if(v1 == v2){
            cout << "This is a simple graph, no loops are allowed"<<endl;
            i--;
        }
        else if(matrix1[v1][v2] != 0){
            cout << "This edge exist already!";
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
    cout << endl;

    for(int i = 0; i<=n; ++i){
        if(i == 0){
            cout << setw(4) <<"\\";
        }
        else {
            cout << setw(3) << "v" << i-1;
        }
    }
    cout<<endl;
    for( int i = 0; i < n; ++i ) {
        cout << setw ( 3 ) <<"v"<< i;
        for (int j = 0; j < n; ++j) {
            cout <<setw ( 4 )<< matrix[i][j];
        }
        cout<<endl;
    }
}
    void printIncidenceMatrix( int** matrix, const int n, const int m){
        for(int i = 0; i<=m; ++i){
            if(i == 0){
                cout << setw(4) <<"\\";
            }
            else {
                cout << setw(3) << "e" << i;
            }
        }
        cout<<endl;
        for( int i = 0; i < n; ++i ) {
            cout << setw ( 3 ) <<"v"<< i;
            for (int j = 0; j < m; ++j) {
                cout <<setw ( 4 )<< matrix[i][j];
            }
            cout<<endl;
        }
    }

    void printAdjacencyList( list<int>* list, const int n){
        for( int i = 0; i < n; ++i ) {
            cout << "v"<<i<<": ";
            for (int x : list[i]) {
                cout << setw(3)<<"v" << x ;
            }
            cout<<endl;
        }
    }

void clear(int** matrix1, int** matrix2, list<int>* list, const int n, const int m){
    for( int i = 0; i < n; ++i )
        delete[] matrix1[i];
    for( int i = 0; i < m; ++i )
        delete[] matrix2[i];
    delete[] matrix1;
    delete[] matrix2;
    delete[] list;
}

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

int** listToAdjacency(list<int>* list, const int &n){
    int** adjacency = makeAdjacencyMatrix(n);
    for( int i = 0; i < n; ++i ) {
        for (int x : list[i]) {
            adjacency[i][x] = 1;
            adjacency[x][i] = 1;
        }
    }
    return adjacency;
}

list<int>* adjacencyToList(int** adjacency, const int& n) {
    list<int> *list = makeAdjacencyList(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(adjacency[i][j] == 1)
                list[i].push_back(j);
        }
    }
    return list;
}

list<int>* incidenceToList(int** incidence, const int& n, const int& m){
    int edges = m;
    int vertices = n;

    list<int>* list = makeAdjacencyList(n);

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

int** listToIncidence(list<int>* list , const int& n, const int& m){

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

