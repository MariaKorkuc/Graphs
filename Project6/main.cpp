#include "project6.h"

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int n = 0;
    int** adjM;
    char c;

    do{
        std::cout<<"1 - PageRank\n";
        std::cout<<"2 - Travelling salesman problem\n";

        c = _getch();
        if(c == 27) break;
        if(c == '1')
        {
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
        }
        if(c == '2')
        {
            char* filename = get_filename(argc,argv);

            if(!file_exist(filename)){
               std::cout<<" File doesn't exist!";
            }
            else{

                int n = 0;
                std::ifstream inFile(filename);
                n = std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n');

                std::ifstream f(filename);

                int** V=new int*[n];
                for (int i = 0; i < n; ++i)
                {
                    V[i] = new int[2];
                }

                for (int i = 0; i < n; i++){
                    f >> V[i][0];
                    f >> V[i][1];
                }



                Simulated_annealing(V, n);
            }
        }

    }while(true);

    return 0;
}
