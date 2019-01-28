# GraphAnalyzer

## Overview
The GraphAnalyzer accepts an input file to build the graph. See "SampleInput.txt" for an example format. Additionally,
vertices should be limited to single characters -- strings are not supported.  Once the graph file is read, the program
will build an undirected, weighted graph as described by the file. The data structure for the graph is an
adjacency list.  Various options are provided to analyze the graph.  Output is to the console.

## Usage
GraphAnalyzer uses the C++ Boost library (https://www.boost.org) for most of it's graphing functions.  In order 
to compile this program you must have the Boost library installed.

Once compiled, at the common prompt type:

"GraphAnalyzer.exe inputfilename"

For example, if your input file is named "mygraph.txt" you should enter

GraphAnalyzer.exe mygraph.txt

Once run the program will output the details of the parsed input file and then provide the options:

(1) Dijkstra's Shortest Path
(2) Kruskal's Minimum Spanning Tree
(Q) Quit

If "(1) Dijkstra's Shortest Path" is selected then the user must also enter a start and end vertex.  For
accurate results make sure the vertices entered matches *exactly* what is described within the input file.

If "(2) Kruskal's Minimum Spanning Tree" is selected, the program will output the minimum spanning tree of
the described graph.

if "(Q) Quit" is selected then the program exits.

## Technical Details
The Dijkstra's Shortest Path uses the Boost library's "dijkstra_shortest_paths" algorithm.  As per the
documentation, "this algorithm solves the single-source shortest-paths problem on a weighted, directed 
or undirected graph for the case where all edge weights are nonnegative."

Code used within GraphAnalyzer for Dijkstra's shortest path was modified from the example provided
at http://programmingexamples.net/wiki/Boost/BGL/DijkstraComputePath

Big O complexity for Dijkstra is O(nlogn).

-----
The Kruskal's Minimum Spanning Tree uses the Boost library's "kruskal_minimum_spanning_tree: algorithm.
Kruskal's MST will the minimum spanning tree in an undirected graph with weighted edges as described by
the input file.

Code used within GraphAnalyzer for Kruskal's Minimum Spanning Tree was modified fromm the example provided
by Boost's example at https://www.boost.org/doc/libs/1_53_0/libs/graph/example/kruskal-example.cpp

Big O complexity for Kruskal's MST is O(nlogn)

