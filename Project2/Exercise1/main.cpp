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

    while(true)
    {
        sort(seq_copy, seq_copy+size, greater<int>());

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

    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort_seq(int** seq, int size)
{
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size-i-1; j++)
        {
            if (seq[j][1] < seq[j+1][1])
            {
                swap(&seq[j][0], &seq[j+1][0]);
                swap(&seq[j][1], &seq[j+1][1]);
            }
        }
    }
}

int** GraphSeq_to_AdjacencyMatrix(int* seq_graph, int size)
{

    int** adjMatrix = new int*[size];
    int** seq = new int*[size];

    for(int i = 0; i < size; i++)
    {
        seq[i] = new int[2];
        seq[i][0] = i;
        seq[i][1] = seq_graph[i];
        adjMatrix[i] = new int[size];
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            adjMatrix[i][j] = 0;
        }
    }

    while(true)
    {
        sort_seq(seq, size);

        if(seq[0][1] == 0)
            break;

        int x,y,j = 1;

        while(seq[0][1] > 0)
        {
            x = seq[0][0];
            y = seq[j][0];

            if(seq[j][1] != 0 && adjMatrix[x][y] != 1 && adjMatrix[y][x] != 1)
            {
                adjMatrix[x][y] = 1;
                adjMatrix[y][x] = 1;
                seq[0][1]--;
                seq[j][1]--;
            }

            j++;
        }
    }

    return adjMatrix;
}

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


