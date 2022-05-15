#include "Reader.h"

Reader::Reader(std::istream& input_stream) : stream_(input_stream) {
    cursor_ = 8;
}

unsigned char Reader::ReadChar() {
    buf_ = 0;
    char c;
    stream_.read(&c, 1);
    buf_ = static_cast<unsigned char>(c);
    return buf_;
}

bool Reader::HaveSomethingToRead() const {
    return stream_.peek() != EOF;
}

MyChar Reader::Get9Bit() {
    MyChar sym(9);
    for (int i = 0; i < 9; ++i) {
        int bit = GetBit();
        if (bit == 1) {
            sym.SetBit(i);
        }
    }
    return sym;
}

int Reader::GetBit() {
    if (cursor_ > 7) {
        ReadChar();
        cursor_ = 0;
    }
    int result = ((buf_ >> cursor_) & 1);
    ++cursor_;
    return result;
}

int Reader::GetSym(Trie& trie) {
    while (!trie.Go(GetBit())) {
    }
    return trie.GetSym();
}