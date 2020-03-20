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