/**
    SpellChecker, wordset.h
    Purpose: Header file for cpp file that loads specified txt file of 
             correct words into a hash map. Dynamically increases in size 
             depending on the size of the specified txt file.

    @author Caleb Pitts
    @version 1.1 8/15/18
*/

#include <iostream>
#include <string>
#include <fstream>

class WordSet {
 public:
    WordSet() {}
    explicit WordSet(std::string file_name) : file_name(file_name) {}
    void traverse_file();
    void display_hash();  // REMOVE THIS LATER
    void add_word(std::string word);  // MOVE THIS LATER
    void initialize_hash(); // MOVE THIS TO PRIVATE
 private:
    struct Node {
        Node* next;
        Node* prev;
        std::string word;
    };
    // void initialize_hash();
    int hash_function(std::string word);
    std::string file_name;
    int hash_size; //FIX??
    Node* wordset_hash[10000];  // Main hash table with one Node pointer for each index in an array.
};
