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
    void create_wordset_reference();
    void display_hash();
    void add_word(std::string word);  // Move later??
 private:
    struct Node {
        Node* next;
        Node* prev;
        std::string word;
    };
    void traverse_file();
    void initialize_hash();
    int DJBHash(std::string word);
    int check_hash_proportion();

    std::string file_name;
    int hash_size;
    int num_filled_indexes;

    // Main hash table with Node pointer stored in each index of an array.
    Node** wordset_hash;
};
