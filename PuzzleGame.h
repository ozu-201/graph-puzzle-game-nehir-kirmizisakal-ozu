//
// Created by nk033893 on 12/14/2023.
//

#ifndef GRAPH_PUZZLE_GAME_NEHIR_KIRMIZISAKAL_OZU_PUZZLEGAME_H
#define GRAPH_PUZZLE_GAME_NEHIR_KIRMIZISAKAL_OZU_PUZZLEGAME_H

#include <string>
#include <vector>
#include "Graph/Graph.h"

namespace list{
    class Graph;
}

class PuzzleGame{

public:
    std::vector<std::string> readFromFile ();
    list::Graph createGraphWithLetterNumber (std::vector<std::string>& words, int letterNumber );
    bool isConnected (std::string& word1, std::string& word2);

};

#endif //GRAPH_PUZZLE_GAME_NEHIR_KIRMIZISAKAL_OZU_PUZZLEGAME_H
