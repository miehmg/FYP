#include "Solution.h"
// class StaticGraph;

// Solution::Solution(const Solution &s) : static_graph(s.static_graph){
    
//     vehicle_graphs  = s.vehicle_graphs;
      

// }

void print(Solution solution)
{
    StaticGraph &static_graph = solution.static_graph;

    for (int i = 0; i < solution.vehicle_graphs.size(); ++i)
    {
        vector<int> vehicle = solution.vehicle_graphs[i];
        std::cout << std::right << std::setw(4) << i;
        int k = vehicle.size();
        for (int j = 0; j < vehicle.size() / 2; ++j)
        {
            std::cout << std::right << std::setw(4) << vehicle[2 * j];
        }
        std::cout << std::endl
                  << std::right << std::setw(4) << i;
        for (int j = 0; j < vehicle.size() / 2; ++j)
        {
            std::cout << std::right << std::setw(4) << vehicle[2 * j + 1];
        }
        std::cout << std::endl;
        for (int k = 0; k < 20; ++k)
        {
            std::cout << '-';
        }
        std::cout << std::endl;
    }
}





//insert request into nearest people not enroute
Solution EarliestInsertionSolve(StaticGraph &static_graph)
{

    vector<vector<int>> VerticesSubGraphs;
    

    // vector<int> vehicle_state;

    int t = static_graph.vertices[0].distance(static_graph.vertices[1]) / static_graph.speed;
    static_graph.vertices[0].complete_time = t + static_graph.vertices[0].strt_time;
    vector<int> v1{0, static_graph.vertices[0].complete_time};
    VerticesSubGraphs.push_back(v1);
    std::cout << std::setw(4) << 0 << " vno " << std::setw(4) << "0" << ' ' << static_graph.vertices[0].strt_time << static_graph.vertices[0].complete_time << std::endl;

    for (int i = 1; i != static_graph.order_size; ++i)
    {
        Vertice &di = static_graph.vertices[i * 2];
        Vertice &oi = static_graph.vertices[i * 2 + 1];

        //check for available vehicle, pick earlierst
        int tmp = INT32_MAX;
        // int tmp = INT32_MIN;
        int vno;
        for (int j = 0; j < VerticesSubGraphs.size(); ++j)
        {
            int index = VerticesSubGraphs[j][(VerticesSubGraphs[j].size() - 2)];
            int told = VerticesSubGraphs[j].back();
            if (told < di.strt_time)
            {
                told = di.strt_time;
            }
            int dist1 = oi.distance(static_graph.vertices[index * 2]);
            int tph1 = told + dist1 / static_graph.speed;
            if (tph1 < oi.strt_time)
            {
                tph1 = oi.strt_time;
            }
            int tnew = tph1 + oi.distance(di) / static_graph.speed;
            // if (tnew < (di.strt_time + static_graph.tolerate_time) && tmp < tnew)
            if (tnew <= (di.strt_time + static_graph.tolerate_time) && tmp > tnew)
            {
                tmp = tnew;
                vno = j;
            }
        }

        //the fastest cannot satisfy
        // if (tmp > (di.strt_time + static_graph.tolerate_time))
        if (tmp == INT32_MIN || tmp == INT32_MAX) 
        {
            int t = di.distance(oi) / static_graph.speed;
            tmp = t + di.strt_time;
            vector<int> vnew{i, tmp};
            VerticesSubGraphs.push_back(vnew);
            di.complete_time = tmp;
            vno = VerticesSubGraphs.size() - 1;
        }
        else
        {
            VerticesSubGraphs[vno].push_back(i);
            VerticesSubGraphs[vno].push_back(tmp);
            di.complete_time = tmp;
        }

        std::cout << std::right << std::setw(4) << i << " vno " << std::setw(4)
                  << vno << std::setw(4) << di.strt_time << std::setw(4) << di.complete_time
                  << std::setw(8) << di.coor.xcoor << std::setw(8) << di.coor.ycoor << std::endl;
    }
    // print(solution);
    // return std::move(solution);
    Solution solution(static_graph, VerticesSubGraphs);
    return solution;
}

//static ant solve

