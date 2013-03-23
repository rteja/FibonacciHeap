#ifndef _BELLMANFORD_H_
#define _BELLMANFORD_H_

#include "graph.h"

// Bellman Ford Algorithm for computing single source shortest path.
// Algorithm returns true of shortest path can be computed, returns false if there is a negetive weight cycle.

bool BellmanFord(graph *g, vertex *s);


#endif
