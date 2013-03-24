#include "johnson.h"

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
     if (D)
	  free(D);
     vertices = 0;

     return;
}


DistanceMatrix Johnson(graph *g)
{
     
}
