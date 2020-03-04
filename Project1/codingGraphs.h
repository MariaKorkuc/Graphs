#pragma once

#include "utils.h"

void setData(int&, int&);
void encode(int**, int, int);
void clear(int**, int**, std::list<int>*, int, int);

int** adjacencyToIncidence(int** , const int&);
int** incidenceToAdjacency(int** , const int&, const int&);
int** listToAdjacency(std::list<int>*, const int&);
std::list<int>*  adjacencyToList(int** , const int&);
std::list<int>* incidenceToList(int** , const int&, const int&);
int** listToIncidence(std::list<int>* , const int&, const int&);