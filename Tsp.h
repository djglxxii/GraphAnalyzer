#pragma once

#include "GraphData.h"

class Tsp {
public:
    Tsp(GraphData const &gd) : graphData(gd) {}

    ~Tsp() = default;

    void execute();
private:
    GraphData graphData;
};