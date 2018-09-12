// #ifdef __cplusplus__
// #include <cstdlib>
// #else
// #include <stdlib.h>
// #endif

#include "common.h"
#include "Solution/Solution.h"
#include "Generator/StaticGraph.h"



int main(int argc, char const *argv[])
{
    int geo_size = 10000, order_size = 50,
    // int geo_size = 7000, order_size = 50,
        time_span = 60, tolerate_time = 30, speed = 300;
    int time_seed = 100, vrtc_seed = 0, vhcl_seed = 5;
    int wait_time = 0;
    // wait_time = 5;

    // StaticGraph(int gs, int os, int ts, int tt, int vs = 0)
    StaticGraph static_graph{geo_size, order_size, time_span, tolerate_time, speed};


    // generate time sequence
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
    
    // generate vehicle start position sequence
    vector<GraphCoor> strt_pos_seq;
    for(int i = 0; i < static_graph.vehicle_size; ++i){
        static std::default_random_engine e(vhcl_seed);
        static std::normal_distribution<> u(0, geo_size / 6);
        int x = u(e);
        int y = u(e);
        strt_pos_seq.emplace_back(x, y);
    }

    InitializePDVertices(static_graph, time_seq, strt_pos_seq, vrtc_seed);
    // std::cout << static_graph;

    // Solution sta_clu_sol = StaticClusterSolve(static_graph);
    // Solution earliest_ins_sol = EarliestInsertionSolve(static_graph);
    // print(earliest_ins_sol);
    // Solution latest_ins_sol = LatestInsertionSolve(static_graph);
    // Solution nearest_ins_sol = NearestInsertionSolve(static_graph);
    // Solution static_cluster_sol = StaticClusterSolve(static_graph);
    // Solution static_tabu_sol = StaticTabuSolve();
    Solution dynamic_tabu_sol = DynamicTabuSolve(static_graph, wait_time);
    print(dynamic_tabu_sol);


    
    // system("PAUSE");
    int i;
    std::cin >> i;
}


// Solution& StaticClusterSolve(StaticGraph &sg){}
