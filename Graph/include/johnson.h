#ifndef _JOHNSON_H_
#define _JOHNSON_H_

#include "bellmanford.h"
#include "dijkstra.h"

typedef class DistanceMatrix DistanceMatrix;

class DistanceMatrix
{
     unsigned int vertices;
     int *D;

public:
     DistanceMatrix(int size);
     ~DistanceMatrix();
     bool IsValid();  //Is invalid when D == NULL. 
     int GetDistance(unsigned int i, unsigned int j); //Get shortest distance between i and j.
     int SetDistance(unsigned int i, unsigned int j, int distance); //Set distance between i and j.
};

// Johnson's algorithm for all pair shortest paths.
// Returns a "Valid" DistanceMatrix when there exsist a shortest paths.
// Returns an "InValid" DistanceMatrix when there is a negetive edge cycle.
DistanceMatrix Johnson(graph *g);


#endif
