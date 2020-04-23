#include "project2.h"
#define STOP 150

int* get_arr(std::vector<int> arr)
{
    int* seq = new int[arr.size()];

    for(unsigned int i=0; i<arr.size(); i++)
    {
        seq[i] = arr[i];
    }

    return seq;
}

void checkSequence(std::vector<int> seq1)
{
    // seq = {4, 2, 2, 3, 2, 1, 4, 2, 2, 2, 2};
    int size = seq1.size();

    int* seq = get_arr(seq1);

    // std::cout<<"size = "<<size<<std::endl;
    if(GraphSeq_check(seq,size))
    {
        std::cout << "Ciag: ";
        for(int i = 0; i < size; i++)
        {
            std::cout << seq[i] << " ";
        }
        std::cout << " jest ciagiem graficznym." << std::endl;

        int** m = GraphSeq_to_AdjacencyMatrix(seq, size);

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                std::cout << m[i][j] << " ";
            }

            std::cout << std::endl;
        }

    }
    else
    {
        std::cout << "Ciag: ";
        for(int i = 0; i < size; i++)
        {
            std::cout << seq[i] << " ";
        }
        std::cout << " nie jest ciagiem graficznym." << std::endl;
    }
}

void randomizeMatrix(char* filename)
{
    int** adjacencyMatrix;
    // int m = 0;
    int a,b,c,d;

    std::ifstream inFile(filename);
    int n = std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n');
    n++;
    std::cout<<n;

    // randomize
    if(!file_exist(filename)){
       std::cout<<" File doesn't exist!";
    }
    else{
        std::ifstream f(filename);
        adjacencyMatrix = makeAdjacencyMatrix(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                f >> adjacencyMatrix[i][j];
            }
        }

        printAdjacencyMatrix(adjacencyMatrix, n);
        std::cout<<std::endl;
    }
    int rand;
    std::cout<<"Set random number"<<std::endl;
    std::cin>>rand;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0, n);
    for(int i = 0; i < rand; ++i){
        a = int(dist(mt));
        b = int(dist(mt));
        c = int(dist(mt));
        d = int(dist(mt));
        if(a!=b and a != c and a!=d and b!=c and b!=d and c!=d){
            if(adjacencyMatrix[a][b] and adjacencyMatrix[c][d]){
                // std::cout<<a<<" "<<b<<" "<<c<<" "<<d<<std::endl;
                if(adjacencyMatrix[a][d] == 0 and adjacencyMatrix[b][c] == 0){
                    adjacencyMatrix[a][d] = 1;
                    adjacencyMatrix[b][c] = 1;
                    adjacencyMatrix[a][b] = 0;
                    adjacencyMatrix[c][d] = 0;
                }
                else{
                    --i;
                }
            }
            else{
                --i;
            }
        }
        else{
            --i;
        }
    }

    printAdjacencyMatrix(adjacencyMatrix, n);
    matrix_to_file(adjacencyMatrix, n);
    std::cout<<std::endl;
}

void greatestComponent(std::vector<int> seq1)
{
    // int seq [] = {4,2,2,3,2,1,4,2,2,2,2};
    int size = seq1.size();
    int* seq = get_arr(seq1);

    std::vector<int> comp = components(seq,size);
    int max = *std::max_element(comp.begin(),comp.end());

    int greatest_count = 0;
    int greatest;
    int count;

    for(int n=1; n<=max; n++)
    {
        count = std::count(comp.begin(),comp.end(),n);
        if(greatest_count < count)
        {
            greatest_count = count;
            greatest = n;
        }

        std::cout<<n<<") ";

        for(int i=0; i<size;i++)
        {
            if(comp[i] == n)
            {
                std::cout<<i+1<<" ";
            }
        }
        std::cout<<std::endl;
    }

    std::cout<<"Greatest component: number "<<greatest<<std::endl;
    
    matrix_to_file(seq, size);

}

