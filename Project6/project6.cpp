#include "project6.h"

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

void Simulated_annealing(int** V, int n)
{
    const int MAX_IT = 15000;
    double T;
    double dP_new, dP, r;

    int* P = new int[n+1];
    int* P_new = new int[n+1];

    getDefaultCycle(P, n);

    std::cout << "Length before = " << cycleLength(P, V, n) << "\n";

    for(int i=100; i>=1; i--)
    {
        T = 0.001*i*i;

        for(int it=0; it < MAX_IT; it++)
        {

            memcpy(P_new, P, sizeof(int)*(n+1));

            shuffleVertex(P, n);

            dP_new = cycleLength(P_new, V, n);
            dP = cycleLength(P, V, n);

            if(dP_new < dP){
                memcpy(P, P_new, sizeof(int)*(n+1));
            }
            else{
                r = ((double) rand() / (RAND_MAX));
                if(r < exp((-1) * (dP_new - dP) / T)){
                    memcpy(P, P_new, sizeof(int)*(n+1));
                }
            }
        }
    }

    std::cout << "Length after = " << cycleLength(P, V, n) << "\n";

    std::ofstream myfile ("cycle.dat");

    if (myfile.is_open())
    {
      for(int i = 0; i <= n; i ++){
          myfile << P[i] << "\n" ;
      }
      myfile.close();
    }
}

void getDefaultCycle(int* P, int n)
{
    for(int i = 0; i < n; i++){
        P[i] = i;
    }

    P[n] = 0;
}

void shuffleVertex(int* P, int n)
{
    int a, b, c, d;

    do{
        a = rand() % (199 - 1) + 1;
        b = a + 1;

        c = rand() % (199 - 1) + 1;
        d = c + 1;

        if(a != b && b != c && d != a)
        {
            int tmp = P[b];
            P[b] = P[c];
            P[c] = tmp;
            break;
        }

    }while(true);
}

*
double cycleLength(int* P, int** V, int n)
{
    double l = 0;
    double x1, x2, y1, y2;

    for(int i = 0; i < n; i++)
    {
        x1 = V[P[i]][0];
        y1 = V[P[i]][1];
        x2 = V[P[i+1]][0];
        y2 = V[P[i+1]][1];
        l += sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    }

    x1 = V[P[n]][0];
    y1 = V[P[n]][1];
    x2 = V[P[0]][0];
    y2 = V[P[0]][1];
    l += sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

    return l;
}
*/

double cycleLength(int* P, int** V, int n)
{
    double l = 0;
    double x1, x2, y1, y2;

    for(int i = 0; i < n; i++)
    {
        x1 = V[P[i]][0];
        y1 = V[P[i]][1];
        x2 = V[P[i+1]][0];
        y2 = V[P[i+1]][1];
        l += sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    }

    x1 = V[P[n]][0];
    y1 = V[P[n]][1];
    x2 = V[P[0]][0];
    y2 = V[P[0]][1];
    l += sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));

    return l;
}
