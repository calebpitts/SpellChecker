/**
    SpellChecker, main.cpp
    Purpose: Collects user input and checks if each word is spelled correctly.
    
    Can also load their own wordset file. Correct alternate spellings are highlighted if 
    it appears in the top1000 wordset, which indicates which words are the top 1000 words 
    used in the english language.

    @author Caleb Pitts
    @9/15/18
*/

#include <iostream>
#include <ctime>
#include <sstream>
#include <algorithm>
#include "spellchecker.cpp"
#include "wordset.cpp"


void welcome() {
    std::cout << "====================================\n"; 
    std::cout << "==  Welcome to SpellChecker 1.0!  ==\n"; 
    std::cout << "==                                ==\n";
    std::cout << "==     Created by Caleb Pitts     ==\n";
    std::cout << "==              2018              ==\n"; 
    std::cout << "====================================\n";
    std::cout << "\nHello, when you input a single word or multiple lines of text, I will check for spelling errors.\n";
    std::cout << "I will also provide correct spelling suggestions if I spot any spelling errors.\n";
    std::cout << "Unfortunately, this version does not check semantics or puntuation; only spelling errors.\n";
}


std::string get_file_input() {
    std::string file;
    std::string input;
    std::cout << "\nI have over 470k words from the english language as the defualt dictionary for me to check your words.\nWould you like you to provide your own txt file of a different set of words? \nNOTE: If yes, please make sure the custom txt file is within the same directory. y/[n]: ";
    std::getline(std::cin, input);

    if (input == "y" || input == "Y") {
        std::cout << "Okay, what is the name of the custom txt file you'd like to use? ";
        std::getline(std::cin, file);
    } else {
        std::cout << "Default dictionary being used." <<std::endl;
        file = "big-wordset-cleaned.txt";
    }

    return file;
}


std::string get_text_input() {
    std::string text;
    std::cout << "\n===========================================================================================" << std::endl;
    std::cout << "\nNow enter a word, sentence, or entire text block for me to check for spelling errors below." << std::endl;
    std::cout << "Input text here: ";
    std::getline(std::cin, text);

    return text;
}


// Filters text input and stores each word as an element within a vector.
std::vector<std::string> fetch_text_parts(std::string text) {
    std::vector<std::string> text_parts;
    std::stringstream ss(text);
    std::string part;

    while(std::getline(ss, part, ' ')){
        part.erase(std::remove_if(part.begin(), part.end(), ::ispunct), part.end ());  // Removes punctuation.
        std::transform(part.begin(), part.end(), part.begin(), ::tolower);  // Makes all characters lowercase.
        text_parts.push_back(part);  // Adds modified text part (word) to vector.
    }

    return text_parts;
}

// Iterates through vector and adds alternate spelling to another vector if it is found in the wordset hash table
void drive_text_part_checks(WordSet &w, WordSet &tw, std::string word, std::vector<std::string> alternate_spellings) {
    bool found_word = false;  // Tracks whether a correct alternate spelling has been found.
    std::cout << "\nINCORRECT: " << word << "\nDid you mean: " << std::endl;
    for (int i = 0; i < alternate_spellings.size(); i++) {
        std::vector<std::string> subtext_parts;  // Resets subtext parts each time a new alternate spelling is checked.
        std::string alt = alternate_spellings[i];
        std::string part;  // Will hold each subtext part if there is a space in the current alternate spelling.
        bool split = false;  // Indicates whether text part has a space in it.
        
        // Checks if at least one character in alt word string is a space.
        for (std::string::const_iterator it = alt.begin(); it != alt.end(); it++) {
            if (*it == ' ') {
                split = true;
            }
        }
        
        // If word part has a space, then we need split and check each part of the split.
        if (split) {
            std::stringstream ss(alt);
            while(std::getline(ss, part, ' ')) {
                subtext_parts.push_back(part);  // Add each part to subtext part vector
            }
            // If both split subtexts are found in hash table, display correct alternate spelling to console.
            if (w.lookup_word(subtext_parts[0]) && w.lookup_word(subtext_parts[1])) {
                found_word = true;
                std::cout << "    " << subtext_parts[0] << " " << subtext_parts[1] << std::endl;
            }
        } else {
            if (w.lookup_word(alt)) {
                found_word = true;
                if (tw.lookup_word(alt)) {  // If found in top1000 and main wordset.
                    std::cout << "    " << alt << " <- TOP SUGGESTED" << std::endl;
                } else {
                    std::cout << "    " << alt << std::endl;
                }
            }
        }
    }
    if (!found_word) {
        std::cout << "    Sorry, no correct alternate spelling found.\n    TIP: Misspelled words must be within one edit of a correctly spelled word." << std::endl;
    }
}


