#include "trie.h"
#include <algorithm>
TrieNode* createNode() {
    TrieNode* node = new TrieNode();
    node->isEnd = false;
    return node;
}

void insertTrie(TrieNode* root, string word) {
    TrieNode* curr = root;
    for (char c : word) {
        if (curr->children.find(c) == curr->children.end())
            curr->children[c] = createNode();
        curr = curr->children[c];
    }
    curr->isEnd = true;
}

void dfs(TrieNode* node, string prefix, vector<string>& result) {
    if (node->isEnd)
        result.push_back(prefix);

    for (auto& p : node->children)
        dfs(p.second, prefix + p.first, result);
}

vector<string> searchPrefix(TrieNode* root, string prefix) {
    TrieNode* curr = root;

    for (char c : prefix) {
        if (curr->children.find(c) == curr->children.end())
            return {};
        curr = curr->children[c];
    }

    vector<string> result;
    dfs(curr, prefix, result);
    return result;
}