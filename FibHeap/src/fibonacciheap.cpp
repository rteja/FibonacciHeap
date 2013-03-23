#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>

#include "fibonacciheap.h"


FibHeapNode*  FibHeapNode_Create()
{
     FibHeapNode *node = (FibHeapNode*) calloc(1, sizeof(FibHeapNode));
     assert(node);

     node->left = node;
     node->right = node;
     return node;
}

FibHeapNode*  FibHeapNode_Create(int key, void* payload)
{
     FibHeapNode *node = FibHeapNode_Create();
     node->key = key;
     node->payload = payload;
     return node;
}

// Insert newNode into the node's level list
void  FibHeapNode_InsertLL(FibHeapNode *node, FibHeapNode *newNode)
{
     assert(node);

     newNode->parent = node->parent;

     FibHeapNode *nodeRight = node->right;
     
     node->right = newNode;
     newNode->left = node;
     newNode->right = nodeRight;
     nodeRight->left = newNode;

     if (node->parent)
	  node->parent->degree++;

     return;
}

// Detach node from its level linked list.
FibHeapNode*  FibHeapNode_DetachLL(FibHeapNode *node)
{
     assert(node);
 
     // This is not fool proof what if the linked list 
     // contains only one element?
     // as of now, assert it!
     assert(node->left != node);

     node->left->right = node->right;
     node->right->left = node->left;

     return (node->right);
}

// Merges linked list2 into linked list1
FibHeapNode*  FibHeapNode_MergeLL(FibHeapNode *list1, FibHeapNode *list2)
{
     if (list1 == NULL)
     {
	  list1 = list2;
	  return list1;
     }

     if (list2 == NULL)
     {
	  return list1;
     }

     FibHeapNode *list1Right = list1->right;
     FibHeapNode *list2Left = list2->left;
     
     list2Left->right = list1Right;
     list1Right->left = list2Left;

     list1->right = list2;
     list2->left = list1;

     FibHeapNode *node = list1->right;
     while (node != list1Right)
     {
	  node->parent = list1->parent;
	  node = node->right;
     }

     return ((list1->key < list2->key)? list1 : list2);
}


// FibonacciHeap constructor
FibonacciHeap::FibonacciHeap()
{
     min = NULL;
     n = 0;
}

// FibonacciHeap destructor
FibonacciHeap::~FibonacciHeap()
{
     while (n)
	  ExtractMin();
     
     return;
}


// Returns the no. of elements in the heap.
unsigned int  FibonacciHeap::Size()
{
     return n;
}

// Resets the Fibonacci Heap to initial state
void  FibonacciHeap::Reset()
{
     min = NULL;
     n = 0;
     return;
}

// Returns true of Fibonacci Heap is empty.
bool  FibonacciHeap::IsEmpty()
{
     return (n == 0);
}

// Returns the minimum key payload element. 
// Returns NULL if Fibonacci heap is empty.
FibHeapNode* FibonacciHeap::Minimum()
{
     return min;
}

// Fibonacci Heap insertion
void  FibonacciHeap::Insert(int key, void* payload)
{
     FibHeapNode *newNode = FibHeapNode_Create(key, payload);
     
     if (min == NULL)
     {
	  // No of nodes at this point must be zero.
	  assert(!n);
	  min = newNode;
     }
     else
     {
	  FibHeapNode_InsertLL(min, newNode);
     }
     
     if (key < min->key)
	  min = newNode;
     
     n++;
     return;
}

// A new heap is merged into the current heap.
// Freeing the unused heap is upto the owner.
FibHeapNode*  FibonacciHeap::UnionHeap(FibonacciHeap *heap)
{
     if (heap->IsEmpty())
     {
	  heap->Reset();
	  return min;
     }

     // If heap is empty
     if (n == 0)
     {
	  min = heap->Minimum();
	  n = heap->Size();
	  heap->Reset();
	  return min;
     }

     // Merge the root lists
     FibHeapNode_MergeLL(min, heap->Minimum());

     // Check if the key of merged heap is smaller than min. key of current heap.
     if (heap->Minimum()->key < min->key)
	  min = heap->Minimum();

     // Remove all pointers from the merged heap structure.
     heap->Reset();
     
     return min;
}

// Detach m from its level linked list and attach to children of n.
void  FibonacciHeap::link(FibHeapNode *m, FibHeapNode *n)
{
     assert(m != n);

     // Remove m from its level linked list
     FibHeapNode_DetachLL(m);
     // Attach m to the children list of n.
     if (n->children == NULL)
     {
	  m->left = m;
	  m->right = m;
	  n->children = m;
     }
     else
	  FibHeapNode_InsertLL(n->children, m);

     m->mark = false;

     return;
}

#define D(n) n
void  FibonacciHeap::consolidate()
{
     FibHeapNode **A = (FibHeapNode**) (calloc(D(n), sizeof(FibHeapNode*)));
     assert(A);
     
     FibHeapNode *it = min;
     std::vector<FibHeapNode*> rootList;
     while (true)
     {
	  rootList.push_back(it);
	  it = it->right;

	  // We want to essentially loop on the root level list.
	  // so break the list collection loop once we hit the first element.
	  if (it == min)
	       break;
     }
     int i;
     for (i = 0; i < rootList.size(); i++)
     {
	  FibHeapNode *x = rootList[i];
	  unsigned int d = x->degree;
	  while (A[d] != NULL)
	  {
	       FibHeapNode *y = A[d];
	       if (x->key > y->key)
	       {
		    // Swap x and y
		    FibHeapNode *z = x;
		    x = y; y = z;
	       }
	       printf("linking %d to %d..\n", y->key, x->key);
	       link(y, x);
	       A[d] = NULL;
	       d++;
	  }
	  A[d] = x;
     }
     
     min = NULL;
     for (i = 0; i < D(n); i++)
     {
	  if (A[i] != NULL)
	  {
	       A[i]->left = A[i];
	       A[i]->right = A[i];

	       if (min != NULL)
	       {
		    //min->right = A[i];
		    FibHeapNode_InsertLL(min, A[i]);
	       }

	       if (min == NULL || (A[i]->key < min->key))
		    min = A[i];
	       
	  }
     }
     free(A);
     return;
}

// Extracts the minimum element from the heap.
// Returns the payload directly.
void*  FibonacciHeap::ExtractMin()
{
     void *payload = NULL;

     if (min)
     {
	  payload = min->payload;
	  
	  // Attach the children list to the root list
	  FibHeapNode *children = min->children;
	  min->children = NULL;
	  FibHeapNode_MergeLL(min, children);
	  n += min->degree;

	  // Detach current minimum
	  if (min->left != min)   // If there are more than one elements in the root list.
	  {
	       FibHeapNode_DetachLL(min);
	       FibHeapNode *newMin = min->right;
	       free(min);
	       min = newMin;
	  }
	  else 
	  {
	       free(min);
	       min = NULL;
	  }
	  
	  // Reduce the size of heap by 1
	  n--;
	  
	  if (min == NULL)
	       assert(!n); // n must be zero at this point. This is a sanity check.
	  else
	       consolidate();
	  
     }

     return payload;
}

