#include<iostream>
#include "lab2zd6.h"

using namespace std;

int main(void){
    int n;
    cout<<"Podaj ilosc wezlow:"<<endl;
    cin>>n;
    int ** graph = new int*[n];
    for(int i = 0; i < n; i++) 
        graph[i] = new int[n];
    cout<<"wprowadz macierz sąsiedztwa"<<endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin>>graph[i][j];
    }
    int* cycle = new int[n];
    cycle = Hamilton(n, graph);
    if(cycle != nullptr){
        for(int i = 0; i < n; i++){
            cout<<cycle[i]<<", ";
    }
    cout<<cycle[0]<<endl;
    }
    else
    cout<<"cykl nie istnieje"<<endl;
    delete[] cycle;
    for(int i = 0; i < n; i++)
        delete[] graph[i];
    delete[] graph;
    return 0;
}