#pragma once

//funkcja sprawdzajaca czy da sie stworzyc graf regularny o zadanej liczbie wierzcholkow i stopni
bool isPossible(int n, int k);

//generuje graf regularny o n wierzcholkach i stopniu k
int** GenerateRegularGraph(int n, int k);