#include <iostream>
#include <fstream>

class WordSet {
 public:
    WordSet() {}
    explicit WordSet(std::string file_name) : file_name(file_name) {}
    void traverse_file();
 private:
    std::string file_name;
};