#include "utils.h"
#include <graphics.h>
#include <math.h>
#include <fstream>

int main()
{
    char node[10];
    int count;
    char *filename;

    std::cout << "Data source(adjacency matrix): ";
    std::cin >> filename;

    if(file_exist(filename) == false)
    {
        std::cout << "File does not exist.\n";
        exit(EXIT_FAILURE);
    }

    /*
    reading file with adjacency matrix (first number is the size of NxN matrix) of format
    e.g.
    5
    0 0 1 0 1
    0 0 1 1 0
    1 1 0 1 0
    0 1 1 0 1
    1 0 0 1 0
    */

    std::ifstream f(filename);
    f >> count;

    int** adjacencyMatrix = makeAdjacencyMatrix(count);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            f >> adjacencyMatrix[i][j];
        }
    }

    initwindow(1200,1000);
    int xC = 600;
    int yC = 500;

    settextstyle(8 , 0 , 5);

    for(int i = 0; i < count; i++)
    {
        sprintf(node, "%d", i+1);
        circle(xC + 350 * cos(2*M_PI/count * i), yC + 350 * sin(2*M_PI/count * i), 5);
        outtextxy(xC + 400 * cos(2*M_PI/count * i), yC + 400 * sin(2*M_PI/count * i), node);
    }

    for(int i = 0; i < count; i++)
    {
        for(int j = 0; j < count; j++)
        {
            if(adjacencyMatrix[i][j] == 1)
            {
                line(xC + 350 * cos(2*M_PI/count * i), yC + 350 * sin(2*M_PI/count * i), xC + 350 * cos(2*M_PI/count * j), yC + 350 * sin(2*M_PI/count * j));
            }
        }
    }

    getch();

    getchar();
    return 0;
}
