#pragma once

#include <list>

//Wiktor pr. 1 ex. 1
int** makeAdjacencyMatrix(int);
int** makeIncidenceMatrix(int, int);
std::list<int>* makeAdjacencyList(int);
void printAdjacencyMatrix(int**, int);
void printIncidenceMatrix(int**, int, int);
void printAdjacencyList(std::list<int>*, int);



//Maciek pr. 1 ex. 2
bool file_exist(const char*);

//Maria pr.1 ex.3
float r_prob();
