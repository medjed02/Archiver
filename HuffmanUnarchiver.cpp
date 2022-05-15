#include "HuffmanUnarchiver.h"
#include "MyChar.h"
#include "MyErrors.h"
#include "Writer.h"
#include <fstream>

enum SPECIAL_SYMBOLS {
    FILENAME_END = 256,
    ONE_MORE_FILE = 257,
    ARCHIVE_END = 258,
};

HuffmanUnarchiver::HuffmanUnarchiver(std::istream& input_stream) : istream_(input_stream) {
}

void CheckReader(Reader& reader) {
    if (!reader.HaveSomethingToRead()) {
        throw FileFormatError("The archive has an incorrect format or is damaged.");
    }
}

void HuffmanUnarchiver::UnarchiveFile(Trie& trie, Reader& reader, Writer& writer) {
    int sym = reader.GetSym(trie);
    int cnt = 0;
    while (sym != SPECIAL_SYMBOLS::ONE_MORE_FILE && sym != SPECIAL_SYMBOLS::ARCHIVE_END) {
        writer.WriteChar(sym);
        CheckReader(reader);
        sym = reader.GetSym(trie);
        ++cnt;
    }
}

bool HuffmanUnarchiver::CheckNewFile(Reader& reader) const {
    return reader.HaveSomethingToRead();
}

Trie HuffmanUnarchiver::GetCodeTrie(Reader& reader) {
    MyChar cnt_sym_byte = reader.Get9Bit();
    int cnt_sym = cnt_sym_byte.GetInt();
    std::vector<MyChar> symbols(cnt_sym);
    for (int i = 0; i < cnt_sym; ++i) {
        CheckReader(reader);
        symbols[i] = reader.Get9Bit();
    }

    int max_code_size = cnt_sym - 1;
    Trie trie;
    int now_sym = 0;
    MyChar code;
    for (int len = 1; len <= max_code_size; ++len) {
        MyChar cnt_byte = reader.Get9Bit();
        int cnt = cnt_byte.GetInt();
        code.AddToLen(len);
        for (int j = 0; j < cnt; ++j) {
            if (static_cast<size_t>(now_sym) >= symbols.size()) {
                throw FileFormatError("The archive has an incorrect format or is damaged.");
            }
            trie.AddCode(code, symbols[now_sym].GetInt());
            ++code;
            ++now_sym;
        }
    }
    return trie;
}

std::string HuffmanUnarchiver::GetFileName(Trie& trie, Reader& reader) {
    std::string file_name;
    int sym = reader.GetSym(trie);
    while (sym != SPECIAL_SYMBOLS::FILENAME_END) {
        file_name.push_back(static_cast<unsigned char>(sym));
        CheckReader(reader);
        sym = reader.GetSym(trie);
    }
    return file_name;
}

void HuffmanUnarchiver::Unarchive() {
    Reader reader(istream_);
    while (CheckNewFile(reader)) {
        Trie trie = GetCodeTrie(reader);
        std::string file_name = GetFileName(trie, reader);
        std::ofstream ostream(file_name);
        Writer writer(ostream);
        UnarchiveFile(trie, reader, writer);
    }
}