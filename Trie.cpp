#include "MyErrors.h"
#include "Trie.h"

Trie::TrieVertex::TrieVertex() {
    is_terminal = false;
    frequency = 0;
    num_sym = -1;
    sons[0] = nullptr;
    sons[1] = nullptr;
}

Trie::TrieVertex::TrieVertex(bool is_terminal, size_t frequency, int num_sym) : is_terminal(is_terminal),
    frequency(frequency), num_sym(num_sym) {
    sons[0] = nullptr;
    sons[1] = nullptr;
}

Trie::Trie(TrieVertex* vrtx) {
    root_ = vrtx;
    current_ = root_;
}

Trie::TrieVertex::~TrieVertex() {
    delete sons[0];
    delete sons[1];
}

Trie::~Trie() {
    delete root_;
}

bool Trie::Go(int bit) {
    if (current_ == nullptr) {
        throw FileFormatError("The archive has an incorrect format or is damaged.");
    }
    current_ = current_->sons[bit];
    return current_->is_terminal;
}

int Trie::GetSym() {
    int result = current_->num_sym;
    current_ = root_;
    return result;
}

void Trie::DFS(TrieVertex* cur, std::vector<int>& lens, int depth) const {
    if (cur == nullptr) {
        return;
    } else if (cur->is_terminal) {
        lens[cur->num_sym] = depth;
        return;
    } else {
        DFS(cur->sons[0], lens, depth + 1);
        DFS(cur->sons[1], lens, depth + 1);
    }
}

std::vector<int> Trie::GetLensCodes() const {
    std::vector<int> lens_codes(259, 0);
    DFS(root_, lens_codes);
    return lens_codes;
}

void Trie::AddCode(const MyChar& code, int sym) {
    TrieVertex* now = root_;
    for (const auto& bit : code) {
        if (bit) {
            if (now->sons[1] == nullptr) {
                TrieVertex* new_vrtx = new TrieVertex;
                now->sons[1] = new_vrtx;
            }
            now = now->sons[1];
        } else {
            if (now->sons[0] == nullptr) {
                TrieVertex* new_vrtx = new TrieVertex;
                now->sons[0] = new_vrtx;
            }
            now = now->sons[0];
        }
    }
    now->is_terminal = true;
    now->num_sym = sym;
}

Trie::Trie(Trie&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
    current_ = other.current_;
    other.current_ = nullptr;
}

Trie& Trie::operator=(Trie&& other) {
    if (this == &other) {
        return *this;
    }
    root_ = other.root_;
    other.root_ = nullptr;
    current_ = other.current_;
    other.current_ = nullptr;
    return *this;
}

bool Trie::TrieVertex::operator<(const TrieVertex& vrtx_2) const {
    return this->frequency > vrtx_2.frequency;
}