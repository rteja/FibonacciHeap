#include "bellmanford.h"
#include "fibonacciheap.h"

#include <assert.h>

#include <stdio.h>


void initialize_b(dgraph *g, vertex *s)
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

     if (v->d > (u->d + edge_cost))
     {
	  v->d = u->d + edge_cost;
	  v->p = u;
	  return true;
     }
     return false;
}

//Standard BellmanFord implementation which is of O(VE) complexity.
bool BellmanFord(dgraph *g, vertex *s)
{
     assert(g);
     assert(s);

     initialize_b(g, s);
     
     unsigned int it = 0;
     for (it = 0; it < g->vsize() - 1; it++)
     {
	  //Relax all edges of the graph
	  unsigned int is = 0;
	  for (is = 0; is < g->vsize(); is++)
	  {
	       vertex *u = g->get_vertex(is);
	       assert(u);
	       
	        int iu = 0;
		
		for (iu = 0; iu < u->edges.size(); iu++)
		{
		     assert(u->edges[iu]);
		     vertex *v = g->vertices[u->edges[iu]->ends[1]];
		     relax(u, v, u->edges[iu]->cost);
		}
	  }
     }

     // If there are edges that can be relaxed still 
     // there is a negative weight cycle.
     for (it = 0; it < g->vsize(); it++)
     {
	  vertex *u = g->get_vertex(it);
	  
	  unsigned int is = 0;
	  for (is = 0; is < u->edges.size(); is++)
	  {
	       assert(u->edges[is]);
	       vertex *v = g->vertices[u->edges[is]->ends[1]];
	       if (relax(u, v, u->edges[is]->cost))
		   return false;
	       
	  }

     }	  
     return true;
}

//Implement for multiple sources
bool BellmanFord(dgraph *g, std::vector<vertex*> s)
{
     return true;
}

//BellmanFord Algorithm Yen's Modification.
bool BellmanFord_Yen(dgraph *g, vertex *s)
{
     assert(g);
     assert(s);

     initialize_b(g, s);
     
     unsigned int it = 0;
     unsigned int max_it = (g->vsize() % 2) ? (g->vsize() / 2) : ((g->vsize() / 2) + 1);

     
     for (it = 0; it < max_it; it++)
     {
	  //Relaxation of edges i->j where i < j
	  unsigned int is = 0;
	  for (is = 0; is < g->vsize(); is++)
	  {
	       vertex *u = g->get_vertex(is);
	       assert(u);
	       
	       unsigned int iu = 0;
	       for (iu = 0; iu < u->edges.size(); iu++);
	       {
		    assert(u->edges[iu]);

		    if (u->edges[iu]->ends[1] <= is)
			 continue;

		    vertex *v = g->vertices[u->edges[iu]->ends[1]];
		    relax(u, v, u->edges[iu]->cost);
	       }
	  }
	  
	  //Relaxation of edges i->j where i > j
	  for (is = 0; is < g->vsize(); is++)
	  {
	       vertex *u = g->get_vertex(is);
	       assert(u);
	       
	       unsigned int iu = 0;
	       for (iu = 0; iu < u->edges.size(); iu++);
	       {
		    assert(u->edges[iu]);

		    if (u->edges[iu]->ends[1] >= is)
			 continue;

		    vertex *v = g->vertices[u->edges[iu]->ends[1]];
		    relax(u, v, u->edges[iu]->cost);
	       }
	  }
     }
  

     // If there are edges that can be relaxed still 
     // there is a negative weight cycle.
     for (it = 0; it < g->vsize(); it++)
     {
	  vertex *u = g->get_vertex(it);
	  
	  unsigned int is = 0;
	  for (is = 0; is < u->edges.size(); is++)
	  {
	       assert(u->edges[is]);
	       vertex *v = g->vertices[u->edges[is]->ends[1]];
	       if (relax(u, v, u->edges[is]->cost))
		   return false;
	       
	  }

     }	  
	  
     return true;
}

//Implement Bellman Ford Yen's modification for multiple sources.
bool BellmanFord_Yen(dgraph *g, std::vector<vertex*> s)
{
     return true;
}
