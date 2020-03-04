#include "codingGraphs.h"

#include <iostream>

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

// A function that encodes graphs
void encode(int** matrix1, const int n, const int m){
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
        }
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


int** adjacencyToIncidence(int** adjacency, const int &n){
    int cols = n;
    int edge = 0;
    int m = 0;
    for(int i = 0; i< n; ++i){
        for(int j = i; j<n; ++j){
            if(adjacency[i][j] == 1)
                ++m;
        }
    }
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