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

//typedef property < vertex_centrality_t, double > CentralityMap;
//typedef property <edge_centrality_t, double > EdgeCentralityMap;
typedef adjacency_list <vecS, vecS, undirectedS> Graph;

Graph CreateGraph(string inputFile);
void FindCommunities(Graph& adjGraph);
int FindGreatest(vector<double> betwList);
void RemoveEdge(int greatestEdge, Graph& adjGraph);
void PrintCommunities(Graph& outGraph, string outputFile);


#endif //INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H
