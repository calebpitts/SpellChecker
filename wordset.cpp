/**
    SpellChecker, wordset.cpp
    Purpose: Loads specified txt file of correct words into a hash map.
             Dynamically increases in size depending on the size of the 
             txt file.

    @author Caleb Pitts
    @9/15/18
*/

#include "./wordset.h"


void WordSet::create_wordset_reference() {
    hash_size = 100;    // Default hash size before any adjustments.
    bool adjustHash = true;
    while (adjustHash) {
        initialize_hash();  // Initializes hash table.
        adjustHash = traverse_file(adjustHash);  // Fills hash table dynamically.
    }
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


// - Loops through every line in the wordset file, calling add_word for each line.
// - Checks if proportion of empty indexes and filled ones exceeds 85%.
// - Adjusts the hash table size so that less than 85% of the indexes are used.
//   I do this for closer O(1) time during retrieval, addition, and reading.
bool WordSet::traverse_file(bool adjustHash) {
    std::string line;
    std::ifstream myfile(file_name);

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            add_word(line);  // Adds the current word to the hash table.
            if (num_filled_indexes/hash_size > 0.85) {
                destroy_hash();  // Deletes the current hash table.
                hash_size *= 2;
                adjustHash = true;
                break;
            } else {
                adjustHash = false;
            }
        }
        myfile.close();
    } else {
        std::cout << "Unable to open <" << file_name << ">. Make sure you selected the right file and try again." << std::endl;
    }
    return adjustHash;
}


// Used DJB hash function implementation to return
// a hashed index within the bounds of the hash array.
int WordSet::DJBHash(const std::string word) {
    int hash = 5381;  // Most efficient hash constant.

    for (int i = 0; i < word.length(); i++) {
       hash = ((hash << 5) + hash) + word.at(i);
    }

    // Mods hash value with hash_size to ensure all hashed indexes are inbounds.
    return abs(hash) % hash_size;
}


// Adds a word string parameter to the wordset hash table.
void WordSet::add_word(const std::string word) {
    // Hashes word using the DJB hash function to reduce collisions.
    int hashed_index = DJBHash(word);

    // Creates an initial node if the index in the hash table is empty/nullptr.
    if (wordset_hash[hashed_index] == nullptr) {
        Node* node = new Node();
        node->prev = nullptr;
        node->word = word;
        node->next = nullptr;
        wordset_hash[hashed_index] = node;
        num_filled_indexes++;  // Increment the number of filled indexes.
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


// Returns true if word argument is found in the wordset hash table.
bool WordSet::lookup_word(const std::string word) {
    int hashed_index = DJBHash(word);  // Gets word location.
    Node* currentNode = wordset_hash[hashed_index];
    while (currentNode != nullptr) {
        if (currentNode->word == word) {
            return true;  // Word found
        } else {
            // Checks the next node at the location in the hash array.
            currentNode = currentNode->next;
        }
    }
    return false;  // Reached end of linked list, not found (returns false)
}


// Iterates through each node and deletes it's contents.
// Sets each empty array index to nullptr to prevent garbage values.
void WordSet::destroy_hash() {
    for (int i = 0; i < hash_size; i++) {
        Node* currentNode = wordset_hash[i];  // Creates a pointer to the first node in the index.
        while (currentNode != nullptr) {
            Node* temp = currentNode->next;   // Temp points to next node
            delete currentNode;
            currentNode = temp;
        }
        wordset_hash[i] = nullptr;
    }
    delete wordset_hash;  // Deletes pointer to the empty array (wordset_hash).
}


// Destroys the final hash once the program is done using the WordSet object
WordSet::~WordSet() {
    destroy_hash();
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
    // std::cout << "Hash table adjusted in size (doubled) " << hash_doubled_count << " times." << std::endl;
    // std::cout << "Filled index to hash size ratio is " << ratio_test << "." << std::endl;
}
