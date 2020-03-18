#include <iostream>
#include "lab2zd5.h"

using namespace std;

int main(void){
    int n,k;
    cin>>n>>k;
    if(isPossible(n, k)){
        int** graph;
        graph = GenerateRegularGraph(n, k);
            for(int i = 0; i < n; i++){
            cout<<i<<": ";
            for(int j = 0; j < k; j++){
                cout<<graph[i][j]<<", ";
            }
            cout<<endl;
        }
    }
    else{
        cout<<"zle dane wejsciowe"<<endl;
    }
    return 0;
}
