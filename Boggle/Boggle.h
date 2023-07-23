#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    /*
    * Function:
    * The default constructor that creates a basic Boggle object.
    *
    * Precondition:
    * No preconditions needed to invoke this default constructor.
    *
    * Postcondition:
    * The function does not return anything. It initializes Dictionary dict from words stored in dictionary.txt.
    * It then initializes each entry of board[][] to the empty string. It also initializes each entry of visited[][] to
    * 0.
    */
    Boggle();  // load "dictionary.txt" into dict

    /*
    * Function:
    * The second explicit constructor that creates a basic Boggle object and loads a custom dictionary using an absolute
    * filename.
    *
    * Precondition:
    * This constructor requires that variable passed through filename be a valid dictionary file.
    *
    * Postcondition:
    * This constructor initializes Dictionary dict from words stored in the dictionary file passed as filename.
    * It then initializes each entry of board[][] to the empty string. It also initializes each entry of visited[][] to
    * 0.
    */
    explicit Boggle(const string& filename);  // load filename into dict

    /*
    * Function:
    * This function copies each entry of the board passed onto the this->board[][] within the object.
    *
    * Precondition:
    * The board passed must be BOARD_SIZE x BOARD_SIZE and no size smaller or bigger.
    *
    * Postcondition:
    * This function does not return anything nor does it throw exceptions. The board pass must be sanitized.
    * Upon successful execution, the board passed will be copied to the local object this->board[][].
    */
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);

    /*
    * Function:
    * This finds all the words on the current board (this->board) and saves them into the Dictionary this->wordsFound.
    *
    * Precondition:
    * A boolean for printBoard and a valid ostream (cout/ofstream) must be passed.
    *
    * Postcondition:
    * This function does not return anything nor does it throw exceptions. This function invokes MakeEmpty() from the
    * Dictionary class which clears the wordsFound dictionary. Upon successful execution of this function, all words
    * found will be stored into the wordsFound dictionary. It will also output to the specified ostream, that is whether
    * is output references cout or a file stream (ofstream). If printBoard is true, it will also invoke PrintBoard() to
    * neatly display the board and a step map.
    */
    void SolveBoard(bool printBoard, ostream& output);


    /*
    * Function:
    * This is a wrapper to SolveBoard(). The difference is that it invokes SaveDictionaryFile() from the Dictionary
    * class to save dict Dictionary into a valid file format.
    *
    * Precondition:
    * An absolute path to an accessible directory including the filename is to be passed as filename.
    *
    * Postcondition:
    * This function does not return anything nor does it throw exceptions. This function invokes MakeEmpty() from the
    * Dictionary class which clears the wordsFound dictionary. Upon successful execution of this function, all words
    * found will be stored into the wordsFound dictionary. It will also output to the specified ostream, that is whether
    * is output references cout or a file stream (ofstream). If printBoard is true, it will also invoke PrintBoard() to
    * neatly display the board and a step map.
    */
    void SaveSolve(const string& filename);   // Saves all the words from the last solve.

    /*
    * Function:
    * Get the dictionary.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * This is function returns the current dictionary (this->dict). Also, this function does not throw exceptions.
    */
    Dictionary GetDictionary();

    /*
    * Function:
    * Get the words found.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * This is function returns the wordsFound dictionary (this->wordsFound). Also, this function does not throw
    * exceptions.
    */
    Dictionary WordsFound();

    // Custom functions

    /*
    * Function:
    * Clear the visit history.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * This is function does not return anything. Also, this function does not throw exceptions. Upon completion, this
    * function rewrites all visited[][] values back to 0.
    */
    void ClearHistory();

    /*
    * Function:
    * Clear the board.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * This is function does not return anything. Also, this function does not throw exceptions. Upon completion, this
    * function rewrites all board[][] entries to an empty "" string.
    */
    void ClearBoard();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    /*
    * Function:
    * This function prints the boggle board and a map that led to the discovery
    *
    * Precondition:
    * output must be a valid ostream. This can be cout or a ofstream object.
    *
    * Postcondition:
    * This function does not return anything nor does it throw exceptions. This function will print out a nicely
    * formatted table showing the boggle board. It will also display the visited board with each step that
    * SolveBoardHelper() used to find the word.
    */
    void PrintBoard(ostream& output);

    /*
    * Function:
    * This function does the heavy lifting of finding all possible words given a board and a dictionary.
    *
    * Precondition:
    * A valid dictionary must be loaded into dict along with a board filled with a-z letters. This function requires a
    * minimum initial call so that x and y are controlled by two for-loops. The steps variable should be 0 when
    * initially called by the double for-loops. The prefix variable should also be set to "" when initially passed by
    * the double for-loops. Finally, printBoard, output should be passed.
    *
    * Postcondition:
    * This function does not return anything nor does it throw exceptions. This function will find all words and store
    * them into the wordsFound dictionary. It will also keep track of each step it took to find each word using the
    * visited[][] board.
    */
    void SolveBoardHelper(int row, int col, int steps, string prefix, bool printBoard, ostream &output);

    // Custom functions

    /*
    * Function:
    * This is the equivalent of the Assistant To The Regional Manager title. This function aids SolveBoardHelper() in
    * completing a repetitive task of checking both dictionaries (dict & wordsFound).
    *
    * Precondition:
    * All three arguments (printBoard, output, prefix) are needed.
    *
    * Postcondition:
    * This function does not return anything nor does it throw exceptions. This function will add prefix into the
    * wordsFound dictionary if it deems that prefix is a valid word in the dict dictionary but does not already exist
    * in the wordsFound dictionary.
    */
    void AssistantToTheSolveBoardHelper(bool printBoard, ostream &output, string prefix);
};

#endif //BOGGLE_BOGGLE_H
