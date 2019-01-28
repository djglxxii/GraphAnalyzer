#pragma once

#include "GraphData.h"

class KruskalMst {
public:
    KruskalMst(GraphData const &gd) : graphData(gd) {}

    ~KruskalMst() = default;

    /**
     * Show the minimum spanning tree.
     */
    void showMinimumSpanningTree();
private:
    GraphData graphData;
};
