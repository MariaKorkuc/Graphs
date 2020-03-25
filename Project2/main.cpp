#include <iostream>
#include "project2.h"
#include <conio.h>

std::vector<int> get_sequence(int n1, char* argv[]);
char* get_filename(int n, char* argv[]);

int main(int argc, char* argv[])
{
    std::cout<<"************Projekt 2************\n";
    int choice;
    char c;

    do{
        std::cout<<"Choose the task:\n(ESC terminates program)\n";
        std::cout<<"1 - check if sequence is a graph sequence\n";
        std::cout<<"2 - randomize matrix (needed file with adjacency matrix)\n";
        std::cout<<"3 - get the greatest component of graph\n";
        std::cout<<"4 - get random euler's graph and check the euler's cycle\n";
        std::cout<<"5 - get random k-regular graph\n";
        std::cout<<"6 - check if graph is a hamilton graph\n";

        c = getch();
        if(c == 27) break;

        choice = int(c) - int('0');
        std::cout<<choice<<std::endl;
        std::vector<int> seq;
        char* filename;

        switch(choice)
        {
            case 1:
                seq = get_sequence(argc,argv);
                checkSequence(seq);
                break;
            case 2:
                filename = get_filename(argc,argv);
                randomizeMatrix(filename);
                break;
            case 3:
                seq = get_sequence(argc,argv);
                greatestComponent(seq);
                break;
            case 4:
                eulersGraph();
                break;
            case 5:
                randomKGraph();
                break;
            case 6:
                filename = get_filename(argc,argv);
                hamiltonGraphCheck(filename);
                break;
            default:
                std::cout<<"Not an option, try again\n";
                break;
        }


    }while(c != 27);

    return 0;
}

std::vector<int> get_sequence(int n1, char* argv[])
{
    int size = n1;
    char* filename;
    int n = 0;
    int temp;
    std::vector<int> seq;

    if(size < 2)
    {
        std::cout<<"Insert sequence's length: ";
        std::cin>>n;
        std::cout<<"\nInsert sequence:\n";
        for(int i=0; i<n; i++)
        {
            std::cin>>temp;
            seq.push_back(temp);
        }
    }
    else
    {
        filename = argv[1];

        if(!file_exist(filename)){
        std::cout<<" File doesn't exist!";
        }
        else{
            std::ifstream f(filename);

            while(f >> temp)
            {
                n++;
                seq.push_back(temp);
            }
        }
    }


    for(int i=0; i<n; i++)
    {
        std::cout<<seq[i]<<" ";
    }
    std::cout<<std::endl;

    return seq;
}

char* get_filename(int n, char* argv[])
{
    int size = n;
    char* filename;

    if(size<2)
    {
        std::string f;
        std::cout<<"Insert path to file:\n";
        getline(std::cin, f);
        std::strcpy(filename, f.c_str());
        std::cout<<std::endl;
    }
    else
    {
        filename = argv[1];
    }

    return filename;
}
