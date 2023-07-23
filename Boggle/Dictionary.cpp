#include <iomanip>
#include <vector>
#include "Dictionary.h"
#include "fstream"

// Your code here


Dictionary::Dictionary() {
    this->root = new Node;
    this->root->isWord = false;
    this->numWords = 0;
}

Dictionary::~Dictionary() {
    MakeEmpty();
}

Dictionary::Dictionary(const Dictionary &otherDict) {
    // BinaryTree-Summer2022 6/30 02:35:19
    // *this = otherDict; or
    // this->operator=(otherDict);
    copyOther(otherDict);
}

Dictionary::Dictionary(const string& filename) {
    this->root = new Node;
    this->root->isWord = false;
    this->numWords = 0;

    LoadDictionaryFile(filename);

}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    // BinaryTree-Summer2022 6/30 02:35:19
    // destroyHelper(this->root);
    // copyHelper(this->root, otherDict.root);

    if (this != &otherDict)
        copyOther(otherDict);

    return *this;
}

void Dictionary::LoadDictionaryFile(const string& filename) {
    ifstream file(filename);
    // Check if opening the file succeeded
    if (file.fail() || !file.is_open()) {
        throw DictionaryError(filename + " failed to open");
    }

    string word;

    while (file >> word){
        AddWord(word);
    }
}

void Dictionary::SaveDictionaryFile(const string& filename) {
    ofstream file;
    file.open(filename);
    // Check if opening the file succeeded
    if (file.fail()) {
        throw DictionaryError(filename + " failed to open");
    }

    Node* currNode = this->root;

    SaveDictionaryHelper(currNode, "", file);

    file.close();
}

void Dictionary::AddWord(const string& word) {
    Node* currNode = this->root;
    for (int i = 0; i < word.size(); i++){
        if (!isValidChar(word[i]))
            throw DictionaryError("Invalid character");
        if (currNode->ptrs[char2Int(word[i])] == nullptr or currNode->ptrs[char2Int(word[i])]->chr != word[i]){
            currNode->ptrs[char2Int(word[i])] = new Node;
            currNode->ptrs[char2Int(word[i])]->chr = word[i];
            if (i == (word.size() - 1)){
                currNode->ptrs[char2Int(word[i])]->isWord = true;
                //Bookkeeping
                this->numWords++;
            }
        }
        currNode = currNode->ptrs[char2Int(word[i])];
    }
}

void Dictionary::MakeEmpty() {
    destroyHelper(this->root);
    this->root = new Node;
    this->numWords = 0;
}

bool Dictionary::IsWord(string word) {
    Node* currNode = this->root;

    for (int i = 0; i < word.size(); i++){
        if (!isValidChar(word[i]))
            throw DictionaryError("Invalid character");

        if (currNode->ptrs[char2Int(word[i])] != nullptr){
            // Check for upper/lower case
            if (currNode->ptrs[char2Int(word[i])]->chr != word[i]){
                return false;
            }

            // We've reached the last character of the word, return theisWord flag
            if (i == (word.size() - 1)){
                return currNode->ptrs[char2Int(word[i])]->isWord;
            }

            // Otherwise, let's keep going on to the next letter
            currNode = currNode->ptrs[char2Int(word[i])];
        } else
            // Return false if any character doesn't even exist.
            return false;
    }

    return false;
}

bool Dictionary::IsPrefix(string word) {
    // "" would always be considered a valid prefix
    if (word.empty())
        return true;

    Node* currNode = this->root;

    for (int i = 0; i < word.size(); i++){
        if (!isValidChar(word[i]))
            throw DictionaryError("Invalid character");

        if (currNode->ptrs[char2Int(word[i])] != nullptr){
            // Check for upper/lower case
            if (currNode->ptrs[char2Int(word[i])]->chr != word[i])
                return false;

            // We've reached the last character of the word, return true.
            if (i == (word.size() - 1))
                return true;

            // Otherwise, let's keep going on to the next letter
            currNode = currNode->ptrs[char2Int(word[i])];
        } else
            // Return false if any character doesn't even exist.
            return false;
    }

    // Example of a scenario of this function reaching this point would be when word = ""
    return false;
}

int Dictionary::WordCount() {
    return this->numWords;
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    this->numWords = otherDict.numWords;

    copyHelper(this->root, otherDict.root);

}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    // Let's traverse all the way to the ends of each alphabet letter
    for (int i = 0; i < NUM_CHARS; i++){
        if (thisTree->ptrs[i] != nullptr){
            destroyHelper(thisTree->ptrs[i]);
        }
    }
    // Once we reached the last one, then we can start to delete
    delete thisTree;
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if (otherTree == nullptr){
        thisTree = nullptr;
        return;
    }

    thisTree = new Node;
    thisTree->chr = otherTree->chr;
    thisTree->isWord = otherTree->isWord;
    for (int i = 0; i < NUM_CHARS;i++){
        copyHelper(thisTree->ptrs[i], otherTree->ptrs[i]);
    }

}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if (curr->isWord){
        outFile << currPrefix << endl;
    }

    for (char i = 0; i < NUM_CHARS; i++){
        char next = 'a' + i;
        Node *childNode = curr->ptrs[i];
        if(childNode){
            // Concat the letter into the prefix
            currPrefix.push_back(next);
            // Repeat until current Node isWord
            SaveDictionaryHelper(childNode, currPrefix, outFile);

            // Clear the buffer for the next iterative recursive call.
            currPrefix.pop_back();
        }
    }
}

int Dictionary::char2Int(char intg) {
    int rtn = char(intg - 97);
    if (rtn >=0)
        return rtn;
    else
        return char(intg - 65);
}

bool Dictionary::isValidChar(char chr) {
    if (char2Int(chr) < 0)
        return false;
    else
        return true;
}