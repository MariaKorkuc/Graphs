#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include "utils.h"
#include <conio.h>
#include <fstream>
#define D 0.15
#define E 1e-5


// EX. 1
//WEJŚCIE - MECIERZ SASIEDZTWA
int random_vertex(int u, int** adjM, int n, bool neighbour = true);
double** make_P_matrix(int** adjM, int n);
void print_PageRank(std::vector<double> visited, int n);
bool stop_condition(std::vector<double> position, std::vector<double> prev, int n);
std::vector<double> multiplication(std::vector<double> position, double** P, int n);
bool check_for_zero_vertices(int** adjM, int n);
void PageRank_1(int** adjM, int n);
void PageRank_2(int** adjM, int n);


// EX. 2
void Simulated_annealing(int** V, int n);
void getDefaultCycle(int* P, int n);
void shuffleVertex(int* P, int n);
double cycleLength(int* P, int** V, int n);
