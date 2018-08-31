def gather_wordset(file_name):
    # Collects wordset from file and returns list of cleaned words that are not all uppercase.
    clean_wordset = []            # List of cleaned words
    excluded_wordset = []   # List of words that were excluded form the clean dataset (uppercase words)

    file = open(file_name, "r")
    for line in file:
        # This primarily excludes all uppercase abreviations like RPV
        # I take these out because when I lowercase the user's input,
        # rpv would be marked correct.
        if line.isupper():
            excluded_wordset.append(line)
        else:
            clean_wordset.append(line)

    file.close()
    return clean_wordset, excluded_wordset


def display_wordsets(clean_wordset, excluded_wordset):
    # Gives a description of the two wordsets returned from gather_wordset
    print("List of {} excluded words:".format(len(excluded_wordset)))
    print("There are", len(excluded_wordset), "words in this dataset.")
    print(excluded_wordset[:10], "...")  # Prints the first 11 words to check accuracy.
    print()
    print("List of {} cleaned words:".format(len(clean_wordset)))
    print("There are", len(clean_wordset), "words in this dataset.")
    print(clean_wordset[:10], "...")  # Prints the first 11 words to check accuracy.


def write_cleaned_wordset(clean_wordset, new_file):
    file = open(new_file, "w")

    # Writes clean wordset to a new txt file
    for word in clean_wordset:
        file.write(word)

    file.close()


def main():
    file_name = "big-wordset.txt"
    new_file = "big-wordset-cleaned.txt"

    clean_wordset, excluded_wordset = gather_wordset(file_name)
    display_wordsets(clean_wordset, excluded_wordset)
    write_cleaned_wordset(clean_wordset, new_file)

    print("\nDone. Cleaned wordset written to", new_file)


if __name__ == '__main__':
    main()
