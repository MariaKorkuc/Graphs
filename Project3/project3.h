#pragma once
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <random>

#include "utils.h"

int** ConsistentRandomGraph(int);
void Dijkstra(int**, int, int);
void Dijkstra(int**,int, int, int*);
void PrintWithPath(int[], int, int[], int);
void PrintParent(int[], int);
int MinimumDistance(const int*, int, const bool*);
void PrintCentrumAndMinmax(int**, int);
void KruskalMST(int**, int);
void Union(int[], int, int);
int Find(int[], int);

