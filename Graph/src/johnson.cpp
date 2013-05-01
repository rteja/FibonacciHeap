#include "johnson.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

DistanceMatrix::DistanceMatrix(int size)
{
     assert( size >= 0);
     
     vertices = size;
     if (size == 0)
     {
	  D = NULL;
	  return;
     }

     vertices = size;
     D = (int*) calloc(size*size, sizeof(int));
     assert(D);

     return;
}


DistanceMatrix::~DistanceMatrix()
{
     if (D)   free(D);
     vertices = 0;

     return;
}

int DistanceMatrix::SetDistance(unsigned int i, unsigned int j, int distance)
{
     assert(i < vertices);
     assert(j < vertices);

     D[i * vertices + j] = distance;
     return distance;
}

int DistanceMatrix::GetDistance(unsigned int i, unsigned int j)
{
     return 0;
}

void DistanceMatrix::Print()
{
     int i = 0;
     printf("DistanceMatrix:\n");
     for (i = 0; i < vertices * vertices; i++)
     {
	  if (i % vertices == 0)
	       printf("\n");

	  
	  if ((int)D[i] < (int)INFINITY)
	       printf("%3d\t", D[i]);
	  else
	       printf("%s\t", "---");
	  

     }
     printf("\n");
     return;
}

DistanceMatrix *Johnson(dgraph *g)
{
     assert(g);

     unsigned int v_id = g->add_vertex();
     unsigned int it = 0;

     for (it = 0; it < g->vsize(); it++)
     {
	  if (it == v_id)
	       continue;

	  // Adding edge from newly created vertex to all 
	  // existing vertices with edge cost 0.
	  g->add_edge(v_id, it, 0);
     }

     if (!BellmanFord(g, g->get_vertex(v_id)))
     {
	  // Return an invalid matrix if Bellman Ford algorithm returns false.
	  // This means there exits a negetive weight cycle.
	  return (new DistanceMatrix(0));
     }

     // If Bellman Ford returns true then d-values of all the vertices contain
     // shortest distances to all vertices from newly created vertex (v_id).
     int *h = (int*) calloc(g->vsize(), sizeof(int));
     assert(h);

     for (it = 0; it < g->vsize(); it++)
     {
	  assert(g->get_vertex(it));
	  h[it] = g->get_vertex(it)->d;
     }


     // Reassign the weights of the edges so that they are non negetive.
     // w'(u,v) = w(u,v) + h(u) - h(v)
     for (it = 0; it < g->vsize(); it++)
     {
	  vertex *u = g->get_vertex(it);
	  assert(u);

	  unsigned int is = 0;
	  for (is = 0; is < u->edges.size(); is++)
	  {
	       assert(u->edges[is]);
	       unsigned int v_index = u->edges[is]->ends[DESTINATION];
	       vertex *v = g->get_vertex(v_index);
	       assert(v);
	       int new_cost = u->edges[is]->cost + h[it] - h[v_index];
	       u->edges[is]->cost = new_cost;
	       //g->set_edge_cost(it, u->edges[is]->ends[DESTINATION], new_cost);
	  }
     }
     
     DistanceMatrix *D = new DistanceMatrix(g->vsize());
     
     for (it = 0; it < g->vsize(); it++)
     {
	  vertex *u = g->get_vertex(it);

	  Dijkstra(g, g->get_vertex(it));
	  
	  unsigned int is = 0;
	  for (is = 0; is < g->vsize(); is++)
	  {
	       vertex *v = g->get_vertex(is);
	       assert(v);
	       
	       D->SetDistance(it, is, v->d + h[is] - h[it]);
	  }
     }

     // Revert back the original edge weights.
     for (it = 0; it < g->vsize(); it++)
     {
	  vertex *u = g->get_vertex(it);
	  assert(u);

	  unsigned int is = 0;
	  for (is = 0; is < u->edges.size(); is++)
	  {
	       assert(u->edges[is]);
	       unsigned int v_index = u->edges[is]->ends[DESTINATION];
	       vertex *v = g->get_vertex(v_index);
	       assert(v);
	       int old_cost = u->edges[is]->cost + h[v_index] - h[it];
	       u->edges[is]->cost = old_cost;
	  }
     }
     
     //Remove the extra vertex.

     return D;
}
