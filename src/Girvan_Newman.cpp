#include "Girvan_Newman.h"
#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/edge_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graphviz.hpp>
#include <vector>
#include <map>

using namespace std;
using namespace boost;

//maps enumeration back to passed in character
map<int, char> intToChar;

//function that creates a graph from the input file
Graph CreateGraph(string inputFile) {
    //reading in the file
    ifstream input;
    input.open(inputFile);
    string numEdgesStr;
    //retrieving number of edges
    getline(input, numEdgesStr);
    int numEdges = stoi(numEdgesStr);
    //mapping passed in character to index enumeration
    map<char, int> charToInt;
    //vertex vector
    vector<char> vertices;
    //edge array
    pair<int, int> edgesArray[numEdges];
    int edgeIndex = 0;

    while (!input.eof()) {
        vector<char>::iterator searchIter;
        string currEdgeStr;
        getline(input, currEdgeStr);
        //add first vertex to array if it does not already exist
        searchIter = find(vertices.begin(), vertices.end(), currEdgeStr[0]);
        if (searchIter == vertices.end()) {
            vertices.push_back(currEdgeStr[0]);
            //add new vertex to char to int maps
            charToInt.emplace(currEdgeStr[0], vertices.size() - 1);
            intToChar.emplace(vertices.size() - 1, currEdgeStr[0]);
        }
        //add second vertex to array if it does not already exist
        searchIter = find(vertices.begin(), vertices.end(), currEdgeStr[4]);
        if (searchIter == vertices.end()) {
            vertices.push_back(currEdgeStr[4]);
            //add new vertex to char to int maps
            charToInt.emplace(currEdgeStr[4], vertices.size() - 1);
            intToChar.emplace(vertices.size() - 1, currEdgeStr[4]);
        }
        //getting the integer associated with each vertex in the current edge
        int vert1 = charToInt.find(currEdgeStr[0])->second;
        int vert2 = charToInt.find(currEdgeStr[4])->second;
        pair<int, int> currEdge = make_pair(vert1, vert2);
        edgesArray[edgeIndex] = currEdge;
        edgeIndex++;
    }
    input.close();

    //creating a graph out of the edges read on from input file
    Graph adjGraph(edgesArray, edgesArray + numEdges, vertices.size());
    return adjGraph;
}

//function that removes edges until community count changes
void FindCommunities(Graph& adjGraph){
    //creating vector needed to calculate connected components
    vector<int> component(num_vertices(adjGraph));

    //calculating initial components in graph
    int startComponents = connected_components(adjGraph, &component[0]);
    int currComponents = startComponents;

    //continues to remove the edge with the greatest betweeness centrality until the number of components changes
    while(currComponents == startComponents){
        //vectors storing the betweeness centralities for the vertices and edges
        std::vector<double> centrality(num_vertices(adjGraph));
        std::vector<double> edgeCentrality(num_edges(adjGraph));

        //typedef for edge descriptor for each edge
        typedef graph_traits< Graph >::edge_descriptor Edge_info;
        //creating edge two iterators
        graph_traits< Graph >::edge_iterator ei_start, ei_end;

        //creating and edge index map to create edge centrality map
        map<Edge_info, int> edgeMap;
        associative_property_map <map<Edge_info, int>> edgeIndexMap(edgeMap);

        //populating index map
        int index = 0;
        for(tie(ei_start, ei_end) = edges(adjGraph); ei_start != ei_end; ++ei_start){
            Edge_info e = *ei_start;
            edgeMap.emplace(make_pair(e,index));
            index++;
        }

        //call brandess betweeness function to find vertex and edge betweenesses
        brandes_betweenness_centrality(adjGraph,
            //creating a centrality map with an iterator property map
           centrality_map(make_iterator_property_map(
                   //creating iterator property map with a vertex index offset map and vertex centrality vector
                   centrality.begin(),get(vertex_index, adjGraph)))
                   //creating edge centrality map with an iterator property map create
                   .edge_centrality_map(make_iterator_property_map(
                           //creating iterator property map with a edge index offset map and edge centrality vector
                           edgeCentrality.begin(),edgeIndexMap))
                           //populating the edge and vertex betweeness vectors
                   .vertex_index_map(get(vertex_index,adjGraph)));

        //call function to find the index of the edge with the greatest betweeness
        int greatestEdge = FindGreatest(edgeCentrality);

        //function to remove the edge at the given index
        RemoveEdge(greatestEdge, adjGraph);

        //recalculating number for connected components in the graph
        vector<int> component(num_vertices(adjGraph));
        currComponents = connected_components(adjGraph, &component[0]);
    }
}

//function prints the communities to output file
void PrintCommunities(Graph& outGraph, string outputFile){
    //opening output file
    ofstream output;
    output.open(outputFile);
    //creating vector to find the communities in the graph
    std::vector<int> component(num_vertices(outGraph));
    int num = connected_components(outGraph, &component[0]);

    //looping through the total number of communities
    for (int components = 0; components < num; components++){
        output << "Community " << components + 1  << ":"<< endl;
        //looping though all vertices
        for (int vertex = 0; vertex < component.size(); vertex++) {
            //outputting the current vertex if it is part of the current community
            if(component[vertex] == components){
                output << intToChar.find(vertex)->second << endl;
            }
        }
        output << endl;
    }
    output.close();
}

//finding the index of the edge with the greatest betwweness
int FindGreatest(vector<double> betwList){
    int greatestEdge = 0;
    for(int i = 0; i< betwList.size()-1; i++){
        if(betwList.at(i) > betwList.at (i+1)){
            greatestEdge = i;
        }else{
            greatestEdge = i+1;
        }
    }
    return greatestEdge;
}

//function that removes the edge of a given graph
void RemoveEdge(int greatestEdge, Graph& adjGraph){
    //typedef for edge descriptor for each edge
    typedef graph_traits< Graph >::edge_descriptor Edge_info;
    //creating two edge iterators
    graph_traits< Graph >::edge_iterator ei_start, ei_end;

    //finding the edge at the given index
    Edge_info foundEdge;
    tie(ei_start, ei_end) = edges(adjGraph);
    for(int j = 0; j <= greatestEdge; ++ei_start, j++){
        foundEdge = *ei_start;
    }
    //removing found edge from graph
    adjGraph.remove_edge(foundEdge);
}


