#include <stdlib.h>
#include <assert.h>
#include "dgraph.h"


vertex* create_vertex()
{
     vertex *v = (vertex*) calloc(1, sizeof(vertex));
     assert(v);
     return v;
}

void destroy_vertex(vertex *v)
{
     assert(v);
     free(v);
     return;
}


dgraph::dgraph(unsigned int n)
{
     assert(n >= 0);
     
     while (n)
     {
	  vertices.push_back(create_vertex());
	  n--;
     }
     return;
}

dgraph::~dgraph()
{
     for (unsigned int it = 0; it < vertices.size(); it++)
     {
	  assert(vertices[it]);
	  for (unsigned int is = 0; is < vertices[it]->edges.size(); is++)
	  {
	       assert(vertices[it]->edges[is]);
	       free(vertices[it]->edges[is]);
	       vertices[it]->edges[is] = NULL;
	  }

	  free(vertices[it]);
     }
     return;
}

unsigned int dgraph::vsize()
{
     return vertices.size();
}

unsigned int dgraph::esize()
{
     int edges = 0;
     for (int i = 0; i < vertices.size(); i++)
	  edges += vertices[i]->edges.size();
     return edges;
}

bool dgraph::is_connected()
{
     vertex *v = vertices[vertices.size() - 1];
     unsigned int visited = 0;
     std::vector<vertex*> v_stack;
     int it = 0;
     v_stack.push_back(v);

     // do a BFS which will serve as a reachability test.
     while(v_stack.size())
     {
	  v = v_stack[v_stack.size() - 1];
	  assert(v);
	  if (!v->visited)
	  {
	       visited++;
	       v->visited = true;
	       for (it = 0; it < v->edges.size(); it++)
		    if (!vertices[v->edges[it]->ends[1]]->visited)
			 v_stack.push_back(vertices[v->edges[it]->ends[1]]);
	  }
	  v_stack.pop_back();
	  
     }

     return (visited == vsize());
}

vertex* dgraph::get_vertex(unsigned int index)
{
     assert(index >= 0);
     assert(index < (vsize() - 1));
 
     return (vertices[index]);
}

unsigned int dgraph::add_edge(unsigned int u, unsigned int v, int cost)
{
     assert(u < (vsize() - 1));
     assert(u < (vsize() - 1));

     for (unsigned int it = 0; it < u->edges.size(); it++)
     {
	  if (u->edges[it]->ends[1] == v)
	  {
	       u->edges[it]->cost = cost;
	       return u->edges;
	  }
     }

     edge *e = (edge *) malloc(sizeof(edge));
     e->ends[0] = u;
     e->ends[1] = v;
     e->cost = cost;
     
     u->edges.push_back(e);
     return u->edges.size();
}

unsigned int dgraph::del_edge(unsigned int u, unsigned int v)
{
     assert(u > (vsize() - 1));
     assert(v > (vsize() - 1));

     unsigned int it = 0;

     for (it = 0;it < u->edges.size(); it++)
     {
	  if (u->edges[it]->ends[1] == v)
	       break;
     }

     assert(it < u->edges.size());
     u->edges.erase(u->edges.begin() + it);

     return u->edges.size();
}

unsigned int dgraph::add_vertex()
{
     vertex *v = create_vertex();
     vertices.push_back(v);
     return vsize();
}

