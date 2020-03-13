#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>
#include "utils.h"


int main(int argc, char* argv[]) {

    int** adjacencyMatrix;
    int m = 0;
    int a,b,c,d;
    char* filename = argv[1];
    std::ifstream inFile(filename);
    int n = std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n');
    n++;
    std::cout<<n;

    // randomize
    if(!file_exist(filename)){
       std::cout<<" File doesn't exist!";
    }
    else{
        std::ifstream f(filename);
        adjacencyMatrix = makeAdjacencyMatrix(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                f >> adjacencyMatrix[i][j];
            }
        }

        printAdjacencyMatrix(adjacencyMatrix, n);
        std::cout<<std::endl;
    }
    int rand;
    std::cout<<"Set random number"<<std::endl;
    std::cin>>rand;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, n);
    for(int i = 0; i < rand; ++i){
        a = int(dist(mt));
        b = int(dist(mt));
        c = int(dist(mt));
        d = int(dist(mt));
        if(a!=b and a != c and a!=d and b!=c and b!=d and c!=d){
            if(adjacencyMatrix[a][b] and adjacencyMatrix[c][d]){

                if(adjacencyMatrix[a][d] == 0 and adjacencyMatrix[b][c] == 0){
                    std::cout<<a<<" "<<b<<" "<<c<<" "<<d<<std::endl;
                    adjacencyMatrix[a][d] = 1;
                    adjacencyMatrix[b][c] = 1;
                    adjacencyMatrix[a][b] = 0;
                    adjacencyMatrix[c][d] = 0;
                }
                else{
                    --i;
                }
            }
            else{
                --i;
            }
        }
        else{
            --i;
        }
    }

    printAdjacencyMatrix(adjacencyMatrix, n);
    std::cout<<std::endl;

}


