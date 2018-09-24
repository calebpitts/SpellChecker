/**
    SpellChecker, spellchecker.h
    Purpose: Produces suggested word corrections using string manipulation. 
    		 Provides the most relevant spell corrections based on Levenshtein's distance algorithm.

    @author Caleb Pitts
    @9/15/18
*/

#include <iostream>
#include <vector>
#include <string>

// Takes in hash map with correct words.
class SpellChecker {
 public:
    SpellChecker() {}
    std::vector<std::string> generate_alternate_spellings(std::string word);
    std::string levenshtein_distance(std::string str1, std::string str2);

 private:
    void swap_word_chars(std::string word);
    void insert_chars(std::string word);
    void delete_word_chars(std::string word);
    void replace_word_chars(std::string word);
    void split_word_chars(std::string word);

    // Holds all correct alternate spellings of the checked word.
    std::vector<std::string> alternate_spellings;
    // Alphabet constant used for string manipulation
    std::string alphabet;
};
