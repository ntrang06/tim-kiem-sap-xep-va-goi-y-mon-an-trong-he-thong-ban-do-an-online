#pragma once
#ifndef TRIE_H
#define TRIE_H

#include <map>
#include <vector>
#include <string>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEnd;
};

TrieNode* createNode();
void insertTrie(TrieNode* root, string word);
vector<string> searchPrefix(TrieNode* root, string prefix);

#endif