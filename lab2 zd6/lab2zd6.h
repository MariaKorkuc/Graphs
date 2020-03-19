#pragma once

using namespace std;

bool CanAdd(int n, int** graph, int* cycle, int p, int v){
    if(graph[v][cycle[p - 1]] == 0)
        return 0;
    for(int i = 0; i < p; i++){
        if(cycle[i] == v) return 0;
    }
    return 1;
}

bool fun1(int n, int** graph, int* cycle, int p){
    //sprawdza czy w cyklu sa wszystkie wierzcholki jesli tak to sprawdza czy ostatni ma polaczenie z pierwszym
    if(p == n){
        if(graph[cycle[0]][cycle[n - 1]] == 1)
            return 1;
        else
            return 0; 
    }
    //sprawdza czy mozna dodac kolejny wiercholek oprocz zerwoego bo on juz jest
    //jesli mozna to dodaje i uruchamia funkcje dla kolejnego wierzcholka
    for(int i = 1; i < n; i++){
        if(CanAdd(n, graph, cycle, p, i)){
            cycle[p] = i;
            if(fun1(n, graph, cycle, p + 1))
                return 1;
            cycle[p] = -1;
        }
    }
    return 0;
}

int* Hamilton(int n, int** graph){
    int* cycle = new int[n];
    for(int i = 0; i < n; i++)
        cycle[i] = -1;

    cycle[0] = 0;

    if(fun1(n, graph, cycle, 1) == 1)
        return cycle;
    else{
        delete[] cycle;
        return nullptr;}
}
