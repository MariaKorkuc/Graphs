#include "lab2zd5.h"
#include <iostream>

using namespace std;

bool isPossible(int n, int k){
    if(n >= k + 1 && (n * k) % 2 == 0) return true;
    return false;
}

 int** GenerateRegularGraph(int n, int k){
    int ** graph = new int*[n];
    for(int i = 0; i < n; i++)
        graph[i] = new int[k];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < k/2; j++){
                graph[i][j] = (i + j + 1) % n;
                if(i - j - 1 >= 0)
                    graph[i][k - j - 1] = i - j - 1;
                else
                    graph[i][k - j - 1] = n + i - j - 1;
            }
            if(k % 2 != 0) graph[i][k/2] = (i + n/2) % n;
        }
    return graph;
 }