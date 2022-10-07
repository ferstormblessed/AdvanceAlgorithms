#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <string>

class Trie {
    public:
        TrieNode* root;
        Trie();
        void insert(std::string word);
        bool search(std::string word);
        void dfs(TrieNode* node);
};

//Initialize the trie
Trie::Trie(){
    root = new TrieNode('\0');
}

//Time Complexity O(m * n), where m = average length of words and n = number of words
void Trie::dfs(TrieNode* node){
    for (int i = 0; i < 26; i++) { 
        if (node -> children[i] == NULL){
            continue;
        }
        int value = node -> children[i] -> val;
        char letter = char (value + 'a');
        std::cout << letter << " | ";
        dfs(node -> children[i]);
    }
}

//Time Complexity O(n)
//Space Complexity O(n)
void Trie::insert(std::string word){
    TrieNode* node = root;
    int curr = 0;
            
    for (int i = 0; i < word.size(); i++) {
        curr = word[i] - 'a';
        char c = curr;
        if (node->children[curr] == NULL) {
            node->children[curr] = new TrieNode(c);
        }
        node = node->children[curr];
    }
    node->isWord = true;
}

//Time Complexity O(n)
//Space Complexity O(1)
bool Trie::search(std::string word){
    TrieNode* node = root;
    int curr = 0;
            
    for (int i = 0; i < word.size(); i++) {
        curr = word[i] - 'a';
        if (node->children[curr] == NULL) {
            return false;
        }
        node = node->children[curr];
    }
            
    return node->isWord;
}

#endif