#include "StaticGraph.h"

// StaticGraph::StaticGraph(){}

std::ostream &operator<<(std::ostream &os, const Vertice &v)
{
    os << "x: " << v.coor.xcoor << ", y: " << v.coor.ycoor << ", tw:["
       << v.strt_time << ", " << v.end_time << "]";
}

std::ostream &operator<<(std::ostream &os, const StaticGraph &sg)
{

    for (Vertice v : sg.vertices)
        os << v << std::endl;
}

StaticGraph &InitializeVertices(StaticGraph &sg, int seed, vector<int> &time_vec)
{
    if (time_vec.size() < sg.order_size)
    {
        std::cout << "time vector not sufficient" << std::endl;
        return sg;
    }
    std::default_random_engine e(seed);
    std::normal_distribution<> n(0, sg.geo_size / 6);
    std::normal_distribution<> m(5, 1);
    for (int i = 0; i != sg.order_size; ++i)
    {
        int x1 = lround(n(e));
        int y1 = lround(n(e));
        int t1 = time_vec[i];
        int x2 = lround(n(e));
        int y2 = lround(n(e));
        int t2 = t1 + m(e);
        GraphCoor gracor1{x1, y1};
        GraphCoor gracor2{x2, y2};
        sg.vertices.emplace_back(gracor1, t1, Vertice::isorigin);
        sg.vertices.emplace_back(gracor2, t2, Vertice::isdest);
    }
}