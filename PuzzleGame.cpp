//
// Created by nk033893 on 12/14/2023.
//

#include <fstream>
#include <iostream>
#include "PuzzleGame.h"


int main(){

    PuzzleGame puzzleGame;

    std::vector<std::string> words = puzzleGame.readFromFile();
    std::vector<std::string> filteredWords = puzzleGame.filteredWords(words,5);


    list::Graph graph = puzzleGame.createGraph(filteredWords);

    graph.breadthFirstSearch(filteredWords, "sappy", "moody");


//    list::Graph graphWith5Letters = puzzleGame.createGraph(words, 5);


    return 0;
}

std::vector<std::string> PuzzleGame::readFromFile (){
    std::vector<std::string> words;

    std::ifstream file ("C:\\Users\\TEMP\\CLionProjects\\graph-puzzle-game-nehir-kirmizisakal-ozu\\english-dictionary.txt");

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

std::vector<std::string> PuzzleGame::filteredWords (std::vector<std::string> words, int length ){
    std::vector<std::string> filteredWords;

    for( const std::string& word: words){
        if(word.length() == static_cast<size_t>(length)){
            filteredWords.push_back(word);
        }

    }
    return filteredWords;
}



list::Graph PuzzleGame::createGraph (std::vector<std::string>& filteredWords){

    list::Graph graph (filteredWords.size());

    for(size_t i = 0 ; i < filteredWords.size() ; i++){
        for(size_t j = i + 1; j < filteredWords.size() ; j++){
            if(isConnected(filteredWords[i], filteredWords[j])){
                graph.addEdge(i,j);
                graph.addEdge(j,i);

            }

        }
    }

    return graph;
}

bool PuzzleGame::isConnected (std::string& word1, std::string& word2){
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