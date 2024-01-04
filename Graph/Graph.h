//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#ifndef DATASTRUCTURES_CPP_GRAPH_H
#define DATASTRUCTURES_CPP_GRAPH_H


#include <string>
#include "EdgeList.h"
#include "Graph/AbstractGraph.h"

namespace list {

    class Graph : public AbstractGraph{
    private:
        EdgeList *edges;
        std::vector<std::string> filteredWords;
    public:
        explicit Graph(int vertexCount);
        ~Graph();
        void addEdge(int from, int to);
        void addEdge(int from, int to, int weight);
        void addWord(std::string word);
        void addEdge(std::string from, std::string to);
        void addWords (std::vector<std::string> words, int length );
        void connectedComponentsDisjointSet();
        Path* bellmanFord(int source);
        Path* dijkstra(std::string start);
        void prim();
        void addEdges ();
        bool isConnected (std::string& word1, std::string& word2);
        void depthFirstSearch(bool* visited, int fromNode) override;
        void BFS(std::string startWord, std::string endWord) override;
        Edge* edgeList(int& edgeCount) override;
        void Dijkstra(std::string start, std::string end);
    };

}
#endif //DATASTRUCTURES_CPP_GRAPH_H
