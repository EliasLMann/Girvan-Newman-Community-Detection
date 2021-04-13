#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/config.hpp>
#include <boost/utility.hpp> // for boost::tie
#include <boost/graph/graphviz.hpp>

#include "Girvan_Newman.h"

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS> Graph;

int main(int argc, char* const argv[]){
    CreateGraph(argv[1]);
    return 0;
}