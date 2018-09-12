#ifndef SOLUTION_H
#define SOLUTION_H

#include "../common.h"
#include "../Generator/StaticGraph.h"
// class StaticGraph;
// class Vertice;

struct SubRout{
    vector<int> subrout;
    
    SubRout(vector<int> sr);
};


struct Solution{
    StaticGraph &static_graph;
    int vehc_num;
    vector<vector<int>> vehicle_graphs;

    Solution(StaticGraph &sg, vector<vector<int>> &vsg) : static_graph(sg), vehicle_graphs(vsg){}

    // Solution(const Solution &);

};


Solution EarliestInsertionSolve(StaticGraph &);

Solution LatestInsertionSolve(StaticGraph &);

Solution NearestInsertionSolve(StaticGraph &static_graph);

Solution StaticAntSolve(StaticGraph &);

void print(Solution);





















#endif