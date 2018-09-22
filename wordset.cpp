/**
    SpellChecker, wordset.cpp
    Purpose: Loads specified txt file of correct words into a hash map.
             Dynamically increases in size depending on the size of the 
             txt file.

    @author Caleb Pitts
    @version 1.1 8/15/18
*/

#include "./wordset.h"



void WordSet::create_wordset_reference() {
    hash_size = 500;    // Default hash size before any adjustments.
    initialize_hash();  // Initializes hash table.
    traverse_file();    // Fills hash table dynamically.
}


// Initializes an empty hash table named 'wordset_hash'.
void WordSet::initialize_hash() {
    // Initializes a dynamic array of node pointers.
    wordset_hash = new Node*[hash_size];
    int num_filled_indexes = 0;   // Filled index counter.

    // Initializes all elements in the wordset_hash array to nullptr.
    for (int i = 0; i < hash_size; i++) {
        wordset_hash[i] = nullptr;
    }
}


// Loops through every line in the wordset file, calling add_word for each line.
void WordSet::traverse_file() {
    std::string line;
    std::ifstream myfile(file_name);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            add_word(line);  // Adds the current word to the hash table.
        }
        myfile.close();
    } else {
        std::cout << "Unable to open <" << file_name << ">. Make sure you selected the right file and try again." << std::endl;
    }
}


///////////// INEFFICIENT HASH FUNCTION /////////////
// // Returns hashed index using the string's ascii value.
// int WordSet::hash_function(std::string word) {
//         int total_ascii = 0;
//         for (int i = 0; i < word.length(); i++) {
//             total_ascii = total_ascii + int(word[i]);
//         }
//         return total_ascii % hash_size;
// }
/////////////////////////////////////////////////////


// Used DJB hash function implementation to return
// a hashed index within the bounds of the hash array.
int WordSet::DJBHash(std::string word) {
    int hash = 5381;  // Most efficient hash constant.

    for (int i = 0; i < word.length(); i++) {
       hash = ((hash << 5) + hash) + word.at(i);
    }

    // Mods hash value with hash_size to ensure all hashed indexes are inbounds.
    return abs(hash) % hash_size;
}


// Adds a word string parameter to the wordset hash table.
void WordSet::add_word(std::string word) {
    // Hashes word using the DJB hash function.
    int hashed_index = DJBHash(word);

    // Creates an initial node if the index in the hash table is empty/nullptr.
    if (wordset_hash[hashed_index] == nullptr) {
        Node* node = new Node();
        node->prev = nullptr;
        node->word = word;
        node->next = nullptr;
        wordset_hash[hashed_index] = node;
        check_hash_proportion();
    } else {
        // Else adds node to the front of the linked list.
        // Saves the current first node in tempNode.
        Node* tempNode = wordset_hash[hashed_index];

        // Creates the node that will be added.
        // Sets newNode to point to the current first node (tempNode).
        Node* newNode = new Node();
        newNode->prev = nullptr;
        newNode->word = word;
        newNode->next = tempNode;

        // Sets the index pointer to the new node.
        wordset_hash[hashed_index] = newNode;
        tempNode->prev = newNode;
    }
}


// Checks whether the hash array size needs to be adjusted
// each time an empty index is filled.
int WordSet::check_hash_proportion() {
    // adjust_hash_size() 
    // Checks if there is a healthy number of empty indexes.
    // If more than 3/4 of the array indexes have been filled with at least one node.
    return 0;
}


// Prints out visual representation of the current hash map. (For testing only)
void WordSet::display_hash() {
    std::cout << "HASH MAP: " << std::endl;
    for (int i = 0; i < hash_size; i++) {
        std::cout << "HASH[" << i << "] -> ";
        if (wordset_hash[i] == nullptr) {
            std::cout << "NULLPTR\n";
        } else {
            Node* currentNode = wordset_hash[i];
            while (currentNode != nullptr) {
                std::cout << currentNode->word;
                if (currentNode->next != nullptr) {
                    std::cout << " -> ";
                }
                currentNode = currentNode->next;
            }
            std::cout << std::endl;
        }
    }
}
