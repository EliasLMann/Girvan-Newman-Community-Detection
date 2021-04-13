//
// Created by Elias Mann on 4/9/21.
//


#ifndef INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H
#define INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H

#include <boost/graph/adjacency_list.hpp>
#include <string>
#include <vector>

using namespace boost;
using namespace std;

typedef adjacency_list <vecS, vecS, undirectedS> Graph;

//function that creates a graph from the input file
Graph CreateGraph(string inputFile);
//function that removes edges until the number of communities changes
void FindCommunities(Graph& adjGraph);
//function prints the communities to output file
void PrintCommunities(Graph& outGraph, string outputFile);

//finding the index of the edge with the greatest betweeness
int FindGreatest(vector<double> betwList);

//function that removes the edge of a given graph
void RemoveEdge(int greatestEdge, Graph& adjGraph);



#endif //INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H
