#pragma once

#include "MyChar.h"
#include "Trie.h"
#include "Reader.h"
#include "Writer.h"
#include <string>
#include <vector>

class HuffmanArchiver {
public:
    HuffmanArchiver() = default;
    HuffmanArchiver(std::string archive_name, std::vector<std::string> files_names);

    void EncodeText();

private:
    struct CharLen {
        int sym;
        size_t len;

        CharLen();
        CharLen(int sym, size_t len);
        bool operator<(const CharLen& sym2);
    };

    struct CharCode {
        int sym;
        MyChar code;

        CharCode();
        CharCode(int sym);
        ~CharCode() = default;
    };

    std::vector<size_t> GetFrequencyVector(const std::string& file_name);
    Trie GetHuffmanTrie(const std::string& file_name);
    std::vector<CharLen> GetLenVector(const std::string& file_name);
    std::vector<CharCode> GetCodesVector(const std::string& file_name);
    void EncodeTextFile(const std::string& file_name, Reader& reader, Writer& writer, bool last_file);

    std::string archive_name_;
    std::vector<std::string> files_names_;
};