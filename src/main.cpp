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


int main(int argc, char* const argv[]){
    Graph myGraph = CreateGraph(argv[1]);
    FindCommunities(myGraph);
    return 0;
}