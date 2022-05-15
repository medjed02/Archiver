#include "Writer.h"

Writer::Writer(std::ostream& output_stream) : stream_(output_stream) {
    buf_ = 0u;
    cursor_ = 0;
    buf_not_empty_ = false;
}

void Writer::WriteChar(unsigned char c) {
    char dop_c = static_cast<char>(c);
    stream_.write(&dop_c, 1);
}

void Writer::WriteBit(int bit) {
    if (cursor_ > 7) {
        ClearBuf();
    }
    buf_ |= (bit << cursor_);
    buf_not_empty_ = true;
    ++cursor_;
}

void Writer::ClearBuf() {
    if (buf_not_empty_) {
        char dop_c = static_cast<char>(buf_);
        stream_.write(&dop_c, 1);
        buf_ = 0u;
        buf_not_empty_ = false;
        cursor_ = 0;
    }
}

void Writer::WriteSym(const MyChar& c) {
    for (const auto& bit : c) {
        if (bit) {
            WriteBit(1);
        } else {
            WriteBit(0);
        }
    }
}

void Writer::Write9Bit(int num) {
    for (int i = 0; i < 9; ++i) {
        WriteBit(((num >> i) & 1));
    }
}