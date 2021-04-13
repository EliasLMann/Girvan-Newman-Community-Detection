#include "Girvan_Newman.h"
#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/config.hpp>
#include <boost/utility.hpp> // for boost::tie
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/graphviz.hpp>
#include <vector>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>

using namespace std;
using namespace boost;

typedef property < vertex_centrality_t, double > CentralityMap;
typedef property <edge_centrality_t, double > EdgeCentralityMap;
typedef adjacency_list <vecS, vecS, undirectedS, CentralityMap ,EdgeCentralityMap> Graph;

typedef boost::concepts::EdgeListGraph<Graph> EdgeGraph;


void CreateGraph(string inputFile) {
    ifstream input;
    input.open(inputFile);
    string numEdgesStr;
    getline(input, numEdgesStr);
    int numEdges = stoi(numEdgesStr);
    vector<char> vertices;
    //edge vector
    pair<int,int> edgesArray[numEdges];
    int edgeIndex = 0;
    //maps to store character vertices and their respective integers
    map<char,int> charToInt;
    map<int,char> intToChar;

    while(!input.eof()){
        vector<char>::iterator searchIter;
        string currEdgeStr;
        getline(input, currEdgeStr);
        //add first vertex to array if it does not already exist
        searchIter = find (vertices.begin(), vertices.end(), currEdgeStr[0]);
        if(searchIter == vertices.end()){
            vertices.push_back(currEdgeStr[0]);
            //add new vertex to char to int maps
            charToInt.emplace(currEdgeStr[0], vertices.size()-1);
            intToChar.emplace(vertices.size()-1, currEdgeStr[0]);
        }
        //add second vertex to array if it does not already exist
        searchIter = find (vertices.begin(), vertices.end(), currEdgeStr[4]);
        if(searchIter == vertices.end()){
            vertices.push_back(currEdgeStr[4]);
            //add new vertex to char to int maps
            charToInt.emplace(currEdgeStr[4], vertices.size()-1);
            intToChar.emplace(vertices.size()-1, currEdgeStr[4]);
        }
        //getting the integer associated with each vertex in the current edge
        int vert1 = charToInt.find(currEdgeStr[0])->second;
        int vert2 = charToInt.find(currEdgeStr[4])->second;
        pair<int,int> currEdge = make_pair(vert1, vert2);
        edgesArray[edgeIndex] = currEdge;
        edgeIndex++;
    }

    std::vector<double> centrality(vertices.size());
    std::vector<double> edgeCentrality(numEdges);
    Graph adjGraph(edgesArray, edgesArray + numEdges, vertices.size());
    EdgeGraph eGraph;
//    for(int i = 0; i < numEdges; i++){
//        add_edge(edgesArray[i].first, edgesArray[i].second, eGraph.g);
//    }

    //typedef for edge descriptor for each edge
    typedef graph_traits< Graph >::edge_descriptor Edge_info;
    //create two iterators that will be the return value of edgesArray(g)
    graph_traits< Graph >::edge_iterator ei_start, ei_end;

    eGraph.g = adjGraph;
    eGraph.const_constraints(adjGraph);
    //centrality_map(make_iterator_property_map(centrality.begin(),get(vertex_index, eGraph.g),double())).vertex_index_map(get(vertex_index,eGraph.g));

    map<Edge_info, int> edgeMap;
    associative_property_map <map<Edge_info, int>> edgeIndexMap(edgeMap);
    int x = connected_components(adjGraph, edgeIndexMap);


    int index = 0;
    for(tie(ei_start, ei_end) = edges(adjGraph); ei_start != ei_end; ++ei_start){
        Edge_info e = *ei_start;
        edgeMap.emplace(make_pair(e,index));
        index++;
    }

    brandes_betweenness_centrality(adjGraph,centrality_map(make_iterator_property_map(centrality.begin(),get(vertex_index, adjGraph))).edge_centrality_map(make_iterator_property_map(edgeCentrality.begin(),edgeIndexMap)).vertex_index_map(get(vertex_index,adjGraph)));

}
