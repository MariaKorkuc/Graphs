#include <iostream>
#include "project3.h"
#include <conio.h>

std::vector<int> get_sequence(int n1, char* argv[]);
char* get_filename(int n, char* argv[]);

int main(int argc, char* argv[])
{
    std::cout<<"************Project 3************\n";
    int choice;
    char c;
    bool matrixInitialized = false;
    bool distanceMatrixInitialized = false;
    int **importanceMatrix;
    int **distanceMatrix;
    int size;
    int vertex;

    do{
        std::cout<<"Choose the task:\n(ESC terminates program)\n";
        std::cout<<"1 - Consistent random graph\n";
        std::cout<<"2 - Read graph from file\n";
        std::cout<<"3 - Dijkstra\n";
        std::cout<<"4 - Distance matrix\n";
        std::cout<<"5 - Graph center\n";
        std::cout<<"6 - Minimal spanning tree (Kruskal)\n";

        c = _getch();
        if(c == 27) break;

        choice = int(c) - int('0');
        std::cout<<choice<<std::endl;
        std::vector<int> seq;
        char* filename;

        switch(choice)
        {
            case 1:
                std::cout<<"Insert matrix size:";
                std::cin>>size;
                importanceMatrix = ConsistentRandomGraph(size);
                matrixInitialized = true;
                break;
            case 2:
                filename = get_filename(argc,argv);
                importanceMatrix = ReadMatrixFromFile(filename, size);
                printAdjacencyMatrix(importanceMatrix, size);
                matrixInitialized = true;
                break;
            case 3:
                if(matrixInitialized) {
                    std::cout<<"Insert vertex number:";
                    std::cin>>vertex;
                    Dijkstra(importanceMatrix, size, vertex);
                }
                else {
                    std::cout<<"Graph not initialized. Initialize with 1 or 2 task."<<std::endl;
                }

                break;
            case 4:
                if(matrixInitialized) {
                    distanceMatrix = makeAdjacencyMatrix(size);
                    for(int i = 0; i < size; ++i){
                        Dijkstra(importanceMatrix, size, i, distanceMatrix[i]);
                    }
                    distanceMatrixInitialized = true;
                    printAdjacencyMatrix(distanceMatrix,size);
                }
                else {
                    std::cout<<"Graph not initialized. Initialize with 1 or 2 task."<<std::endl;
                }

                break;
            case 5:
                if(distanceMatrixInitialized){
                    PrintCentrumAndMinmax(distanceMatrix, size);
                }
                else {
                    std::cout<<"Distance matrix not initialized. Initialize with 4 task."<<std::endl;
                }

                break;
            case 6:
                if(matrixInitialized){
                    KruskalMST(importanceMatrix, size);
                }
                else {
                    std::cout<<"Graph not initialized. Initialize with 1 or 2 task."<<std::endl;
                }

                break;

            default:
                std::cout<<"Not an option, try again\n";
                break;
        }


    }while(true);

    return 0;
}

std::vector<int> get_sequence(int n1, char* argv[])
{
    int size = n1;
    char* filename;
    int n = 0;
    int temp;
    std::vector<int> seq;

    if(size < 2)
    {
        std::cout<<"Insert sequence's length: ";
        std::cin>>n;
        std::cout<<"\nInsert sequence:\n";
        for(int i=0; i<n; i++)
        {
            std::cin>>temp;
            seq.push_back(temp);
        }
    }
    else
    {
        filename = argv[1];

        if(!file_exist(filename)){
        std::cout<<" File doesn't exist!";
        }
        else{
            std::ifstream f(filename);

            while(f >> temp)
            {
                n++;
                seq.push_back(temp);
            }
        }
    }

    return seq;
}

char* get_filename(int n, char* argv[])
{
    int size = n;
    char* filename = new char;

    if(size<2)
    {
        std::cout<<"Insert path to file:\n";
        std::cin >> filename;
    }
    else
    {
        filename = argv[1];
    }

    if(!file_exist(filename)){
        std::cout<<" File doesn't exist!";
        exit(EXIT_FAILURE);
        }

    return filename;
}
