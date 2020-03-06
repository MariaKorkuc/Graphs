#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <iterator>
#include <vector>
#include "utils.h"
#include "codingGraphs.h"
#include "circle_graph.h"
#include "RandomGraph.h"

int main(int argc, char* argv[]) {
    int n, m = 0;
    int **adjacencyMatrix, **incidenceMatrix;
    std::list<int>* adjacencyList;
    char node[10];
    int count;
    int laterChoice = -1;
    char *filename;
    int fileType;

    if(strncmp("random", argv[1], 6) == 0){
        char choice;

        do{
            std::cout<<"Choose model of random graph: "<<std::endl<<"Type 'p' for G(n,p) graph, 'm'  for G(n,m) graph: ";
            choice = getchar();

            if(choice == 'p')
            {
                make_probability_graph();
            }
            else if(choice == 'm')
            {
                make_random_graph();
            }
            else
            {
                std::cout<<"Choose available option"<<std::endl;
            }
        }while(choice != 'p' && choice != 'm');

        return 0;
    }

    else {
        filename = argv[1];

        if (!file_exist(filename)) {
            setData(n, m);
            adjacencyMatrix = makeAdjacencyMatrix(n);
            encode(adjacencyMatrix, n, m);
            printAdjacencyMatrix(adjacencyMatrix, n);
            std::cout << std::endl;
        } else {
            std::ifstream f(filename);
            std::cout<<"What type of encoding is in the file?"<<std::endl;
            std::cout<<"1 - Adjacency matrix"<<std::endl;
            std::cout<<"2 - Incidence matrix"<<std::endl;
            std::cout<<"3 - Adjacency list"<<std::endl;
            std::cin>>fileType;

            switch(fileType) {
                case 1:
                    n = std::count(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>(), '\n');
                    ++n;
                    f.clear();
                    f.seekg(0, std::ios::beg);
                    adjacencyMatrix = makeAdjacencyMatrix(n);
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            f >> adjacencyMatrix[i][j];
                        }
                    }
                    m = countEdges(adjacencyMatrix, n);

                    std::cout << std::endl;

                    adjacencyList = adjacencyToList(adjacencyMatrix, n);
                    incidenceMatrix = adjacencyToIncidence(adjacencyMatrix, n);
                    break;
                case 2:
                    n = std::count(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>(), '\n');
                    ++n;
                    f.clear();
                    f.seekg(0, std::ios::beg);
                    m = std::count(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>(), ' ');
                    m = m+n;
                    m = m/n;
                    f.clear();
                    f.seekg(0, std::ios::beg);
                    incidenceMatrix = makeIncidenceMatrix(n,m);
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < m; j++) {

                            f >> incidenceMatrix[i][j];
                        }

                    }
                    //printIncidenceMatrix(incidenceMatrix,n,m);
                    std::cout<<n<<" "<<m << std::endl;

                    adjacencyMatrix = incidenceToAdjacency(incidenceMatrix, n, m);
                    adjacencyList = incidenceToList(incidenceMatrix, n, m);


                    break;
                case 3:
                    n = std::count(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>(), '\n');
                    //++n;
                    f.clear();
                    f.seekg(0, std::ios::beg);
                    adjacencyList = makeAdjacencyList(n);
                    m = 0;
                    for(int i = 0; i<n; ++i) {
                        std::string myString;
                        std::getline (f, myString);

                        std::istringstream iss(myString);
                        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                                         std::istream_iterator<std::string>());
                        for (unsigned j=1; j<results.size(); j++) {
                            ++m;
                            adjacencyList[i].push_back(stoi(results[j]) - 1);
                        }
                    }
                    m=m/2;
                    adjacencyMatrix = listToAdjacency(adjacencyList,n);
                    incidenceMatrix = listToIncidence(adjacencyList, n,m);
                    break;
                default:
                    std::cout << "You chose the wrong value";
                    exit(EXIT_FAILURE);

            }
        }
    }
    while(laterChoice) {
        std::cout<<"What u want to do next?"<<std::endl;
        std::cout<<"0 - Exit"<<std::endl;
        std::cout<<"1 - Show adjacency matrix"<<std::endl;
        std::cout<<"2 - Show adjacency list"<<std::endl;
        std::cout<<"3 - Show incidence matrix"<<std::endl;
        std::cout<<"4 - Draw graph"<<std::endl;
        std::cin >> laterChoice;
        switch (laterChoice) {
            case 1:
                printAdjacencyMatrix(adjacencyMatrix,n);
                break;
            case 2:

                printAdjacencyList(adjacencyList, n);
                break;
            case 3:
                printIncidenceMatrix(incidenceMatrix, n, m);
                break;
            case 4:
                //drawGraph(adjacencyMatrix, n);
                break;
            default:
                std::cout << "You chose the wrong value";
        }

    }
    return 0;
}

