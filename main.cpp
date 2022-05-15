#include "ArgumentParser.h"
#include "HuffmanArchiver.h"
#include "HuffmanUnarchiver.h"
#include "MyErrors.h"
#include <cstdio>
#include <fstream>
#include <iostream>

void Archive(const std::string& archive_name, const std::vector<std::string>& files_names) {
    try {
        HuffmanArchiver archiver(archive_name, files_names);
        archiver.EncodeText();
    } catch (const FileOpenError& error) {
        std::cout << "File opening error: " << error.what();
        std::remove(archive_name.c_str());
    }
}

void Unarchive(const std::string& archive_name) {
    try {
        std::ifstream stream(archive_name, std::ios_base::binary);
        if (!stream.is_open()) {
            throw FileOpenError("archive with name \"" + archive_name + "\" not found.");
        }
        HuffmanUnarchiver unarchiver(stream);
        unarchiver.Unarchive();
    } catch (const FileOpenError& error) {
        std::cout << "File opening error: " << error.what();
    } catch (const FileFormatError& error) {
        std::cout << "File format error: " << error.what();
    }
}

void PrintHelpInfo() {
    std::cout << "The Archiver\n"
                 "Help list:\n"
                 "archiver -h : information about functions\n"
                 "archiver -c archive_name file1 [file2 ...] : encode file1,... in archive with name \"archive_name\"\n"
                 "archiver -d archive_name : decode archive_name." << std::endl;
}

int main(int argc, char** argv) {
    ArgumentParser arg_parser(argc, argv);

    if (arg_parser.Contains("-h")) {
        PrintHelpInfo();
        return 0;
    } else if (arg_parser.Contains("-c")) {
        try {
            Archive(arg_parser.GetArchiveName(), arg_parser.GetFilesNames());
        } catch (const ArgumentsError& error) {
            std::cout << "Arguments error: " << error.what();
        }
        return 0;
    } else if (arg_parser.Contains("-d")) {
        try {
            Unarchive(arg_parser.GetArchiveName());
        } catch (const ArgumentsError& error) {
            std::cout << "Arguments error: " << error.what();
        }
        return 0;
    }

    return 0;
}
