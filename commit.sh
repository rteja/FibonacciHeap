#!/bin/bash

rm -rf FibHeap/include/*~
rm -rf FibHeap/src/*~
rm -rf Graph/include/*~
rm -rf Graph/src/*~

rm -rf Graph/test/* Graph/run/* Graph/src/*.o Graph/app/*.o Graph/app/*.out
rm -rf FibHeap/test/* FibHep/run/* FibHeap/src/*.o FibHeap/app/*.o FibHeap/app/*.out

git add .
git commit -a
