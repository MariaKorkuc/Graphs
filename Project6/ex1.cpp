#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>
#include "utils.h"
#include <conio.h>
#define D 0.15
#define E 1e-5

//WEJŚCIE - MECIERZ SASIEDZTWA

int random_vertex(int u, int** adjM, int n, bool neighbour = true);
double** make_P_matrix(int** adjM, int n);
void print_PageRank(std::vector<double> visited, int n);
bool stop_condition(std::vector<double> position, std::vector<double> prev, int n);
std::vector<double> multiplication(std::vector<double> position, double** P, int n);
bool check_for_zero_vertices(int** adjM, int n);
void PageRank_1(int** adjM, int n);
void PageRank_2(int** adjM, int n);

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int n = 0;
    int** adjM;
    char* filename = get_filename(argc,argv);

    if(!file_exist(filename)){
       std::cout<<" File doesn't exist!";
    }
    else{
        std::ifstream inFile(filename);
        n = std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n');
        n++;
        std::cout<<n<<std::endl;
        
        std::ifstream f(filename);
        adjM = makeAdjacencyMatrix(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                f >> adjM[i][j];
            }
        }

        printAdjacencyMatrix(adjM, n);
        std::cout<<std::endl;
    }
    
    if(check_for_zero_vertices(adjM,n))
    {
        std::cout<<"Cannot make a PageRank from this graph\n";
        exit(EXIT_FAILURE);
    }

    char c;

    do{
        std::cout<<"Choose the Page Rank:\n(ESC terminates program)\n";
        std::cout<<"1 - Random\n";
        std::cout<<"2 - With position vector\n";

        c = getch();
        if(c == 27) break;
        if(c == '1')
        {
            std::cout<<"Page Rank - 1:\n";
            PageRank_1(adjM,n);
        }
        else if(c == '2')
        {
            std::cout<<"\nPage Rank - 2:\n";
            PageRank_2(adjM,n);
        }

    }while(true);

    



    return 0;
}


bool check_for_zero_vertices(int** adjM, int n)
{
    bool zero;

    for(int i=0; i<n; i++)
    {
        zero = true;

        for(int j=0; j<n; j++)
        {
            if(adjM[i][j])
            {
                zero = false;
                break;
            }
        }

        if(zero) break;
    }

    return zero;
}

void PageRank_1(int** adjM, int n)
{
    std::vector<int> visited(n);
    std::vector<double> position(n);
    std::fill(visited.begin(),visited.end(),0);
    int u = rand()%n;

    for(int i=0; i<n; i++)
    {
        visited[u]++;

        double d = r_prob();
        
        if(d <= D)
        {
            u = random_vertex(u,adjM,n);
        }
        else
        {
            u = random_vertex(u,adjM,n,true);
        }
    }

    for(int j=0; j<n; j++)
    {
        position[j] = double(visited[j])/double(n);
    }

    print_PageRank(position,n);
}

void PageRank_2(int** adjM, int n)
{    
    double** P = make_P_matrix(adjM,n);
    // printAdjacencyMatrix(P,n);

    std::vector<double> position(n);
    std::vector<double> prev(n);
    std::fill(position.begin(), position.end(), 1./double(n));

    int control = 0;

    do
    {
        std::copy(position.begin(), position.end(), prev.begin());
        position = multiplication(position,P,n);
        control++;
    }while(!stop_condition(position, prev, n) && control < 2000);

    std::cout<<"Control value = "<<control<<std::endl;

    if(control == 2000)
    {
        for(int i=0; i<n; i++)
        {
            position[i] = (position[i] + prev[i])/2.;
        }
    }

    for(int i=0; i<n; i++)
    {
        delete [] P[i];
    }

    print_PageRank(position,n);

}


int random_vertex(int u, int** adjM, int n, bool neighbour)
{
    srand(time(NULL));
    int r;
    
    do
    {
        r = rand()%n;
        if(neighbour)
        {
            //checking if r is u's neighbour - if not, then assign u to r, so that the loop continues
            r = adjM[u][r] ? r : u;
        }

    }while(r == u);

    return r;
}

double** make_P_matrix(int** adjM, int n)
{
    double** P = new double*[n];
    for(int i=0; i<n; i++) 
    {
        P[i] = new double[n];
    }
    
    int di;

    for(int i=0; i<n; i++)
    {
        di = std::count(adjM[i], adjM[i] + n, 1);
        for(int j=0; j<n; j++)
        {
            P[i][j] = (1-D) * double(adjM[i][j])/double(di) + D/double(n);
        }
    }

    return P;
}

void print_PageRank(std::vector<double> vec, int n)
{
    std::vector<double> cvec(n);
    std::copy(vec.begin(),vec.end(),cvec.begin());
    int i=0;
    int imax;

    while(i < n)
    {
        imax = max_ind(cvec);
        std::cout<<imax+1<<" ==> PageRank = "<<vec[imax]<<std::endl;
        cvec[imax] = -1;
        i++;
    }

    std::cout<<std::endl;
}

bool stop_condition(std::vector<double> position, std::vector<double> prev, int n)
{
    double suma1 = 0;
    double suma2 = 0;

    for(int i=0; i<n; i++)
    {
        suma1 += pow(position[i],2);
        suma2 += pow(prev[i],2);
    }

    if(fabs(sqrt(suma1) - sqrt(suma2)) <= E) return true;

    return false;

}

std::vector<double> multiplication(std::vector<double> position, double** P, int n)
{
    std::vector<double> ans(n);
    double val = 0;

    for(int i=0; i<n; i++)
    {
        val = 0;
        for(int j=0; j<n; j++)
        {
            val += position[j]*P[j][i];
        }
        ans[i] = val;
    }

    return ans;
}