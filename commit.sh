#!/bin/bash

rm -rf FibHeap/include/*~ FibHeap/include/*#
rm -rf FibHeap/src/*~ FibHeap/src/*#
rm -rf Graph/include/*~ Graph/include/*#
rm -rf Graph/src/*~ Graph/src/*#

rm -rf Graph/test/* Graph/run/* Graph/src/*.o Graph/app/*.o Graph/app/*.out
rm -rf FibHeap/test/* FibHep/run/* FibHeap/src/*.o FibHeap/app/*.o FibHeap/app/*.out

git add .
git commit -a
