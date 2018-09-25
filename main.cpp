/**
    SpellChecker, main.cpp
    Purpose: Collects user input that will be spell checked by running
    		 the SpellChecker class module.

    @author Caleb Pitts
    @9/15/18
*/

#include <iostream>
#include <ctime>
#include <sstream>
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
    std::cout << "\nNow enter a word, sentence, or entire text block for me to check for spelling errors below." << std::endl;
    std::cout << "Input text here: ";
    std::getline(std::cin, text);

    return text;
}



std::vector<std::string> fetch_text_parts(std::string text) {
    std::vector<std::string> text_parts;
    std::stringstream ss(text);
    std::string part;

    while(std::getline(ss, part, ' ')){
        text_parts.push_back(part);
    }
    // ************************* REMOVE PUNCTUATION *************************
    //for (std::vector<std::string>::const_iterator j = text_parts.begin(); j != text_parts.end(); j++) {
    //    std::cout << "CONTENTS: " << *j << std::endl;
    //}
    return text_parts;
}


int main() {
    std::string file;
    std::string topwords_file;
    std::string text;
    std::vector<std::string> text_parts;
    std::vector<std::string> alternate_spellings;
    bool top_word;

    clock_t begin = clock();  // Program timer.

    WordSet w;   // Main wordset object
    WordSet tw;  // Top1000 wordset object
    SpellChecker s;

    welcome();  // Welcome message.
    file = get_file_input();  // Gets user-selected file input.
    topwords_file = "top1000.txt";  // Default set of most used words.
    text = get_text_input();  // Gets user-selected text input.

    w = WordSet(file);
    tw = WordSet(topwords_file);

    w.create_wordset_reference();  // Generates hash table from selected txt file.
    tw.create_wordset_reference();

    clock_t lookup_begin = clock();  // Word lookup timer.

    text_parts = fetch_text_parts(text);  // Filters punctuation and fectches all individual words in the inputted text block.
    bool all_correct = true;

    // Drives program to check if each text part in 'text_parts' is spelled correctly.
    for (std::vector<std::string>::const_iterator word = text_parts.begin(); word != text_parts.end(); word++) {
        if (!w.lookup_word(*word)) {
            all_correct = false;
            alternate_spellings = s.generate_alternate_spellings(*word);
    
            // Iterates through vector and adds alternate spelling to another vector if it is found in the wordset hash table
            // I could have used 'auto' for iteration but I opted for the full vector declaration since some machines don't run c++11.
            std::cout << "Did you mean: " << std::endl;
            for (std::vector<std::string>::const_iterator alt = alternate_spellings.begin(); alt != alternate_spellings.end(); alt++) {
                if (w.lookup_word(*alt)) {
                    if (tw.lookup_word(*alt)) {
                        top_word = true;  // Found in top1000 and main wordset.
                    } else {
                        top_word = false;  // Not found in top1000, but found in main wordset.
                    }
                    // if top_word true, push to front of vector, sort all others in alphabetical order?
                    // sort in alphabetical first, then push top words to front.
                    // DONT NEED top_word, just use 'tw.lookup_word(*alt)' as the bool value
                    std::cout << "    " << *alt << ": Top1000 - " << top_word << std::endl;
                }
            }
        }
    }

    if (all_correct) {
        std::cout << "\nAccording to my wordset, everything is spelled correctly!" << std::endl;
    }

    clock_t lookup_end = clock();
    clock_t end = clock();
    double hash_elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    double lookup_elapsed_secs = double(lookup_end - lookup_begin) / CLOCKS_PER_SEC;

    std::cout << "\n\nProgram ran in " << hash_elapsed_secs << " seconds." << std::endl;
    std::cout << "Word lookup took " << lookup_elapsed_secs << " seconds." << std::endl;

    return 0;
}
