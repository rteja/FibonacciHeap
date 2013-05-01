#ifndef _BELLMANFORD_H_
#define _BELLMANFORD_H_

#include "dgraph.h"

#define INFINITY (unsigned int )(100000)


// Bellman Ford Algorithm for computing single source shortest path.
// Algorithm returns true of shortest path can be computed, returns false if there is a negetive weight cycle.

bool BellmanFord(dgraph *g, vertex *s);
bool BellmanFord(dgraph *g, std::vector<vertex*> s);

// Yen's modification of Bellman Ford Algorithm which will reduce the time complexity to half that comes by
// standard implementation above.
bool BellmanFord_Yen(dgraph *g, vertex *s);
bool BellmanFord_Yen(dgraph *g, std::vector<vertex*> s);


#endif
