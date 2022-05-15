#include <string>

class MyError : public std::exception {
public:
    explicit MyError(const std::string& info_error) : info_error_(info_error) {}
    const char* what() const noexcept override {
        return info_error_.c_str();
    }

private:
    std::string info_error_;
};

class FileOpenError : public MyError {
public:
    explicit FileOpenError(const std::string& info_error) : MyError(info_error) {
    }
};

class FileFormatError : public MyError {
public:
    explicit FileFormatError(const std::string& info_error) : MyError(info_error) {
    }
};

class ArgumentsError : public MyError {
public:
    explicit ArgumentsError(const std::string& info_error) : MyError(info_error) {
    }
};