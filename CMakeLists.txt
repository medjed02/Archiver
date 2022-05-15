cmake_minimum_required(VERSION 3.15)
project(Archiver)

set(CMAKE_CXX_STANDARD 20)

add_executable(Archiver
    main.cpp
        ArgumentParser.cpp
        MyChar.cpp
        Reader.cpp
        Writer.cpp
        Trie.cpp
        Heap.cpp
        HuffmanArchiver.cpp
        HuffmanUnarchiver.cpp
)