void eulersGraph()
{
    srand(time(NULL));
    int n;
    std::cout<<"Insert number of vertices: ";
    std::cin>>n;

    int max_edge_level = n - 1;

    // int seq[] = {4, 2, 6, 2, 6, 2, 4, 2};
    int seq[n];
    int step = 0;

    do{

        for(int i=0; i<n; i++)
        {
            seq[i] = 2*(rand()%(static_cast<int>(ceil(max_edge_level/2.))));
        }
            step++;

    }while(!GraphSeq_check(seq, n) && step != STOP);

    if(step == STOP)
    {
        std::cout<<"Too many attempts for a random sequence. Try again\n";
        exit(EXIT_FAILURE);
    }

    std::cout<<"Your sequence:\n";
    for(int i=0; i<n;i++)
    {
        std::cout<<seq[i]<<" ";
    }
    std::cout<<std::endl;

    int** adjM = GraphSeq_to_AdjacencyMatrix(seq, n);
    printAdjacencyMatrix(adjM, n);
    matrix_to_file(adjM, n);

    std::vector<int> cykl;
    std::vector<bool> visited(n);
    std::fill(visited.begin(), visited.end(), false);

    int v = 0;
    cykl.push_back(v+1);

    int next;
    int nr;
    int check = 0;
    

    do
    {
        nr = 0;
        do{ 
            nr++;
            // std::cout<<"v = "<<v<<"\nnr before = "<<nr<<"\n";
            next = next_neighbour(adjM,n,v,nr);
            // std::cout<<"nr after = "<<nr<<"\n";
        }while(nr != -1 && is_bridge(adjM,n,v,next));

        //if there is no neighbour left, break the loop
        if(next == -1) break;

        //add neighbour to cycle (adding +1 only for difference in indexing in the end)
        cykl.push_back(next+1);

        //remove the edge we just crossed
        removeEdge(v,next,adjM);

        //go to the next neighbour and make it current vertex
        v = next;

        check++;

        if(check%20 == 0) std::cout<<check<<std::endl;

    }while(check != STOP);


    if(check == STOP)
    {
        std::cout<<"Time frame error\n";
        exit(EXIT_FAILURE);
    }

    std::cout<<"Euler's cycle:\n";
    for(unsigned int j=0; j<cykl.size(); j++)
    {
        std::cout<<cykl[j]<<" ";
    }
    std::cout<<std::endl;
}

void randomKGraph()
{
    int n,k;
    std::cout<<"insert number and level of vertices"<<std::endl;
    std::cout<<"Number: ";
    std::cin>>n;
    std::cout<<"\nLevel: ";
    std::cin>>k;
    if(isPossible(n, k)){
        int** graph;
        graph = GenerateRegularGraph(n, k);
        for(int i = 0; i < n; i++){
            std::cout<<i<<": ";
            for(int j = 0; j < k; j++){
                std::cout<<graph[i][j]<<", ";
            }
            std::cout<<std::endl;
        }
        
        matrix_to_file(graph, n);

        for(int i = 0; i < n; i++){
            delete[] graph[i];
        }
        delete[] graph;
    }
    else{
       std::cout<<"zle dane wejsciowe"<<std::endl;
    }
}

void hamiltonGraphCheck(char* filename)
{
    int** graph;

    std::ifstream inFile(filename);
    int n = std::count(std::istreambuf_iterator<char>(inFile),std::istreambuf_iterator<char>(), '\n');
    n++;
    std::cout<<n;

    // randomize
    if(!file_exist(filename)){
       std::cout<<" File doesn't exist!";
    }
    else{
        std::ifstream f(filename);
        graph = makeAdjacencyMatrix(n);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                f >> graph[i][j];
            }
        }

        printAdjacencyMatrix(graph, n);
        std::cout<<std::endl;
    }

    int* cycle = new int[n];
    cycle = Hamilton(n, graph);
    if(cycle != nullptr){
        for(int i = 0; i < n; i++){
            std::cout<<cycle[i]<<", ";
    }
    std::cout<<cycle[0]<<std::endl;
    }
    else
    std::cout<<"cykl nie istnieje"<<std::endl;
    delete[] cycle;
    for(int i = 0; i < n; i++)
        delete[] graph[i];
    delete[] graph;
}