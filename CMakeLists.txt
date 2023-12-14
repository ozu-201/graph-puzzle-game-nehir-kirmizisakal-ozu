cmake_minimum_required(VERSION 3.25)
project(graph_puzzle_game_nehir_kirmizisakal_ozu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(graph_puzzle_game_nehir_kirmizisakal_ozu
        Graph/AbstractGraph.cpp
        Graph/AbstractGraph.h
        DisjointSet/DisjointSet.cpp
        DisjointSet/DisjointSet.h
        Graph/Edge.cpp
        Graph/Edge.h
        Graph/EdgeList.cpp
        Graph/EdgeList.h
        Graph/Graph.cpp
        Graph/Graph.h
        Heap/Heap.cpp
        Heap/Heap.h
        Heap/HeapNode.cpp
        Heap/HeapNode.h
        Heap/MinHeap.cpp
        Heap/MinHeap.h
        Queue/Node.cpp
        Queue/Node.h
        Graph/Path.cpp
        Graph/Path.h
        Queue/Queue.cpp
        Queue/Queue.h
        DisjointSet/Set.cpp
        DisjointSet/Set.h PuzzleGame.cpp PuzzleGame.h)
