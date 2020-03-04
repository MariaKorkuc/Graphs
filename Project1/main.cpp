#include <iostream>
#include <fstream>
#include <cmath>
#include "utils.h"
#include "codingGraphs.h"

int main(int argc, char* argv[]) {
    int n, m = 0;
    int **adjacencyMatrix, **incidenceMatrix;
    std::list<int>* adjacencyList;
    char node[10];
    int count;
    int choice = -1;
    char *filename;

    filename = argv[1];


    if(!file_exist(filename)){
        setData(n,m);
        adjacencyMatrix = makeAdjacencyMatrix(n);
        encode(adjacencyMatrix,n ,m);
        printAdjacencyMatrix(adjacencyMatrix, n);
        std::cout<<std::endl;
    }
    else{
        std::ifstream f(filename);

        f >> n;
        adjacencyMatrix = makeAdjacencyMatrix(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                f >> adjacencyMatrix[i][j];
            }
        }
        printAdjacencyMatrix(adjacencyMatrix, n);
        std::cout<<std::endl;
        for(int i = 0; i< n; ++i){
            for(int j = i; j<n; ++j){
                if(adjacencyMatrix[i][j] == 1)
                    ++m;
            }
        }
    }

    while(choice) {
        std::cout<<"What u want to do next?"<<std::endl;
        std::cout<<"0 - Exit"<<std::endl;
        std::cout<<"1 - Show adjacency list"<<std::endl;
        std::cout<<"2 - Show incidence matrix"<<std::endl;
        std::cout<<"3 - Draw graph"<<std::endl;
        std::cin >> choice;
        switch (choice) {
            case 1:
                adjacencyList = adjacencyToList(adjacencyMatrix, n);
                printAdjacencyList(adjacencyList, n);
                break;
            case 2:
                incidenceMatrix = adjacencyToIncidence(adjacencyMatrix, n);
                printIncidenceMatrix(incidenceMatrix, n, m);
                break;
            case 3:
                //drawGraph(adjacencyMatrix, n);
                break;
            default:
                std::cout << "You chose the wrong value";
        }

    }
    return 0;
}
