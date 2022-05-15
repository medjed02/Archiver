#include "Heap.h"
#include "HuffmanArchiver.h"
#include "MyErrors.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <tuple>

enum SPECIAL_SYMBOLS {
    FILENAME_END = 256,
    ONE_MORE_FILE = 257,
    ARCHIVE_END = 258,
};

using namespace std::literals;

HuffmanArchiver::CharLen::CharLen() : sym(-1), len(0) {
}

HuffmanArchiver::CharLen::CharLen(int sym, size_t len) : sym(sym), len(len) {
}

HuffmanArchiver::CharCode::CharCode() : sym(-1), code() {
}

HuffmanArchiver::CharCode::CharCode(int sym) : sym(sym), code() {
}

bool HuffmanArchiver::CharLen::operator<(const CharLen& sym2) {
    return std::tie(this->len, this->sym) < std::tie(sym2.len, sym2.sym);
}

HuffmanArchiver::HuffmanArchiver(std::string archive_name, std::vector<std::string> files_names) :
    archive_name_(archive_name), files_names_(files_names) {
}

std::vector<size_t> HuffmanArchiver::GetFrequencyVector(const std::string& file_name) {
    std::ifstream stream(file_name);
    if (!stream.is_open()) {
        throw FileOpenError("File with name \"" + file_name + "\" not found.");
    }

    Reader reader(stream);
    std::vector<size_t> frequency(259, 0);
    while (reader.HaveSomethingToRead()) {
        ++frequency[reader.ReadChar()];
    }
    for (const unsigned char c : file_name) {
        ++frequency[c];
    }
    frequency[FILENAME_END] = 1;
    frequency[ONE_MORE_FILE] = 1;
    frequency[ARCHIVE_END] = 1;
    return frequency;
}

Trie HuffmanArchiver::GetHuffmanTrie(const std::string& file_name) {
    auto frequency = GetFrequencyVector(file_name);
    Heap heap;
    for (size_t sym = 0; sym < frequency.size(); ++sym) {
        if (frequency[sym] > 0) {
            heap.Insert(new Trie::TrieVertex(true, frequency[sym], sym));
        }
    }
    while (heap.GetSize() != 1) {
        Trie::TrieVertex* vrtx_1 = heap.GetMin();
        heap.PopMin();
        Trie::TrieVertex* vrtx_2 = heap.GetMin();
        heap.PopMin();
        Trie::TrieVertex* new_vrtx = new Trie::TrieVertex();
        new_vrtx->frequency = vrtx_1->frequency + vrtx_2->frequency;
        new_vrtx->sons[0] = vrtx_1;
        new_vrtx->sons[1] = vrtx_2;
        heap.Insert(new_vrtx);
    }
    Trie trie(heap.GetMin());
    return trie;
}

std::vector<HuffmanArchiver::CharLen> HuffmanArchiver::GetLenVector(const std::string& file_name) {
    Trie trie = GetHuffmanTrie(file_name);
    std::vector<int> lens = trie.GetLensCodes();
    std::vector<CharLen> len_vector;
    for (size_t sym = 0; sym < lens.size(); ++sym) {
        if (lens[sym] > 0) {
            len_vector.push_back(CharLen(sym, lens[sym]));
        }
    }
    std::sort(len_vector.begin(), len_vector.end());
    return len_vector;
}

std::vector<HuffmanArchiver::CharCode> HuffmanArchiver::GetCodesVector(const std::string& file_name) {
    std::vector<CharLen> lens = GetLenVector(file_name);
    std::vector<CharCode> codes;
    MyChar code;
    for (auto& sym : lens) {
        code.AddToLen(sym.len);
        codes.push_back(CharCode(sym.sym));
        codes.back().code = code;
        ++code;
    }
    return codes;
}

void HuffmanArchiver::EncodeTextFile(const std::string& file_name, Reader& reader, Writer& writer, bool last_file) {
    std::vector<CharCode> codes = GetCodesVector(file_name);
    std::vector<MyChar> code_table(SPECIAL_SYMBOLS::ARCHIVE_END + 1);
    int max_symbol_code_size = codes.size() - 1;
    std::vector<int> lens(max_symbol_code_size + 1);
    for (const auto& sym : codes) {
        code_table[sym.sym] = sym.code;
        ++lens[sym.code.GetSize()];
    }

    writer.Write9Bit(codes.size());
    for (const auto& sym : codes) {
        writer.Write9Bit(sym.sym);
    }
    for (int len = 1; len <= max_symbol_code_size; ++len) {
        writer.Write9Bit(lens[len]);
    }
    for (unsigned char sym : file_name) {
        writer.WriteSym(code_table[sym]);
    }
    writer.WriteSym(code_table[SPECIAL_SYMBOLS::FILENAME_END]);
    while (reader.HaveSomethingToRead()) {
        unsigned char sym = reader.ReadChar();
        writer.WriteSym(code_table[sym]);
    }
    if (last_file) {
        writer.WriteSym(code_table[SPECIAL_SYMBOLS::ARCHIVE_END]);
    } else {
        writer.WriteSym(code_table[SPECIAL_SYMBOLS::ONE_MORE_FILE]);
    }
}

void HuffmanArchiver::EncodeText() {
    std::ofstream ostream(archive_name_, std::ios_base::binary);
    Writer writer(ostream);
    for (size_t i = 0; i < files_names_.size(); ++i) {
        std::ifstream istream(files_names_[i]);
        if (!istream.is_open()) {
            throw FileOpenError("File with name \"" + files_names_[i] + "\" not found.");
        }
        Reader reader(istream);
        EncodeTextFile(files_names_[i], reader, writer, i + 1 == files_names_.size());
    }
    writer.ClearBuf();
}