#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

typedef struct vertex vertex;
typedef struct edge edge;


struct 
{
     unsigned int id;
     bool visited;
} vertex;

struct
{
     vertex ends[2];
} edge;

class graph
{
     std::vector<edge> edges;
     vertex *s;  //designated vertex of the graph.

public:
     graph();
     ~graph();
};



#endif
