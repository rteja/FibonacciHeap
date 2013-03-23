#ifndef _DGRAPH_H_
#define _DGRAPH_H_

#include <vector>

typedef struct vertex vertex;
typedef struct edge edge;


struct vertex
{
     bool visited;
     std::vector<edge*> edges;
     vertex *p; //path predecessor
     int d; //shortest path distance
};

struct edge 
{
     unsigned int ends[2];
     int cost;
};

class dgraph
{
     std::vector<vertex*> vertices;
     std::vector<vertex*> s;  //designated vertices of the graph.
     
public:
     dgraph();
     ~dgraph();
     unsigned int vsize();  //returns no. of vertices.
     unsigned int esize();  //returns no. of edges.
     vertex *get_vertex(unsigned int v_index);
     unsigned int add_edge(unsigned int u, unsigned int v, int cost);
     unsigned int add_vertex();
     unsigned int del_edge(unsigned int u, unsigned int v);
     unsigned int del_vertex(unsigned int u);
     bool is_connected();
};



#endif
