
#include "Dictionary.h"
#include "Boggle.h"

// Your code here


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}

Boggle::Boggle() {
    // Initialize each entry of board to the empty string
    ClearBoard();

    // Initialize each entry of visited to false/0
    ClearHistory();

    // The default constructor should initialize the dict with words from dictionary.txt
    this->dict = Dictionary("dictionary.txt");
}

Boggle::Boggle(const string& filename) {
    // Initialize each entry of board to the empty string
    ClearBoard();

    // Initialize each entry of visited to false/0
    ClearHistory();

    // The default constructor should initialize the dict with words from dictionary.txt
    this->dict = Dictionary(filename);

}

void Boggle::SetBoard(string brd[][BOARD_SIZE]) {
    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++)
            this->board[x][y] = brd[x][y];
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    // This function should reset the wordsFound dictionary each time it is run.
    this->wordsFound.MakeEmpty();

    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++){
            SolveBoardHelper(x, y, 0, "", printBoard, output);
        }

}

void Boggle::SaveSolve(const string& filename) {
    // The solution will start with the SolveBoard function.
    SolveBoard(false, cout);

    // This should use the SaveDictionaryFile for the wordsFound.
    this->wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {
    for (int x = 0; x < BOARD_SIZE; x++){
        for (int y = 0; y < BOARD_SIZE; y++){
            // Use the visited matrix to figure out when to print the quotes around the letter.
            if (this->visited[x][y] != 0){
                // Print a quote if the visited matrix is not 0 at a given position.
                output << " '" << this->board[x][y] << "' ";
            } else {
                output << "  " << this->board[x][y] << "  ";
            }
        }

        output << "\t";

        for (int y = 0; y < BOARD_SIZE; y++) {
            output << "  " << this->visited[x][y] << "  ";
        }

        output << endl;
    }

    output << endl;
}

void Boggle::SolveBoardHelper(int row, int col, int steps, string prefix, bool printBoard, ostream &output) {
    if (row >= BOARD_SIZE || col >= BOARD_SIZE || row < 0 || col < 0 || this->visited[row][col] != 0)
        return;

    // Be sure to make use of the isPrefix method to prevent exploration of paths that will not produce words.
    if (!this->dict.IsPrefix(prefix))
        return;

    AssistantToTheSolveBoardHelper(printBoard, output, prefix);

    // Grab the next letter on the board and concat it onto the prefix.
    prefix.append(this->board[row][col]);
    // Bookkeeping
    this->visited[row][col] = ++steps;

    // Check to see if the appended letter from the board is a valid word. Without checking, a valid word would escape
    // at the first base case when traveling.
    AssistantToTheSolveBoardHelper(printBoard, output, prefix);

    // The job of SolveBoardHelper is to recursively check the surrounding 8 positions.

    // North
    SolveBoardHelper(row - 1, col, steps, prefix, printBoard, output);
    // Northeast
    SolveBoardHelper(row - 1, col + 1, steps, prefix, printBoard, output);
    // East
    SolveBoardHelper(row, col + 1, steps, prefix, printBoard, output);
    // Southeast
    SolveBoardHelper(row + 1, col + 1, steps, prefix, printBoard, output);
    // South
    SolveBoardHelper(row + 1, col, steps, prefix, printBoard, output);
    // Southwest
    SolveBoardHelper(row + 1, col - 1, steps, prefix, printBoard, output);
    // West
    SolveBoardHelper(row, col - 1, steps, prefix, printBoard, output);
    // Northwest
    SolveBoardHelper(row - 1, col - 1, steps, prefix, printBoard, output);

    this->visited[row][col] = 0;
}

void Boggle::ClearHistory() {
    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++)
            this->visited[x][y] = 0;
}

void Boggle::ClearBoard() {
    for (int x = 0; x < BOARD_SIZE; x++)
        for (int y = 0; y < BOARD_SIZE; y++){
            this->board[x][y] = "";
        }
}

void Boggle::AssistantToTheSolveBoardHelper(bool printBoard, ostream &output, string prefix) {
    if (this->dict.IsWord(prefix)){
        // Check if it's already in the wordsFound dictionary. If so, don't add it.
        if(!this->wordsFound.IsWord(prefix)){
            this->wordsFound.AddWord(prefix);
            if (!printBoard){
                output << this->wordsFound.WordCount() << "\t" << prefix << endl;
            }

            if (printBoard){
                output << "Word: " << prefix << endl;
                output << "Number of Words: " << this->wordsFound.WordCount() << endl;
                PrintBoard(output);
            }
        }
    }
}



