#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError : public std::exception{
public:
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    /*
    * Function:
    * The default constructor that creates a basic Dictionary object.
    *
    * Precondition:
    * No preconditions needed to invoke this default constructor.
    *
    * Postcondition:
    * The function does not return anything. This constructor creates a root node and sets the root isWord to false.
    * The total number of words is also set to 0.
    */
    Dictionary();

    /*
    * Function:
    * The default deconstructor that destroys the Dictionary object.
    *
    * Precondition:
    * No preconditions needed to invoke this deconstructor.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. The deconstructor invokes destroyHelper().
    */
    ~Dictionary();  // I will not require this

    /*
    * Function:
    * The copy constructor that creates a basic Dictionary object given another Dictionary object.
    *
    * Precondition:
    * otherDict passed must be a valid Dictionary object.
    *
    * Postcondition:
    * The function does not return anything. This copy constructor copies all contents of otherDict to this. It
    * invokes copyOther() to accomplish what is known as a "deep copy".
    */
    Dictionary(const Dictionary& otherDict);    // copy constructor

    /*
    * Function:
    * The second constructor that creates a basic Dictionary object when explicitly given a path to a file.
    *
    * Precondition:
    * A valid file, including the path, must be passed. Additionally, the file format must be a valid
    * Dictionary format where each word is stored in a newline inside a txt file.
    *
    * Postcondition:
    * The function does not return anything. This function also does not throw exceptions except for the possibility
    * that an exception is thrown by the call to LoadDictionary() function. This constructor initializes the object
    * exactly how Dictionary() initializes the root.
    */
    explicit Dictionary(const string& filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.

    /*
    * Function:
    * The overload that copies all of otherDict into this.
    *
    * Precondition:
    * otherDict must be a Dictionary object.
    *
    * Postcondition:
    * The overload returns the pointer of the current (this*) Dictionary object. This overload only copies data if
    * otherDict does not equal to the current Dictionary (this).
    */
    Dictionary& operator=(const Dictionary& otherDict);

    /*
    * Function:
    * This function is responsible for loading words into the current Dictionary given a valid Dictionary file format
    * and its path.
    *
    * Precondition:
    * A valid file, including the path, must be passed as filename. Additionally, the file format must be a valid
    * Dictionary format where each word is stored in a newline inside a txt file.
    *
    * Postcondition:
    * The function does not return anything. This function does throw a DictionaryError("<filename> failed to open")
    * exception if filename fails to open or read. Otherwise, each word is added into the dictionary using AddWord().
    * Additionally, this function does not reset the words in the dictionary only adding to the current dictionary.
    */
    void LoadDictionaryFile(const string& filename);

    /*
    * Function:
    * This function traverses through the dictionary and saves all words into a file.
    *
    * Precondition:
    * A valid filename, including the path and file format suffix, must be passed. This is saved in ASCII txt format.
    *
    * Postcondition:
    * The function does not return anything. This function does throw a DictionaryError("<filename> failed to open")
    * exception if filename fails to open. Otherwise, SaveDictionaryHelper() is invoked until completion where the
    * filename is closed().
    */
    void SaveDictionaryFile(const string& filename);

    /*
    * Function:
    * Adds 'word' into the dictionary.
    *
    * Precondition:
    * A valid 'word' string is required.
    *
    * Postcondition:
    * The function does not return anything. This function does throw a DictionaryError("Invalid character")
    * exception if a character in the 'word' variable is not a valid [A-Z][a-z] character. Otherwise, each letter is
    * added onto the tree and numWords is increased.
    */
    void AddWord(const string& word);

    /*
    * Function:
    * Nulls/empties the current object effectively resetting it back to what the default constructor Dictionary() does.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function does not return anything. Also, this function does not throw exceptions. It invokes destroyHelper()
    * on this->root before creating a new Node on this->root and setting this->numWords back to 0.
    */
    void MakeEmpty();

    /*
    * Function:
    * Is 'word' a word? Let's check 'word' against this dictionary.
    *
    * Precondition:
    * A prefix/word in a string format is required to invoke this function.
    *
    * Postcondition:
    * The function returns a true or false boolean. The state of the boolean is determined by traversing through the
    * dictionary tree until reaching the last character of 'word' and reading its isWord boolean flag. This isWord
    * boolean gets returned. This function will throw DictionaryError("Invalid character") if it determines that a
    * character of 'word' is not valid.
    */
    bool IsWord(string word);

    /*
    * Function:
    * Is 'word' a prefix? Let's check 'word' against this dictionary.
    *
    * Precondition:
    * A prefix/word in a string format is required to invoke this function.
    *
    * Postcondition:
    * The function returns a true or false boolean. The state of the boolean is determined by traversing through the
    * dictionary tree until reaching the last character of 'word'. If each of the characters exist in the tree, then
    * IsPrefix returns true, otherwise it returns false. This function will throw DictionaryError("Invalid character")
    * if it determines that a character of 'word' is not valid.
    */
    bool IsPrefix(string word);

    /*
    * Function:
    * How many words do we have in the dictionary?
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function does not throw exceptions. It simply returns numWords.
    */
    int WordCount();

private:
    class Node {
    public:
        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
        char chr{};
        bool isWord = false;
        Node *ptrs[NUM_CHARS] = {};
    };

    Node* root;
    int numWords;

    /*
    * Function:
    * This private function is a wrapper to another private function CopyHelper().
    *
    * Precondition:
    * A Dictionary object must be passed as otherDict.
    *
    * Postcondition:
    * The function does not return anything. It also does not throw exceptions. This function assigns numWords to the
    * numWords of the otherDict before invoking the recursive function copyHelper().
    */
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.

    /*
    * Function:
    * This private recursive function deletes the entire tree holding the dictionary.
    *
    * Precondition:
    * A Dictionary object must be passed as otherDict. this->root should be passed when initially calling this function
    *
    * Postcondition:
    * The function does not return anything. Upon completion, the entire tree of words is deleted leaving this->root
    * pointing to a non-existent node.
    */
    void destroyHelper(Node* thisTree);

    /*
    * Function:
    * This private recursive function performs a deep copy of the entire tree onto otherTree.
    *
    * Precondition:
    * Two Dictionary objects must be passed as thisTree and otherTree.
    * this->root and otherTree.root should be passed when initially calling this function as thisTree and otherTree
    * respectively.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. Upon completion, the entire tree of words is
    * copied onto otherTree along with eac respective character (otherTree->chr) and isWord boolean flag
    * (otherTree->isWord).
    */
    void copyHelper(Node*& thisTree, Node* otherTree);

    /*
    * Function:
    * This private recursive function traverses through the dictionary tree and saves each word into the specified
    * output file stream.
    *
    * Precondition:
    * The current Node that is traveling along is required. The prefix that is checking also needs to be passed.
    * Finally, an output file stream is needed to direct the prefix/word.
    * this->root and "" should be passed when initially calling this function as curr and currPrefix respectively.
    * outFile should just be passed along.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. Upon completion, the entire tree of words is
    * directed to outFile, commonly cout or an ifstream, where each newline defines a word.
    */
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);

    /*
    * Function:
    * This private function converts a char data type into an integer.
    *
    * Precondition:
    * A lowercase or uppercase char is required.
    *
    * Postcondition:
    * The function returns an integer (should be between 0 - 25) that represents a numerical position in the English
    * alphabet.
    */
    int char2Int(char intg);

    /*
    * Function:
    * Is chr a valid char?
    *
    * Precondition:
    * A lowercase or uppercase char is required.
    *
    * Postcondition:
    * The function returns a boolean that is determined false by converting chr into an int and if that int is less
    * than 0.
    */
    bool isValidChar(char chr);
};

#endif //BOGGLE_DICTIONARY_H
