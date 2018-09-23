/**
    SpellChecker, main.cpp
    Purpose: Collects user input that will be spell checked by running
    		 the SpellChecker class module.

    @author Caleb Pitts
    @version 1.1 8/15/18
*/

#include <iostream>
#include <ctime>
#include "spellchecker.cpp"
#include "wordset.cpp"  // MAYBE do inheritance??

// Returns the user's input text and file. The text will be cross referenced
// with a correct set of words indicated by the selected file. Each file is
// a different language.
std::string get_file_name_input() {
    std::string file_name;
    std::cout << "Select the txt file/langauge you want: ";
    std::getline(std::cin, file_name);

    return file_name;
}

std::string get_text_block_input() {
    std::string text_block;
    std::cout << "Please enter your block of text that you would like to be spell checked: ";
    std::getline(std::cin, text_block);

    return text_block;
}


int main() {
    std::string text_block;
    std::string file_name;
    // file_name  = get_file_name_input();
    file_name = "big-wordset-cleaned.txt";
    // text_block = get_text_block_input();
    text_block = "testing";

    std::cout << "Text  Block INPUT: " << text_block << std::endl;
    std::cout << "Selected TXT FILE: " << file_name << std::endl;

    clock_t begin = clock();  // Begin timing section.

    WordSet w;
    SpellChecker s;

    w = WordSet(file_name);
    w.create_wordset_reference();

    std::string word;
    std::cout << "Enter text block here: ";
    std::getline(std::cin, word);

    bool found = w.lookup_word(word);
    
    if (found) {
        std::cout << "Spelled correctly" << std::endl;
    } else {
        std::cout << "Incorrectly spelled." << std::endl;
    }

    // w.display_hash();  // REMOVE LATER

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    std::cout << "Program ran in " << elapsed_secs << " seconds." << std::endl;

    return 0;
}
