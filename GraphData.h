#pragma once

#include <vector>

class GraphData {
public:
    struct Edge {
        Edge(char const u, char const v, int const w)
                : u(u), v(v), w(w) {}

        char u, v;
        int w;
    };

    GraphData() = default;

    ~GraphData() = default;

    void addVertex(char const vertex) {
        vertices.push_back(vertex);
    }

    std::vector<char> getVertices() const {
        return vertices;
    }

    int getVertexCount() const {
        return vertices.size();
    }

    void addEdge(char const u, char const v, int const w) {
        auto const edge = Edge(u, v, w);
        edges.push_back(edge);
    }

    std::vector<Edge> getEdges() const {
        return edges;
    }

    int getEdgeCount() const {
        return edges.size();
    }

private:
    std::vector<char> vertices;
    std::vector<Edge> edges;
};
