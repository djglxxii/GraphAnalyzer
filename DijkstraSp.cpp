#include <boost/config.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/properties.hpp>

#include <boost/property_map/property_map.hpp>

#include <iostream>
#include <utility>
#include <vector>
#include <map>

#include "DijkstraSp.h"

typedef int Weight;
typedef boost::property<boost::edge_weight_t, Weight> WeightProperty;
typedef boost::property<boost::vertex_name_t, char> NameProperty;

typedef boost::adjacency_list < boost::listS, boost::vecS, boost::undirectedS,
        NameProperty, WeightProperty > Graph;

typedef boost::graph_traits < Graph >::vertex_descriptor Vertex;

typedef boost::property_map < Graph, boost::vertex_index_t >::type IndexMap;
typedef boost::property_map < Graph, boost::vertex_name_t >::type NameMap;

typedef boost::iterator_property_map < Vertex*, IndexMap, Vertex, Vertex& > PredecessorMap;
typedef boost::iterator_property_map < Weight*, IndexMap, Weight, Weight& > DistanceMap;

// method code modified for use from http://programmingexamples.net/wiki/Boost/BGL/DijkstraComputePath
void DijkstraSp::showShortest(char const src, char const dst) {
    std::map<char, Vertex> vertexMap;

    Graph g;

    for (auto v : graphData.getVertices())
    {
        vertexMap[v] = boost::add_vertex(v, g);
    }

    for (auto e : graphData.getEdges())
    {
        Vertex v1 = vertexMap[e.u];
        Vertex v2 = vertexMap[e.v];
        Weight w = e.w;

        boost::add_edge(v1, v2, w, g);
    }

    Vertex v0 = vertexMap[src];
    Vertex v3 = vertexMap[dst];

    // Create things for Dijkstra
    std::vector<Vertex> predecessors(boost::num_vertices(g)); // To store parents
    std::vector<Weight> distances(boost::num_vertices(g)); // To store distances

    IndexMap indexMap = boost::get(boost::vertex_index, g);
    PredecessorMap predecessorMap(&predecessors[0], indexMap);
    DistanceMap distanceMap(&distances[0], indexMap);

    // Compute shortest paths from v0 to all vertices, and store the output in predecessors and distances
    // boost::dijkstra_shortest_paths(g, v0, boost::predecessor_map(predecessorMap).distance_map(distanceMap));
    // This is exactly the same as the above line - it is the idea of "named parameters" - you can pass the
    // prdecessor map and the distance map in any order.
    boost::dijkstra_shortest_paths(g, v0, boost::distance_map(distanceMap).predecessor_map(predecessorMap));

    // Output results
    NameMap nameMap = boost::get(boost::vertex_name, g);

    // Extract a shortest path
    std::cout << std::endl;

    typedef std::vector<Graph::edge_descriptor> PathType;

    PathType path;

    Vertex v = v3; // We want to start at the destination and work our way back to the source
    for (Vertex u = predecessorMap[v]; // Start by setting 'u' to the destintaion node's predecessor
         u != v; // Keep tracking the path until we get to the source
         v = u, u = predecessorMap[v]) // Set the current vertex to the current predecessor, and the predecessor to one level up
    {
        std::pair<Graph::edge_descriptor, bool> edgePair = boost::edge(u, v, g);
        Graph::edge_descriptor edge = edgePair.first;

        path.push_back(edge);
    }

    // Write shortest path
    std::cout << "Shortest path from " << src << " to " << dst << ":" << std::endl;
    float totalDistance = 0;
    for (PathType::reverse_iterator pathIterator = path.rbegin(); pathIterator != path.rend(); ++pathIterator)
    {
        std::cout << nameMap[boost::source(*pathIterator, g)] << " -> " << nameMap[boost::target(*pathIterator, g)]
                  << " = " << boost::get(boost::edge_weight, g, *pathIterator) << std::endl;

    }

    std::cout << std::endl;

    std::cout << "Distance: " << distanceMap[v3] << std::endl;
}
