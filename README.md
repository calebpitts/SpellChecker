# SpellChecker 1.0
A program that checks the spelling of a word, line of text, or whole paragraph of text inputted by the user. It also provides suggestions to correct the word if it is misspelled. 

## How To Run It
1. Download the repository 
2. Open your command line
3. Navigate to the directory you saved the SpellChecker
4. Run main with ```./main``` or recompile ```main.cpp``` (I used g++ for compiling this project)

## How It Works
The spell checker splits isolates each word and removes punctuation. Then, each word is compared with over 460k words in an 
english wordset. If the word is found in the wordset, it is spelled correctly, otherwise it is spelled incorrectly. 

Then the program displays alternate word suggestions that are spelled correctly by manipulating the original incorrect word in 
multiple different ways to see if it can find a smililar word in the large wordset. Once it has found similar words that are 
spelled correctly, the program highlights words that are most commonly used in the english language by comparing those alternate spellings with another wordset called top1000, which gives the top 1000 most commonly used english words. 

You can also load your own wordset different from the default large wordset that I have provided by specifying the directory  in a field that is provided when the program runs. Or you can just select 'No' and the program will run with the default wordset.

## Data Structure Implementation
As you can imagine, iterating over a regular list container or array that has 460k elements is quite impractical. So, I used a hash map that takes each word it needs to check and assigned it a hashed index value in a dynamic array. I used the DJB Hash function, which consistently provided me with a low collision rate. I used linked lists to handle cases where collisions do occur. I have the hash map in a class called WordSet, so I can create multiple hash maps by simply passing in the file I want to read from. I took advantage of this by also using a top1000.txt file which gives me the 1000 most commonly used words in the english language. This helped me rank alternate spellings based on relevance.

If you'd like to learn more about how the program works, check out the comments in the source code, or just email me directly. Enjoy!
