# Girvan-Newman Community Detection Algorithm

## By Elias Mann

This program uses the Boost Graph Library to implement the [Girvan Newman Community Detection Algorithm](https://www.pnas.org/content/99/12/7821).

The input file contains the edges that make up the graph written in the following format: 
```text
4
A - B
A - C
B - C
B - D
```

The first line is the number of edges.

The output of the program is in "output_communities.txt" located in the "data" directory. It contains the community number followed by a list of vertices in the given commmunity.

To edit the input graph, edit the file "input_edges.txt" located in the "data" directory.

For the program to properly run, command line arguments must be used after the executable for the input and output files as follows (if you are in the project directory):

../data/input_edges.txt ../data/output_communities.txt
