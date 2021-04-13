//
// Created by Elias Mann
//

#include "Girvan_Newman.h"

using namespace std;
using namespace boost;

int main(int argc, char* const argv[]){
    Graph myGraph = CreateGraph(argv[1]);
    FindCommunities(myGraph);
    PrintCommunities(myGraph, argv[2]);
    return 0;
}