# pragma once

#include<iostream>

void printCentrumAndMinmax(int ** distanceMatrix, int size){
    int * sum_distance = new int[size];
    int * min_distance = new int[size];


    for(int j = 0; j < size; j++){
        sum_distance[j] = 0;
        min_distance[j] = distanceMatrix[j][0];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            sum_distance[i] += distanceMatrix[i][j];
            if(distanceMatrix[i][j] >= min_distance[i]) min_distance[i] = distanceMatrix[i][j];
        }
    }

    int centrum = 0;
    int minmax = 0;

    for(int i = 0; i < size; i++){
        if(sum_distance[i] <= sum_distance[centrum]) centrum = i;
        if(min_distance[i] <= min_distance[minmax]) minmax = i;
    }

    std::cout<<"Centrum = "<<centrum<<" (suma odleglosci: "<<sum_distance[centrum]<<")\n";
    std::cout<<"Centrum minimax= "<<minmax<<" (odleglosc od najdalszego: "<<min_distance[minmax]<<")\n";


}