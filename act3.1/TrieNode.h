#ifndef TRIENODE_H
#define TRIENODE_H

#include <iostream>

class TrieNode {
    public:
        TrieNode* children[26];
        char val;
        bool isWord;
        TrieNode(char c);
};
//Initialize the node with a specific value
TrieNode::TrieNode(char c){
    for (int i = 0; i < 26; i++) {
        children[i] = NULL;
    }
    val = c;
    isWord = false;
}

#endif