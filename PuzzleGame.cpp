//
// Created by nk033893 on 12/14/2023.
//

#include <fstream>
#include <iostream>
#include "PuzzleGame.h"


int main(){

//    PuzzleGame puzzleGame;
//
//    std::vector<std::string> words = puzzleGame.readFromFile();
//
//    list::Graph graph(82975);
//    graph.addWords(words,5);
//    graph.addEdges();
//
//    graph.BFS("sappy", "happy");


    list::Graph graph4(3);
    graph4.addWord("dark");
    graph4.addWord("bark");
    graph4.addWord("barn");
    graph4.addEdge("dark", "bark");
    graph4.addEdge("bark", "barn");

    std::cout << "Test Case: Adding Edges with One-Letter Difference (4 letter words)\n";
    std::cout << "Shortest Path from 'dark' to 'barn' (BFS):\n";
    graph4.BFS("dark", "barn");
    std::cout << "Shortest Path from 'dark' to 'barn' (dijkstra):\n";
    graph4.Dijkstra("dark", "barn"); // couldn't do the dijkstra.
    std::cout << "------------------------------------------\n";

    return 0;
}

std::vector<std::string> PuzzleGame::readFromFile (){
    std::vector<std::string> words;

    std::ifstream file ("C:\\Users\\TEMP.OZUN\\CLionProjects\\graph-puzzle-game-nehir-kirmizisakal-ozu\\english-dictionary.txt");

    std::string word;

    if(file.is_open()){

        while(std::getline(file, word)){
            words.push_back(word);
        }

        file.close();
    }

    else{
        std::cerr<<"Unable to open the file";

    }

    return words;
}



