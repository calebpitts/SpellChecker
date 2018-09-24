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
    swap_word_chars(word);
    insert_chars(word);
    delete_word_chars(word);
    replace_word_chars(word);
    split_word_chars(word);

    return alternate_spellings;
}


// Swaps each adjacent pair of characters.
void SpellChecker::swap_word_chars(std::string word) {
    for (int i = 0; i < word.length()-1; i++) {
        std::string copy = word;  // Makes a copy of word before modifying.
        std::swap(copy[i], copy[i+1]);  // Swaps adjacent characters
        alternate_spellings.push_back(copy);  // Adds alternate to vector.
    }
}


// Inserts letters 'A' to 'Z' between each adjacent pair of characters.
void SpellChecker::insert_chars(std::string word) {
    for (int i = 0; i < word.length()+1; i++) {
        for (int j = 0; j < alphabet.length(); j++) {
            std::string copy = word;  // Makes a copy of word before modifying.
            copy.insert(i, 1, alphabet[j]);  // Inserts each char in 'alphabet'.
            alternate_spellings.push_back(copy);  // Adds alternate to vector.
        }
    }
}


// Replaces each character in the word with each letter 'A' to 'Z'.
void SpellChecker::replace_word_chars(std::string word) {
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
void SpellChecker::delete_word_chars(std::string word) {
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
void SpellChecker::split_word_chars(std::string word) {
    for (int i = 1; i < word.length(); i++) {
            std::string copy = word;  // Makes a copy of word before modifying.
            copy.insert(i, " ");  // Inserts a space at index i in copy.
            alternate_spellings.push_back(copy);  // Adds alternate to vector.
    }
}


// Implements the Levenshtein distance algorithm.
// Produces the top 3 closest correctly spelled words.
// 'Closeness' is defined as the least number of edits made to
// the misspelled word to make it correct.
std::string SpellChecker::levenshtein_distance(std::string str1, std::string str2) {
    return str1;
}


// size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
// {
//   const size_t m(s1.size());
//   const size_t n(s2.size());
 
//   if( m==0 ) return n;
//   if( n==0 ) return m;
 
//   size_t *costs = new size_t[n + 1];
 
//   for( size_t k=0; k<=n; k++ ) costs[k] = k;
 
//   size_t i = 0;
//   for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
//   {
//     costs[0] = i+1;
//     size_t corner = i;
 
//     size_t j = 0;
//     for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
//     {
//       size_t upper = costs[j+1];
//       if( *it1 == *it2 )
//       {
//           costs[j+1] = corner;
//       }
//       else
//       {
//         size_t t(upper<corner?upper:corner);
//         costs[j+1] = (costs[j]<t?costs[j]:t)+1;
//       }
 
//       corner = upper;
//     }
//   }
 
//   size_t result = costs[n];
//   delete [] costs;
 
//   return result;
// }
