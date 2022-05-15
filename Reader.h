#pragma once

#include "MyChar.h"
#include "Trie.h"
#include <istream>

class Reader {
public:
    explicit Reader(std::istream& input_stream);

    unsigned char ReadChar();
    int GetBit();
    MyChar Get9Bit();
    bool HaveSomethingToRead() const;
    int GetSym(Trie& trie);

private:
    std::istream& stream_;
    unsigned char buf_;
    int cursor_;
};