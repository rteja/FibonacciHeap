e#include "dijkastra.h"
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

void relax(vertex *u, vertex *v, int edge_cost)
{
     assert(u);
     assert(v);
     assert(edge_cost >= 0);

     if (v->d > (u->d + edge_cost))
     {
	  v->d = u->d + edge_cost;
	  v->p = u;
     }
     return;
}

void Dijkastra(graph *g)
{
     assert(g);

     initialize(g, g->s[0]);
     FibonacciHeap v_heap;
     
     unsigned int it = 0;
     for (it = 0; it < g->vsize(); it++)
     {
	  v_heap.Insert(g->get_vertex(it)->d, (void*)g->get_vertex(it));
     }

     while (v_heap.Size())
     {
	  vertex *u = (vertex*) v_heap.ExtractMin();
	  for (it = 0; it < u->edges.size(); it++)
	       relax(u, u->edges[it], u->edges[it]->cost);
	  
     }

}
