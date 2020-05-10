#pragma once

#include "utils.h"
#include <algorithm>

int** randomDiGraph(int& n);
int componentsWithKosaraju(int**, int);
//void BellmanFord(int**, int);
void BellmanFord(int[][3], int, int);
void Exercise4();
