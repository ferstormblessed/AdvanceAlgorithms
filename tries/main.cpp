/*
    Actividad 3.1 Implementación de "Tries"

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

*/

#include "Trie.h"
#include <iostream>
#include <vector>

int main(){

    Trie t = Trie();

    int numInsert = 0;
    int numSearch = 0;
    std::cin >> numInsert;
    std::vector<std::string> wordsInsert;
    std::vector<std::string> wordsSearch;

    //read words to insert
    for(int i = 0; i < numInsert; i++){
        std::string temp = "";
        std::cin >> temp;
        wordsInsert.push_back(temp);
    }
    //insert words
    for(int i = 0; i < wordsInsert.size(); i++){
        t.insert(wordsInsert[i]);
    }

    std::cin >> numSearch;
    //read words to search
    for(int i = 0; i < numSearch; i++){
        std::string temp = "";
        std::cin >> temp;
        wordsSearch.push_back(temp);
    }
    //search words
    for(int i = 0; i < wordsSearch.size(); i++){
        std::cout << t.search(wordsSearch[i]) << std::endl;
        // std::cout << true << std::endl;
    }
    t.dfs(t.root);

    return 0;
}