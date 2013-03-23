#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

typedef struct vertex vertex;
typedef struct edge edge;


struct 
{
     unsigned int id;
     bool visited;
     std::vector<edge*> out;
     vertex *p; //path predecessor
     int d; //shortest path distance
} vertex;

struct 
{
     vertex ends[2];
     int cost;
} edge;

class graph
{
     std::vector<edge*> edges;
     std::vertex<vertex*> s;  //designated vertices of the graph.
     
public:
     graph();
     ~graph();
};



#endif
