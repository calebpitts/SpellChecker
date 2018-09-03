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
            //std::cout << line << std::endl;  // Now call method that adds each word to hash table
            add_word(line);  // Adds the word to the wordset hash table. 
        }
        myfile.close();
    } else {
        std::cout << "Unable to open <" << file_name << ">. Make sure you selected the right file and try again." << std::endl;
    }
}

// Initializes all elements in the wordset_hash array to nullptr.
void WordSet::initialize_hash() {
    hash_size = 10000;
    std::cout << "initializing..." << std::endl;
    for (int i = 0; i < hash_size; i++) {
        wordset_hash[i] = nullptr;
    }
}


// Hashes strings to indexes within the range of the max index in the wordset hash table.
int WordSet::hash_function(std::string word) {
        int total_ascii = 0;
        for(int i = 0; i < word.length(); i++) {
        	total_ascii = total_ascii + int(word[i]);
        }
        return total_ascii % hash_size;
}


// Adds a word string parameter to the wordset hash table.
void WordSet::add_word(std::string word) {
    int hashed_index = hash_function(word);
    // Hashes the word and finds its index.
    if (wordset_hash[hashed_index] == nullptr) {
        // Sets initial node if the index is empty/nullptr.
        Node* node = new Node();
        node->prev = nullptr;
        node->word = word;
        node->next = nullptr;
        wordset_hash[hashed_index] = node;
    } else {
        // std::cout << "RUNNING NEXT.." <<std::endl;
        Node* tempNode = wordset_hash[hashed_index];  // Saves the first node in tempNode.

        // Creates the node that will be added. 
        Node* newNode = new Node();
        newNode->prev = nullptr;
        newNode->word = word;
        newNode->next = tempNode;

        // Sets the index pointer to the new node.
        wordset_hash[hashed_index] = newNode;
        tempNode->prev = newNode;
    }
}

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
