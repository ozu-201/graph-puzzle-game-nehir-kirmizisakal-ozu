//
// Created by Olcay Taner YILDIZ on 8.05.2023.
//

#include <vector>
#include <iostream>
#include "Graph.h"
#include "DisjointSet/DisjointSet.h"
#include "Queue/Queue.h"
#include "Heap/MinHeap.h"

namespace list {

    Graph::Graph(int _vertexCount) : AbstractGraph(_vertexCount){
        edges = new EdgeList[vertexCount];
        for (int i = 0; i < vertexCount; i++) {
            edges[i] = EdgeList();
        }
    }

    void Graph::addEdge(int from, int to) {
        Edge* edge = new Edge(from, to, 1);
        edges[from].insert(edge);
    }

    void Graph::addEdge(int from, int to, int weight) {
        Edge* edge = new Edge(from, to, weight);
        edges[from].insert(edge);
    }

    Graph::~Graph() {
        delete[] edges;
    }

    void Graph::addWord(std::string word) {
        filteredWords.push_back(word);
    }


    void Graph::addEdge(std::string from, std::string to) {
        for(int i = 0; i < filteredWords.size(); i++){
            for(int j = 0; j < filteredWords.size(); j++){
                if(filteredWords[i] == from && filteredWords[j] == to && isConnected(filteredWords[i], filteredWords[j])){
                    addEdge(i,j);
                    addEdge(j,i);
                }
            }
        }
    }


    void Graph::addWords (std::vector<std::string> words, int length ){

        for( const std::string& word: words){
            if(word.length() == static_cast<size_t>(length)){
                filteredWords.push_back(word);
            }

        }
    }



    void Graph::addEdges (){

        for(size_t i = 0 ; i < filteredWords.size() ; i++){
            for(size_t j = i + 1; j < filteredWords.size() ; j++){
                if(isConnected(filteredWords[i], filteredWords[j])){
                    addEdge(i,j);
                    addEdge(j,i);

                }

            }
        }
    }

    bool Graph::isConnected (std::string& word1, std::string& word2){
        int differentLetterCount = 0;

        for(int i = 0; i < word1.length(); i++){
            if(word1[i]!= word2[i]){
                differentLetterCount ++;
            }

            if(differentLetterCount > 1){
                return false;
            }
        }

        return differentLetterCount == 1;
    }




    void Graph::connectedComponentsDisjointSet() {
        Edge* edge;
        int toNode;
        DisjointSet sets = DisjointSet(vertexCount);
        for (int fromNode = 0; fromNode < vertexCount; fromNode++){
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                toNode = edge->getTo();
                if (sets.findSetRecursive(fromNode) != sets.findSetRecursive(toNode)){
                    sets.unionOfSets(fromNode, toNode);
                }
                edge = edge->getNext();
            }
        }
    }

    void Graph::depthFirstSearch(bool *visited, int fromNode) {
        Edge* edge;
        int toNode;
        edge = edges[fromNode].getHead();
        while (edge != nullptr){
            toNode = edge->getTo();
            if (!visited[toNode]){
                visited[toNode] = true;
                depthFirstSearch(visited, toNode);
            }
            edge = edge->getNext();
        }
    }

    void Graph::BFS(std::string startWord, std::string endWord) {

        std::vector<bool> visited (filteredWords.size(), false);
        std::vector<int> parent (filteredWords.size(), -1);
        std::vector<std::string> orderedPath;
        Edge* edge;
        int fromNode, toNode;
        Queue queue = Queue();

        int startingPosition;

        for(startingPosition = 0; startingPosition < filteredWords.size(); startingPosition++){
            if(filteredWords[startingPosition] == startWord){
                break;
            }
        }
        queue.enqueue(new Node(startingPosition));
        visited[startingPosition] = true;

        while (!queue.isEmpty()){
            fromNode = queue.dequeue()->getData();
            edge = edges[fromNode].getHead();

            while (edge != nullptr) {
                toNode = edge->getTo();
                if (!visited[toNode]){
                    visited[toNode] = true;
                    queue.enqueue(new Node(toNode));
                    parent[toNode] = fromNode;

                    if(filteredWords[toNode] == endWord){
                        int current = toNode;
                        while(current != -1){
                            orderedPath.push_back(filteredWords[current]);
                            current = parent[current];

                        }

                        for(int i = orderedPath.size() -1; i >= 0; i--){
                            std::cout << orderedPath[i] << std::endl;
                        }

                        return;
                    }
                }
                edge = edge->getNext();
            }
        }

        if(orderedPath.size() == 0 || orderedPath.size() == 1){
            std::cout << "No path." << std::endl;
        }

    }

    Path *Graph::bellmanFord(int source) {
        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        for (int i = 0; i < vertexCount - 1; i++){
            for (int fromNode = 0; fromNode < vertexCount; fromNode++){
                edge = edges[fromNode].getHead();
                while (edge != nullptr){
                    int toNode = edge->getTo();
                    int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                    if (newDistance < shortestPaths[toNode].getDistance()){
                        shortestPaths[toNode].setDistance(newDistance);
                        shortestPaths[toNode].setPrevious(fromNode);
                    }
                    edge = edge->getNext();
                }
            }
        }
        return shortestPaths;
    }

    void Graph::Dijkstra(std::string start, std::string end){
        Path *paths = dijkstra(start);

    }

    Path *Graph::dijkstra(std::string start) {
        int source;

        for(int i = 0;i < filteredWords.size() ; i++){
            if(filteredWords[i] == start){
                source = i;
                break;
            }
        }

        Edge* edge;
        Path* shortestPaths = initializePaths(source);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(shortestPaths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                int newDistance = shortestPaths[fromNode].getDistance() + edge->getWeight();
                if (newDistance < shortestPaths[toNode].getDistance()){
                    int position = heap.search(toNode);
                    heap.update(position, newDistance);
                    shortestPaths[toNode].setDistance(newDistance);
                    shortestPaths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
        return shortestPaths;
    }


    Edge *Graph::edgeList(int& edgeCount) {
        Edge* list;
        edgeCount = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                edgeCount++;
                edge = edge->getNext();
            }
        }
        list = new Edge[edgeCount];
        int index = 0;
        for (int i = 0; i < vertexCount; i++){
            Edge* edge = edges[i].getHead();
            while (edge != nullptr){
                list[index] = Edge(edge->getFrom(), edge->getTo(), edge->getWeight());
                index++;
                edge = edge->getNext();
            }
        }
        return list;
    }

    void Graph::prim() {
        Path* paths = initializePaths(0);
        MinHeap heap = MinHeap(vertexCount);
        for (int i = 0; i < vertexCount; i++){
            heap.insert(HeapNode(paths[i].getDistance(), i));
        }
        while (!heap.isEmpty()){
            HeapNode node = heap.deleteTop();
            int fromNode = node.getName();
            Edge* edge = edges[fromNode].getHead();
            while (edge != nullptr){
                int toNode = edge->getTo();
                if (paths[toNode].getDistance() > edge->getWeight()){
                    int position = heap.search(toNode);
                    heap.update(position, edge->getWeight());
                    paths[toNode].setDistance(edge->getWeight());
                    paths[toNode].setPrevious(fromNode);
                }
                edge = edge->getNext();
            }
        }
    }

}