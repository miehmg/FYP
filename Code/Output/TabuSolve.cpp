#include "TabuSolve.h"
#include "Solution.h"

Solution StaticTabuSolve(StaticGraph static_graph, int wait_time)
{

    using std::pair;

    Solution prime_solut = NearestInsertionSolve(static_graph);

    vector<vector<int>> vehic_graphs = prime_solut.vehicle_graphs;
    int vehic_num = vehic_graphs.size;
    vector<pair<int, int>> tabu_list;

    Solution best = prime_solut;
    bool condition = true;
    while (condition)
    {
        for (int vehic = vehic_num - 1; vehic != -1; --vehic)
        {
            vector<int> subrout = vehic_graphs[vehic];
            for (int vrtc = subrout.size(); vrtc != -1; --vrtc)
            {
            }
        }
    }
}

Solution DynamicTabuSolve(StaticGraph static_graph, int wait_time)
{

    using std::queue;

    vector<Vertice> vertices = static_graph.vertices;
    vector<vector<int>> vehic_grphs; //verticeno, starttime, finishtime

    queue<int> order_in_wndw, vhcl_in_wndw;
    bool condition = true;
    int curr_order_no = 0, fin_order_no = 0;

    int time_hrz = wait_time;
    // int left_margin = vertices[0].strt_time, right_margin = left_margin + 5;
    // while(fin_order_no != static_graph.order_size){
    while (condition)
    {
        vector<int> vehic_strt_tm;
        vector<int> avlb_order;

        //about to go vehicle's order should not be forgot
        // for (vector<int> vehic : vehic_grphs)
        // {
        //     if (vehic[vehic.size() - 2] >= time_hrz)
        //     {
        //         int i = vehic[vehic.size() - 3];
        //         avlb_order.push_back(i);
        //     }
        // }

        for (int orno = 0; orno != static_graph.order_size; ++orno)
        {
            if (vertices[orno * 2].complete_time == INT32_MIN)
            {
                avlb_order.push_back(orno);
            }
        }

        //nearest solve first
        vector<vector<int>> temp_vhcl_graph;
        for (int i = 1; i != avlb_order.size(); ++i)
        {
            int order_index = avlb_order[i];
            Vertice &di = static_graph.vertices[order_index * 2];
            Vertice &oi = static_graph.vertices[order_index * 2 + 1];

            //check for available vehicle, pick earlierst
            int tmp = INT32_MAX;
            // int tmp = INT32_MIN;
            int tmpdist = INT32_MAX;
            // int tmp = INT32_MIN;
            int vno;
            for (int j = 0; j != vehic_grphs.size(); ++j)
            {
                int index;
                int told;
                if (vehic_grphs[j][vehic_grphs[j].size() - 2] < time_hrz)
                { //str before time horizon canbe enroute or wait
                    index = vehic_grphs[j][(vehic_grphs[j].size() - 3)];
                    told = vehic_grphs[j].back();
                }
                else if (vehic_grphs[j].size() >= 6)
                {
                    index = vehic_grphs[j][vehic_grphs[j].size() - 6];
                    told = vehic_grphs[j][vehic_grphs[j].size() - 4];
                }
                else
                {
                    index = -1;
                    told = INT32_MIN;
                }
                if (told < di.strt_time)
                {
                    told = di.strt_time;
                }
                int dist1;
                if (index == 1)
                {
                    dist1 = 0;
                }
                else
                {
                    dist1 = oi.distance(static_graph.vertices[index * 2]);
                } //last dest to this origin
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
                vector<int> vnew{i, di.strt_time+wait_time, tmp};
                vehic_grphs.push_back(vnew);
                di.complete_time = tmp;
                vno = vehic_grphs.size() - 1;
            }
            else
            {
                vehic_grphs[vno].push_back(i);
                vehic_grphs[vno].push_back(tmp);
                di.complete_time = tmp;
            }

            std::cout << std::right << std::setw(4) << i << " vno " << std::setw(4)
                      << vno << std::setw(4) << di.strt_time << std::setw(4) << di.complete_time
                      << std::setw(8) << di.coor.xcoor << std::setw(8) << di.coor.ycoor << std::endl;
        }
    }
}