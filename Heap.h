#pragma once

#include "Trie.h"
#include <queue>
#include <vector>

class Heap {
public:
    Heap();
    void Insert(Trie::TrieVertex* vrtx);
    Trie::TrieVertex* GetMin() const;
    void PopMin();
    size_t GetSize() const;

private:
    void SiftUp(int v);
    void SiftDown(int v);

    std::vector<Trie::TrieVertex*> tree_;
};