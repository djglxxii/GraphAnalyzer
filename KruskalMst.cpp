#include "GraphData.h"
#include "KruskalMst.h"

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iostream>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
        boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef std::pair<char, char> E;

// method code modified for use from https://www.boost.org/doc/libs/1_53_0/libs/graph/example/kruskal-example.cpp
void KruskalMst::showMinimumSpanningTree() {
    std::vector<std::pair<char, char>> edgeVector;
    std::vector<int> weightVector;

    // convert graphData into a structure this method can use.
    for (auto e:graphData.getEdges()) {
        auto edge = std::make_pair(e.u, e.v);
        edgeVector.push_back(edge);
        weightVector.push_back(e.w);
    }

    auto edge_array = &edgeVector[0];
    auto weights = &weightVector[0];

    std::size_t const num_nodes = graphData.getVertexCount();
    std::size_t const num_edges = edgeVector.size();

    Graph g(edge_array, edge_array + num_edges, weights, num_nodes);

    boost::property_map<Graph, boost::edge_weight_t>::type weight = get(boost::edge_weight, g);
    std::vector<Edge> spanning_tree;

    kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

    int totalWeight = 0;

    std::cout << "Print the edges in the MST:" << std::endl;
    for (auto &ei : spanning_tree) {
        auto const src = source(ei, g);
        auto const tgt = target(ei, g);

        std::cout << static_cast<char>(src) << " <--> " << static_cast<char>(tgt)
                  << " with weight of " << weight[ei]
                  << std::endl;

        totalWeight += weight[ei];
    }

    std::cout << "Total weight: " << totalWeight << std::endl;
}
