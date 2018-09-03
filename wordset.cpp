/**
    SpellChecker, wordset.cpp
    Purpose: Loads specified txt file of correct words into a hash map.
    		 Dynamically increases in size depending on the size of the 
    		 txt file.

    @author Caleb Pitts
    @version 1.1 8/15/18
*/

#include "./wordset.h"

void WordSet::traverse_file() {
    std::string line;
    std::ifstream myfile(file_name);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            std::cout << line << std::endl;  // Now call method that adds each word to hash table
        }
        myfile.close();
    } else {
        std::cout << "Unable to open <" << file_name << ">. Make sure you selected the right file and try again." << std::endl;
    }
}
