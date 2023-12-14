//
// Created by nk033893 on 12/14/2023.
//

#include <fstream>
#include <iostream>
#include "PuzzleGame.h"


int main(){

    PuzzleGame puzzleGame;

    std::vector<std::string> words = puzzleGame.readFromFile();

    list::Graph graphWith3Letters = puzzleGame.createGraphWithLetterNumber(words, 3);
//    list::Graph graphWith4Letters = puzzleGame.createGraphWithLetterNumber(words, 4);
//    list::Graph graphWith5Letters = puzzleGame.createGraphWithLetterNumber(words, 5);


    return 0;
}

std::vector<std::string> PuzzleGame::readFromFile (){
    std::vector<std::string> words;

    std::ifstream file ("C:\\Users\\TEMP\\CLionProjects\\graph-puzzle-game-nehir-kirmizisakal-ozu\\data");

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

list::Graph PuzzleGame::createGraphWithLetterNumber (std::vector<std::string>& words, int letterNumber ){
    std::vector<std::string> filteredWords;

    for( const std::string& word: words){
        if(word.length() == static_cast<size_t>(letterNumber)){
            filteredWords.push_back(word);
        }

    }

    list::Graph graph (filteredWords.size());

    for(size_t i = 0 ; i < filteredWords.size() ; i++){
        for(size_t j = i + 1; j < filteredWords.size() ; j++){
            if(isConnected(filteredWords[i], filteredWords[j])){
                graph.addEdge(i,j);
                std::cout <<"edge added.";
            }

        }
    }

    return graph;
}

bool PuzzleGame::isConnected (std::string& word1, std::string& word2){
    int sameLetterCount = 0;

    for(int i = 0; i < word1.length(); i++){
        if(word1[i]== word2[i]){
            sameLetterCount ++;
        }

        if(sameLetterCount > 0){
            return false;
        }
    }

    if(sameLetterCount == 0){
        return false;
    }

    return true;
}