Solution LatestInsertionSolve(StaticGraph &static_graph)
{

    vector<vector<int>> VerticesSubGraphs;

    // vector<int> vehicle_state;

    int t = static_graph.vertices[0].distance(static_graph.vertices[1]) / static_graph.speed;
    static_graph.vertices[0].complete_time = t + static_graph.vertices[0].strt_time;
    vector<int> v1{0, static_graph.vertices[0].complete_time};
    VerticesSubGraphs.push_back(v1);
    std::cout << std::setw(4) << 0 << " vno " << std::setw(4) << "0" << ' ' << static_graph.vertices[0].strt_time << static_graph.vertices[0].complete_time << std::endl;

    for (int i = 1; i != static_graph.order_size; ++i)
    {
        Vertice &di = static_graph.vertices[i * 2];
        Vertice &oi = static_graph.vertices[i * 2 + 1];

        //check for available vehicle, pick earlierst
        // int tmp = INT32_MAX;
        int tmp = INT32_MIN;
        int vno;
        for (int j = 0; j < VerticesSubGraphs.size(); ++j)
        {
            int index = VerticesSubGraphs[j][(VerticesSubGraphs[j].size() - 2)];
            int told = VerticesSubGraphs[j].back();
            if (told < di.strt_time)
            {
                told = di.strt_time;
            }
            int dist1 = oi.distance(static_graph.vertices[index * 2]);
            int tph1 = told + dist1 / static_graph.speed;
            if (tph1 < oi.strt_time)
            {
                tph1 = oi.strt_time;
            }
            int tnew = tph1 + oi.distance(di) / static_graph.speed;
            if (tnew < (di.strt_time + static_graph.tolerate_time) && tmp < tnew)
            // if (tnew <= (di.strt_time + static_graph.tolerate_time) && tmp > tnew)
            {
                tmp = tnew;
                vno = j;
            }
        }

        //the fastest cannot satisfy
        // if (tmp > (di.strt_time + static_graph.tolerate_time))
        if (tmp == INT32_MIN || tmp == INT32_MAX) 
        {
            int t = di.distance(oi) / static_graph.speed;
            tmp = t + di.strt_time;
            vector<int> vnew{i, tmp};
            VerticesSubGraphs.push_back(vnew);
            di.complete_time = tmp;
            vno = VerticesSubGraphs.size() - 1;
        }
        else
        {
            VerticesSubGraphs[vno].push_back(i);
            VerticesSubGraphs[vno].push_back(tmp);
            di.complete_time = tmp;
        }

        std::cout << std::right << std::setw(4) << i << " vno " << std::setw(4)
                  << vno << std::setw(4) << di.strt_time << std::setw(4) << di.complete_time
                  << std::setw(8) << di.coor.xcoor << std::setw(8) << di.coor.ycoor << std::endl;
    }
    // print(solution);
    // return std::move(solution);
    Solution solution(static_graph, VerticesSubGraphs);
    return solution;
}


Solution NearestInsertionSolve(StaticGraph &static_graph){

    vector<vector<int>> VerticesSubGraphs;

    // vector<int> vehicle_state;

    int t = static_graph.vertices[0].distance(static_graph.vertices[1]) / static_graph.speed;
    static_graph.vertices[0].complete_time = t + static_graph.vertices[0].strt_time;
    vector<int> v1{0, static_graph.vertices[0].complete_time};
    VerticesSubGraphs.push_back(v1);
    std::cout << std::setw(3) << 0 << " vno " << std::setw(2) << "0" << ' ' << static_graph.vertices[0].strt_time << static_graph.vertices[0].complete_time << std::endl;

    for (int i = 1; i != static_graph.order_size; ++i)
    {
        Vertice &di = static_graph.vertices[i * 2];
        Vertice &oi = static_graph.vertices[i * 2 + 1];

        //check for available vehicle, pick earlierst
        int tmp = INT32_MAX;
        // int tmp = INT32_MIN;
        int tmpdist = INT32_MAX;
        // int tmp = INT32_MIN;
        int vno;
        for (int j = 0; j < VerticesSubGraphs.size(); ++j)
        {
            int index = VerticesSubGraphs[j][(VerticesSubGraphs[j].size() - 2)];
            int told = VerticesSubGraphs[j].back();
            if (told < di.strt_time)
            {
                told = di.strt_time;
            }
            int dist1 = oi.distance(static_graph.vertices[index * 2]);
            int tph1 = told + dist1 / static_graph.speed;
            if (tph1 < oi.strt_time)
            {
                tph1 = oi.strt_time;
            }
            int tnew = tph1 + oi.distance(di) / static_graph.speed;
            // if (tnew < (di.strt_time + static_graph.tolerate_time) && tmp < tnew)
            if (tnew <= (di.strt_time + static_graph.tolerate_time) && tmpdist > (dist1 + di.distance(static_graph.vertices[index * 2])))
            {
                tmpdist = dist1 + oi.distance(di);
                tmp = tnew;
                vno = j;
            }
        }

        //the fastest cannot satisfy
        // if (tmp > (di.strt_time + static_graph.tolerate_time))
        if (tmp == INT32_MIN || tmp == INT32_MAX) 
        {
            int t = di.distance(oi) / static_graph.speed;
            tmp = t + di.strt_time;
            vector<int> vnew{i, tmp};
            VerticesSubGraphs.push_back(vnew);
            di.complete_time = tmp;
            vno = VerticesSubGraphs.size() - 1;
        }
        else
        {
            VerticesSubGraphs[vno].push_back(i);
            VerticesSubGraphs[vno].push_back(tmp);
            di.complete_time = tmp;
        }

        std::cout << std::right << std::setw(4) << i << " vno " << std::setw(4)
                  << vno << std::setw(4) << di.strt_time << std::setw(4) << di.complete_time
                  << std::setw(8) << di.coor.xcoor << std::setw(8) << di.coor.ycoor << std::endl;
    }
    // print(solution);
    Solution solution(static_graph, VerticesSubGraphs);
    return solution;
}