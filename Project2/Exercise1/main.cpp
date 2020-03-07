#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

bool GraphSeq_check(int *seq, int size)
{
    int* seq_copy = new int[size];
    for(int i = 0; i < size; i++)
        seq_copy[i] = seq[i];

    int odd = 0;
    for(int i = 0; i < size; i++)
    {
        if(seq_copy[i] % 2 == 1) odd++;
    }

    // If number of odd elements in the sequence is odd - it's not graphical sequence
    if(odd % 2 == 1)
    {
        return false;
    }

    sort(seq_copy, seq_copy+size, greater<int>());

    while(true)
    {
        // If all elements in the sequence are 0 - it's graphical sequence
        bool zeros = true;
        for(int i = 0; i < size; i++)
        {
            if(seq_copy[i] != 0)
            {
                zeros = false;
                break;
            }
        }
        if(zeros == true) return true;

        // If there is negative element in the sequence - it's not graphical sequence
        bool negative = false;
        for(int i = 1; i < size; i++)
        {
            if(seq_copy[i] < 0)
            {
                negative = true;
                break;
            }
        }
        if(negative == true || seq_copy[0] < 0 || seq_copy[0] >= size) return false;


        for(int i = 1; i <= seq_copy[0]; i++)
        {
            seq_copy[i] -= 1;
        }
        seq_copy[0] = 0;

        sort(seq_copy, seq_copy+size, greater<int>());
    }
}

int** GraphSeq_to_AdjacencyMatrix(int* seq_graph, int size)
{

    int** adjMatrix = new int*[size];
    int* seq = new int[size];

    for(int i = 0; i < size; i++)
    {
        seq[i] = seq_graph[i];
        adjMatrix[i] = new int[size];
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }


    int i = 0, j = size-1;
    while(true)
    {
        if(seq[i] == 0) i++;
        else break;
    }

    while(true)
    {
        if(seq[j] == 0) j--;
        else break;
    }


    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;
    seq[i]--;
    seq[j]--;


    for(int i = 0; i < size; i++)
    {
        for(int j = i+1; j < size; j++)
        {
            if(seq[i] == 0) break;
            if(i != j && seq[i] != 0 && seq[j] != 0 && adjMatrix[i][j] != 1 && adjMatrix[j][i] != 1)
            {
                adjMatrix[i][j] = 1;
                adjMatrix[j][i] = 1;
                seq[i]--;
                seq[j]--;
            }
        }
    }

    for(int i = 0; i < size; i++)
    {
        if(seq[i] != 0)
        {
            random_shuffle(&seq_graph[0], &seq_graph[size]);
            GraphSeq_to_AdjacencyMatrix(seq_graph, size);
        }
    }

    return adjMatrix;
}

int main()
{
    int seq[] = {2,2,4,3,2,1,4,2,2,2,2};
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


