#include "bellmanford.h"
#include "fibonacciheap.h"

#define INFINITY (unsigned int )(-1)

void initialize(dgraph *g, vertex *s)
{
     assert(g);
     assert(s);

     unsigned int it = 0;
     for (it = 0; it < g->vertices.size(); it++)
     {
	  g->vertices[it]->d = INFINITY;
	  g->vertices[it]->p = NULL;
     }

     s->p = NULL;
     s->d = 0;
     return;
}

bool relax(vertex *u, vertex *v, int edge_cost)
{
     assert(u);
     assert(v);
     assert(edge_cost >= 0);

     if (v->d > (u->d + edge_cost))
     {
	  v->d = u->d + edge_cost;
	  v->p = u;
	  return true;
     }
     return false;
}

//Standard BellmanFord implementation which is of O(VE) complexity.
bool BellmanFord(graph *g, vertex *s)
{
     initialize(g, s);
     
     unsigned int it = 0;
     for (it = 0; it < vsize() - 1; it++)
     {
	  unsigned int is = 0;
	  for (is = 0; is < vsize(); is++)
	  {
	       vertex *u = g->get_vertex(is);
	       assert(u);
	       
	       unsigned int iu = 0;
	       for (iu = 0; iu < u->edges.size(); iu++);
	       {
		    assert(u->edges[iu]);
		    vertex *v = vertices[u->edges[iu]->ends[1]];
		    relax(u, v, u->edges[iu]->cost);
	       }
	  }
     }

     for (it = 0; it < vsize(); it++)
     {
	  vertex *u = g->get_vertex(it);
	  
	  unsigned int is = 0;
	  for (is = 0; is < u->edges.size(); is++)
	  {
	       assert(u->edges[iu]);
	       vertex *v = vertices[u->edges[iu]->ends[1]];
	       if (relax(u, v, u->edges[iu]->cost))
		   return false;
	       
	  }

     }	  
     return true;

     
}

//Implement for multiple sources
bool BellmanFord(graph *g, std::vector<vertex*> s)
{
     return true;
}


//BellmanFord Algorithm Yen's Modification.
bool BellmanFord_Yen(graph *g, vertex *s)
{
     
}
