#pragma once

#include <vector>

class MyChar {
public:
    MyChar();
    explicit MyChar(size_t size);
    MyChar(const MyChar& other);
    MyChar(MyChar&& other);

    MyChar& operator=(const MyChar& other);
    MyChar& operator=(MyChar&& other);

    int GetBit(int ind) const;
    void SetBit(int ind);
    size_t GetSize() const;
    int GetInt() const;
    void AddToLen(int len);


    std::vector<bool>::iterator begin();
    std::vector<bool>::iterator end();
    std::vector<bool>::const_iterator begin() const;
    std::vector<bool>::const_iterator end() const;

    void operator++();

    ~MyChar();

private:
    std::vector<bool> data_;
};