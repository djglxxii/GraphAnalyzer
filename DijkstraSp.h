#pragma once

#include "GraphData.h"

/**
 * Dijkstra Shortest Path
 */
class DijkstraSp {
public:
    DijkstraSp(GraphData const &gd) : graphData(gd) {}

    ~DijkstraSp() = default;

    /**
     * Show the shortest path from source vertex to destination vertex.
     * @param src The source vertex.
     * @param dst The destination vertex.
     */
    void showShortest(char const src, char const dst);

private:
    GraphData graphData;
};
