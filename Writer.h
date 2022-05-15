#pragma once

#include "MyChar.h"
#include <ostream>
#include <vector>

class Writer {
public:
    explicit Writer(std::ostream& output_stream);

    void WriteChar(unsigned char c);
    void WriteBit(int bit);
    void WriteSym(const MyChar& c);
    void Write9Bit(int num);
    void ClearBuf();

private:
    std::ostream& stream_;
    unsigned char buf_;
    bool buf_not_empty_;
    int cursor_;
};