// Drives all the functions that check if the word is spelled correctly and generates alternate correct
// spellings if the word is spelled incorrectly.
bool check_spelling(bool all_correct, std::string word, SpellChecker&s, WordSet &w, WordSet &tw) {
    std::vector<std::string> alternate_spellings;
    if (!w.lookup_word(word)) {
        all_correct = false;
        alternate_spellings = s.generate_alternate_spellings(word);
        drive_text_part_checks(w, tw, word, alternate_spellings);
    }
    return all_correct;
}


// Iterates through all words from the text input.
void drive_text_part_iteration(SpellChecker&s, WordSet &w, WordSet &tw, std::vector<std::string> text_parts) {
    bool all_correct = true;

    for (std::vector<std::string>::const_iterator word = text_parts.begin(); word != text_parts.end(); word++) {
        all_correct = check_spelling(all_correct, *word, s, w, tw);
    }
    if (all_correct) {
        std::cout << "\nAccording to my wordset, everything is spelled correctly!" << std::endl;
    }
}


// Computation for runtime outputs.
void compute_runtimes(clock_t begin, clock_t lookup_begin, clock_t end, clock_t lookup_end) {
    double hash_elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    double lookup_elapsed_secs = double(lookup_end - lookup_begin) / CLOCKS_PER_SEC;

    std::cout << "\nProgram ran in " << hash_elapsed_secs << " seconds." << std::endl;
    std::cout << "Word lookup took " << lookup_elapsed_secs << " seconds." << std::endl;
}


// Enables a restart ability in the program.
bool prompt_restart() {
    std::string input;
    std::cout << "\nWould you like another spellcheck? ([y]/n): ";
    std::getline(std::cin, input);
    if (input == "y" || input == "Y") {
        std::cout << "Restarting..." << std::endl;
        return true;
    } else {
        std::cout << "You didn't select yes (y). Now exiting the program... Goodbye!" << std::endl;
        return false;
    }
}


int main() {
    std::string file;
    std::string topwords_file;
    std::string text;
    bool restart = true;

    clock_t begin = clock();  // Program timer.

    WordSet w;   // Main wordset object
    WordSet tw;  // Top1000 wordset object
    SpellChecker s;  // Word manipulation object

    //// INITIAL PROGRAM STARTUP ////
    welcome(); 
    file = get_file_input();  // Gets user-selected file input.
    topwords_file = "top1000.txt";  // Default set of most used words.
    text = get_text_input();  // Gets user-selected text input.
    /////////////////////////////////

    //// GENERATES HASH TABLE OBJECTS ////
    w = WordSet(file);
    tw = WordSet(topwords_file);

    w.create_wordset_reference();  // Generates hash table from selected txt file.
    tw.create_wordset_reference();
    //////////////////////////////////////

    //// MAIN PROGRAM LOOP ////
    while (restart) {
        std::vector<std::string> text_parts;

        clock_t lookup_begin = clock();  // Word lookup timer.

        text_parts = fetch_text_parts(text);  // Filters punctuation and fetches all individual words in the inputted text block.
        drive_text_part_iteration(s, w, tw, text_parts);  // Drives program to check if each text part in 'text_parts' is spelled correctly.

        clock_t lookup_end = clock();
        clock_t end = clock();

        compute_runtimes(begin, lookup_begin, end, lookup_end);

        restart = prompt_restart();
        if (restart) {
            text = get_text_input();  // Gets the new text input from user.
        }
    }
    ///////////////////////////
    return 0;
}
