//#include "circle_graph.h"
//#include <cmath>
//
//void drawGraph(int** adjacencyMatrix, int count){
//    initwindow(1200,1000);
//    int xC = 600;
//    int yC = 500;
//
//    settextstyle(8 , 0 , 5);
//
//    for(int i = 0; i < count; i++)
//    {
//        sprintf(node, "%d", i+1);
//        circle(xC + 350 * cos(2*M_PI/count * i), yC + 350 * sin(2*M_PI/count * i), 5);
//        outtextxy(xC + 400 * cos(2*M_PI/count * i), yC + 400 * sin(2*M_PI/count * i), node);
//    }
//
//    for(int i = 0; i < count; i++)
//    {
//        for(int j = 0; j < count; j++)
//        {
//            if(adjacencyMatrix[i][j] == 1)
//            {
//                line(xC + 350 * cos(2*M_PI/count * i), yC + 350 * sin(2*M_PI/count * i), xC + 350 * cos(2*M_PI/count * j), yC + 350 * sin(2*M_PI/count * j));
//            }
//        }
//    }
//}