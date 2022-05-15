#pragma once

#include <string>
#include <vector>

class ArgumentParser {
public:
    ArgumentParser(int argc, char** argv);

    bool Contains(const std::string& key) const;

    std::string GetArchiveName() const;
    std::vector<std::string> GetFilesNames() const;

private:
    std::vector<std::string> keys_;
};
