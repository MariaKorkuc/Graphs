#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

int main()
{
    int seq[] = {4, 2, 2, 3, 2, 1, 4, 2, 2, 2, 2};
    int size = (sizeof(seq)/sizeof(seq[0]));
    if(GraphSeq_check(seq,size))
    {
        cout << "Ciag: ";
        for(int i = 0; i < size; i++)
        {
            cout << seq[i] << " ";
        }
        cout << " jest ciagiem graficznym." << endl;

        int** m = GraphSeq_to_AdjacencyMatrix(seq, size);

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                cout << m[i][j] << " ";
            }

            cout << endl;
        }

    }
    else
    {
        cout << "Ciag: ";
        for(int i = 0; i < size; i++)
        {
            cout << seq[i] << " ";
        }
        cout << " nie jest ciagiem graficznym." << endl;
    }

    return 0;
}