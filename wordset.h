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
    bool lookup_word(std::string word);
    ~WordSet();  // Destructor
 private:
    struct Node {
        Node* next;
        Node* prev;
        std::string word;
    };
    bool traverse_file(bool adjustHash);
    void initialize_hash();
    int DJBHash(std::string word);
    void destroy_hash();

    std::string file_name;
    int hash_size;
    int num_filled_indexes;

    int hash_doubled_count;   // testing only
    int ratio_test;  // testing only

    // Main hash table with Node pointer stored in each index of an array.
    Node** wordset_hash;
};
