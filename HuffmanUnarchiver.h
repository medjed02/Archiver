#pragma once

#include "Reader.h"
#include "Trie.h"
#include "Writer.h"
#include <string>
#include <vector>
#include <istream>

class HuffmanUnarchiver {
public:
    explicit HuffmanUnarchiver(std::istream& input_stream);

    void Unarchive();

private:
    bool CheckNewFile(Reader& reader) const;
    Trie GetCodeTrie(Reader& reader);
    std::string GetFileName(Trie& trie, Reader& reader);
    void UnarchiveFile(Trie& trie, Reader& reader, Writer& writer);


    std::istream& istream_;
};
