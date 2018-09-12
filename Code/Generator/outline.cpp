#ifdef __cplusplus__
#include <cstdlib>
#else
#include <stdlib.h>
#endif

#include "../common.h"
#include "../Output/Solution.h"
#include "../Output/ClusterSolve.h"
#include "../Output/TabuSolve.h"
#include "StaticGraph.h"



int main(int argc, char const *argv[])
{
    int geo_size = 10000, order_size = 50,
        time_span = 60, tolerate_time = 30, speed = 300;
    int time_seed = 100, coor_seed = 0;
    //StaticGraph(int gs, int os, int ts, int tt, int vs = 0)
    StaticGraph static_graph{geo_size, order_size, time_span, tolerate_time, speed};

    //generate time sequence
    vector<int> time_seq;
    time_seq.reserve(100);
    for (int i = 0; i < order_size; ++i)
    {
        static std::default_random_engine e(time_seed);
        static std::normal_distribution<> u(0, time_span / 6);
        int t = u(e);
        time_seq.emplace_back(t);
    }

    std::sort(time_seq.begin(), time_seq.end());

    InitializeVertices(static_graph, coor_seed, time_seq);
    std::cout << static_graph;

    // Solution sta_clu_sol = StaticClusterSolve(static_graph);
    Solution earliest_ins_sol = EarliestInsertionSolve(static_graph);
    print(earliest_ins_sol);
    // Solution latest_ins_sol = LatestInsertionSolve(static_graph);
    // Solution nearest_ins_sol = NearestInsertionSolve(static_graph);
    // Solution static_cluster_sol = StaticClusterSolve(static_graph);
    // Solution static_tabu_sol = StaticTabuSolve(static_graph);
    // print(static_tabu_sol);


    
    system("PAUSE");
}


// Solution& StaticClusterSolve(StaticGraph &sg){}
