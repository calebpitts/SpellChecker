/**
    SpellChecker, spellchecker.cpp
    Purpose: Defines declarations made in 'spellchecker.h'. Detailed explanation can be
             found in 'spellchecker.h'.

    @author Caleb Pitts
    @9/15/18
*/
#include "./spellchecker.h"



// Calls helper functions that collectively generate
// all possible edits to the misspelled word.
std::vector<std::string> SpellChecker::generate_alternate_spellings(std::string word) {
    alphabet = "abcdefghijklmnopqrstuvwxyz";  // Constant used for string manipulation.
    alternate_spellings.clear();  // Clears whatever alternate spellings was before.
    swap_word_chars(word);
    insert_chars(word);
    delete_word_chars(word);
    replace_word_chars(word);
    split_word_chars(word);

    return alternate_spellings;
}


// Swaps each adjacent pair of characters.
void SpellChecker::swap_word_chars(const std::string word) {
    for (int i = 0; i < word.length()-1; i++) {
        std::string copy = word;  // Makes a copy of word before modifying.
        std::swap(copy[i], copy[i+1]);  // Swaps adjacent characters
        alternate_spellings.push_back(copy);  // Adds alternate to vector.
    }
}


// Inserts letters 'A' to 'Z' between each adjacent pair of characters.
void SpellChecker::insert_chars(const std::string word) {
    for (int i = 0; i < word.length()+1; i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            std::string copy = word;  // Makes a copy of word before modifying.
            copy.insert(i, 1, alphabet[j]);  // Inserts each char in 'alphabet'.
            alternate_spellings.push_back(copy);  // Adds alternate to vector.
        }
    }
}


// Replaces each character in the word with each letter 'A' to 'Z'.
void SpellChecker::replace_word_chars(const std::string word) {
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            std::string copy = word;  // Makes a copy of word before modifying.
            // Replaces 1 character from the ith index of copy with 1 character
            // from the jth index of alphabet.
            copy.replace(i, 1, alphabet, j, 1);
            alternate_spellings.push_back(copy);  // Adds alternate to vector.
        }
    }
}


// Deletes each character one at a time from the word.
void SpellChecker::delete_word_chars(const std::string word) {
    for (int i = 0; i < word.length(); i++) {
        std::string copy = word;  // Makes a copy of word before modifying.
        copy.erase(i, 1);  // Specifies removal of 1 character at index i.
        alternate_spellings.push_back(copy);  // Adds alternate to vector.
    }
}


// - Splits each adjacent pair of characters by inserting a space between
//   each adjacent character to produce two words.
// - Since I am splitting one word to two, each word must be found in the hash table
//   to be marked as a correct spelling suggestion.
void SpellChecker::split_word_chars(const std::string word) {
    for (int i = 1; i < word.length(); i++) {
            std::string copy = word;  // Makes a copy of word before modifying.
            copy.insert(i, " ");  // Inserts a space at index i in copy.
            alternate_spellings.push_back(copy);  // Adds alternate to vector.
    }
}


