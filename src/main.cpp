//
// Created by Elias Mann
//

#include "Girvan_Newman.h"

using namespace std;
using namespace boost;

int main(int argc, char* const argv[]){
    //creating graph from input file
    Graph myGraph = CreateGraph(argv[1]);
    //removing edges from the graph until communities are created
    FindCommunities(myGraph);
    //outputting communities to output file
    PrintCommunities(myGraph, argv[2]);
    return 0;
}