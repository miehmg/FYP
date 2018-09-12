#ifndef TABUSOLVE_H
#define TABUSOLVE_H

#include "../common.h"
#include "Solution.h"

Solution StaticTabuSolve(StaticGraph static_graph, int wait_time);

Solution DynamicTabuSolve(StaticGraph static_graph, int wait_time);

































#endif