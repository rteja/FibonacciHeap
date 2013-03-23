#ifndef _FIBONACCIHEAP_H_
#define _FIBONACCIHEAP_H_

typedef struct FibHeapNode FibHeapNode;

struct FibHeapNode
{
     FibHeapNode *parent;
     FibHeapNode *children;
     // No. of children
     unsigned int degree; 
     // Did this node loose any of its children since the last time it
     // has been made the child of another node? It is unmarked whenever it
     // is made the child of another node. Also a newly created node is
     // unmarked.
     bool mark; 

     // Doubly linked list (unordered)
     FibHeapNode *left;
     FibHeapNode *right;

     // Heap key
     int key;
     // Payload pointer
     void *payload;
     
};

class FibonacciHeap 
{
     // Pointer to the minimum.
     FibHeapNode *min;
     // No. of nodes.
     unsigned int n; 

     void consolidate();
     // Make m a child of n
     void link(FibHeapNode *m, FibHeapNode *n);

public:
     FibonacciHeap();
     ~FibonacciHeap();
     void Reset();
     bool IsEmpty();
     unsigned int Size();
     void Insert(int key, void *payload);
     FibHeapNode *Minimum();
     void *ExtractMin();
     FibHeapNode* UnionHeap(FibonacciHeap *heap);
     
     
};



#endif
