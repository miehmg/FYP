#ifndef STATICGRAPH_H
#define STATICGRAPH_H

#include "../common.h"



struct GraphCoor
{
    int xcoor;
    int ycoor;

    GraphCoor() {}
    GraphCoor(int x, int y) : xcoor(x), ycoor(y) {}
    int distance(GraphCoor d)
    {
        int hd = abs(d.xcoor - xcoor) + abs(d.ycoor - ycoor);
        return abs(hd);
    }
};

struct Vertice
{
    GraphCoor coor;
    GraphCoor pairver;
    enum vertype
    {
        isorigin,
        isdest
    };
    vertype type;
    int strt_time;
    int end_time;
    int complete_time;
    int seri_no;
    const int ifntuppertime = __INT_MAX__;

    Vertice() {}
    Vertice(GraphCoor gr, int stm, vertype tp) : coor(gr), type(tp)
    {
        strt_time = stm;
        end_time = isOrigin() ? (strt_time+30) : ifntuppertime;
        complete_time = INT32_MIN;
    }

    

    int distance(Vertice &v){
        return this->coor.distance(v.coor);
    }
    bool isOrigin() { return type == isorigin ? true : false; }
    bool isDest() { return type == isdest ? true : false; }
};

struct StaticGraph
{
    vector<Vertice> vertices;
    int geo_size;
    int order_size;
    int time_span;
    int tolerate_time;
    int speed = 1;
    int vehicle_size;

    

    StaticGraph(int gs, int os, int ts, int tt, int spd, int vs = 0)
        : geo_size(gs), order_size(os), time_span(ts), tolerate_time(tt), speed(spd) {}

    friend StaticGraph &InitializeVertices(StaticGraph &, int, vector<int> &);


};

std::ostream &operator<<(std::ostream &, const Vertice &);

std::ostream &operator<<(std::ostream &, const StaticGraph &);

StaticGraph &InitializeVertices(StaticGraph &, int, vector<int> &);


#endif