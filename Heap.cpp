#include "Heap.h"

Heap::Heap() {
    tree_.push_back(nullptr);
}

void Heap::Insert(Trie::TrieVertex* vrtx) {
    tree_.push_back(vrtx);
    SiftUp(tree_.size() - 1);
}

Trie::TrieVertex* Heap::GetMin() const {
    return tree_[1];
}

void Heap::PopMin() {
    tree_[1] = tree_.back();
    tree_.pop_back();
    SiftDown(1);
}

void Heap::SiftUp(int v) {
    if (v == 1) {
        return;
    }
    Trie::TrieVertex::CompareForHeap cmp;
    if (cmp(tree_[v / 2], tree_[v])) {
        std::swap(tree_[v], tree_[v / 2]);
        SiftUp(v / 2);
    }
}

void Heap::SiftDown(int v) {
    if (static_cast<size_t >(v) * 2 >= tree_.size()) {
        return;
    }

    Trie::TrieVertex::CompareForHeap cmp;
    int max_idx;
    if (static_cast<size_t >(v) * 2 + 1 == tree_.size()) {
        max_idx = v * 2;
    } else if (!cmp(tree_[v * 2], tree_[v * 2 + 1])) {
        max_idx = v * 2;
    } else {
        max_idx = v * 2 + 1;
    }

    if (cmp(tree_[v], tree_[max_idx])) {
        std::swap(tree_[v], tree_[max_idx]);
        SiftDown(max_idx);
    }
}

size_t Heap::GetSize() const {
    return tree_.size() - 1;
}