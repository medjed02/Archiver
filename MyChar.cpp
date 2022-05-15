#include "MyChar.h"

MyChar::MyChar(size_t size) {
    data_.resize(size, false);
}

MyChar::MyChar() {
    data_ = {};
}

MyChar::~MyChar() {
    data_.clear();
}

int MyChar::GetBit(int ind) const {
    if (data_[data_.size() - ind - 1]) {
        return 1;
    } else {
        return 0;
    }
}

void MyChar::SetBit(int ind) {
    data_[data_.size() - ind - 1] = true;
}

size_t MyChar::GetSize() const {
    return data_.size();
}

int MyChar::GetInt() const {
    if (data_.size() != 9) {
        return 0;
    }
    int result = 0;
    for (int i = 0; i < 9; ++i) {
        result ^= (GetBit(i) << i);
    }
    return result;
}

void MyChar::operator++() {
    int first_zero = -1;
    for (int i = data_.size() - 1; i >= 0; --i) {
        if (!data_[i]) {
            first_zero = i;
            break;
        }
    }
    if (first_zero == -1) {
        std::vector<bool> new_data(data_.size() + 1, false);
        new_data[0] = true;
        data_ = new_data;
    } else {
        data_[first_zero] = true;
        for (size_t i = first_zero + 1; i < data_.size(); ++i) {
            data_[i] = false;
        }
    }
}

void MyChar::AddToLen(int len) {
    for (int i = data_.size(); i < len; ++i) {
        data_.push_back(false);
    }
}

MyChar::MyChar(const MyChar& other) {
    data_ = other.data_;
}

MyChar::MyChar(MyChar&& other) {
    data_ = other.data_;
    other.data_.clear();
}

MyChar& MyChar::operator=(const MyChar& other) {
    if (this == &other) {
        return *this;
    }
    data_ = other.data_;
    return *this;
}

MyChar& MyChar::operator=(MyChar&& other) {
    if (this == &other) {
        return *this;
    }
    data_ = other.data_;
    other.data_.clear();
    return *this;
}

std::vector<bool>::iterator MyChar::begin() {
    return data_.begin();
}

std::vector<bool>::iterator MyChar::end() {
    return data_.end();
}

std::vector<bool>::const_iterator MyChar::begin() const {
    return data_.begin();
}

std::vector<bool>::const_iterator MyChar::end() const {
    return data_.end();
}