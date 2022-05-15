#include "ArgumentParser.h"
#include "MyErrors.h"
#include <algorithm>

ArgumentParser::ArgumentParser(int argc, char** argv) {
    for (int i = 0; i < argc; ++i) {
        keys_.emplace_back(argv[i]);
    }
}

bool ArgumentParser::Contains(const std::string& key) const {
    return std::find(keys_.begin(), keys_.end(), key) != keys_.end();
}

std::string ArgumentParser::GetArchiveName() const {
    if (keys_.size() < 3) {
        throw ArgumentsError("The archive name is not specified.");
    }
    return keys_[2];
}

std::vector<std::string> ArgumentParser::GetFilesNames() const {
    if (keys_.size() < 4) {
        throw ArgumentsError("Filenames are not specified.");
    }
    return {keys_.begin() + 3, keys_.end()};
}