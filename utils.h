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
void dijkstra(int** ,int ,int );
void dijkstra(int** ,int ,int, int* );

float r_prob();
std::list<int>* DiAdjacencyToList(int**, int);


//Maciek pr. 1 ex. 2
bool file_exist(const char*);

//Maciek pr. 2 ex. 1
bool GraphSeq_check(int *seq, int size);
void swap(int *xp, int *yp);
void sort_seq(int** seq, int size);
int** GraphSeq_to_AdjacencyMatrix(const int* seq_graph, int size);

//Maria pr.2
void components_R(int nr, int v, int** adjM, std::vector<int>& comp, int size);
std::vector<int> components(int* seq, int size);
int count_components(int** adjM, int n);

/*
function checking if edge between two vertices is a bridge
arguments: adjacency matrix, size - number of vertices
v - index of first vertex,
u - index of second vertex
*/
bool is_bridge(int** adjM, int size, int v,int u);

/* arguments: adjacency matrix, n - number of vertices,
v - current vertex, which neighbour we're looking for,
nr - number of neighbour we're looking for (e.g. in case previous is a bridge) */
int next_neighbour(int** adjM,int n,int v,int& nr);
void addEdge(int v, int u, int** adjM);
void removeEdge(int v, int u, int** adjM);



//Dawid pr.2
//funkcja sprawdzajaca czy da sie stworzyc graf regularny o zadanej liczbie wierzcholkow i stopni
bool isPossible(int n, int k);

bool CanAdd(int n, int** graph, int* cycle, int p, int v);


//Maria proj 4

std::vector<int> Kosaraju(int** adjM, int n);
void DFS_visit(int v,int** adjM, std::vector<int>& d, std::vector<int>& f, int& t, int n);
int** transpose(int** adjM, int n);
int max_ind(std::vector<int>& vec);