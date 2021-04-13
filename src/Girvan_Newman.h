//
// Created by Elias Mann on 4/9/21.
//


#ifndef INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H
#define INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H

#include <boost/graph/adjacency_list.hpp>
#include <string>

using namespace boost;

typedef property < vertex_centrality_t, double > CentralityMap;
typedef property <edge_centrality_t, double > EdgeCentralityMap;
typedef adjacency_list <vecS, vecS, undirectedS, CentralityMap ,EdgeCentralityMap> Graph;

Graph CreateGraph(std::string inputFile);
void FindCommunities(Graph& adjGraph);


#endif //INC_21_S_PA03_ELIASMANN_GIRVAN_NEWMAN_H
