#include "utils.h"

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


float r_prob()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

bool file_exist(const char *fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}