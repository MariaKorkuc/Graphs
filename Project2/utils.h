#pragma once

#include <list>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>

//Wiktor pr. 1 ex. 1
int** makeAdjacencyMatrix(int);
int** makeIncidenceMatrix(int, int);
std::list<int>* makeAdjacencyList(int);
void printAdjacencyMatrix(int**, int);
void printIncidenceMatrix(int**, int, int);
void printAdjacencyList(std::list<int>*, int);



//Maciek pr. 1 ex. 2
bool file_exist(const char*);

//Maciek pr. 2 ex. 1
bool GraphSeq_check(int *seq, int size);
void swap(int *xp, int *yp);
void sort_seq(int** seq, int size);
int** GraphSeq_to_AdjacencyMatrix(const int* seq_graph, int size);

//Maria pr.1 ex.3
float r_prob();
void components_R(int nr, int v, int** adjM, std::vector<int>& comp, int size);
std::vector<int> components(int* seq, int size);
int count_components(int** adjM, int n);