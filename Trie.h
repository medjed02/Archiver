#pragma once

#include "MyChar.h"
#include <vector>

class Trie {
public:
    struct TrieVertex {
        TrieVertex* sons[2];
        bool is_terminal;
        size_t frequency;
        int num_sym;

        TrieVertex();
        TrieVertex(bool is_terminal, size_t frequency, int num_sym);
        ~TrieVertex();

        bool operator<(const TrieVertex& vrtx_2) const;
        struct CompareForHeap {
            bool operator()(const TrieVertex* vrtx_1, const TrieVertex* vrtx_2) const {
                return vrtx_1->frequency > vrtx_2->frequency;
            }
        };
    };

    Trie(TrieVertex* vrtx);
    Trie(Trie&& other);
    Trie() = default;

    Trie& operator=(Trie&& other);

    std::vector<int> GetLensCodes() const;
    bool Go(int bit);
    int GetSym();
    void AddCode(const MyChar& code, int sym);

    ~Trie();

private:
    TrieVertex* root_ = new TrieVertex;
    TrieVertex* current_ = root_;

    void DFS(TrieVertex* cur, std::vector<int>& lens, int depth = 0) const;
};