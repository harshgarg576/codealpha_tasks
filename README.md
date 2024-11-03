CodeAlpha C++ Intern Tasks

This repository contains a collection of tasks completed as part of the internship program at CodeAlpha. Each task showcases different C++ programming concepts and problem-solving techniques.

Table of Contents
- [Task 1: Number Guessing Game](#task-1-number-guessing-game)
- [Task 2: Simple Command-Line File Manager](#task-2-simple-command-line-file-manager)
- [Task 3: Sudoku Solver](#task-3-sudoku-solver)
- [Task 4: Simple Chatbot](#task-4-simple-chatbot)
- [How to Run](#how-to-run)
- [More Information](#more-information)

Task 1: Number Guessing Game

A simple console-based game where the user tries to guess a randomly generated number between 1 and 100.

Features
- Random number generation
- User input for guesses
- Feedback on guesses (too high, too low, or correct)

Code
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() 
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Generate a random number between 1 and 100
    int targetNumber = rand() % 100 + 1;
    int guess = 0;
    int attempts = 0;

    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I have selected a number between 1 and 100." << endl;
    cout << "Try to guess it!" << endl;

    // Game loop
    while (guess != targetNumber) {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess < targetNumber) {
            cout << "Too low! Try again." << endl;
        } else if (guess > targetNumber) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << "Congratulations! You've guessed the number " << targetNumber << " in " << attempts << " attempts!" << endl;
        }
    }

    return 0;
}


More Information
[LinkedIn Post](https://www.linkedin.com/posts/harsh-garg-792780305_cplusplus-coding-internship-activity-7258573527316942849-nTP4?utm_source=share&utm_medium=member_desktop)


Task 2: Simple Command-Line File Manager

A command-line tool that allows users to perform basic file operations such as listing files, creating directories, copying, moving files, and changing directories.

Features
- List files and directories
- Create new directories
- Copy and move files
- Change current working directory

Code
#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>

using namespace std;
namespace fs = filesystem;

void listFiles(const fs::path& path) {
    cout << "Listing files in: " << path << "\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename() << "\n";
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        cout << "Directory created: " << path << "\n";
    } else {
        cout << "Failed to create directory or already exists: " << path << "\n";
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    try {
        if (!fs::exists(source)) {
            cout << "Source file does not exist: " << source << "\n";
            return;
        }
        fs::copy(source, destination);
        cout << "File copied from " << source << " to " << destination << "\n";
    } catch (const fs::filesystem_error& e) {
        cout << "Error copying file: " << e.what() << "\n";
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    try {
        if (!fs::exists(source)) {
            cout << "Source file does not exist: " << source << "\n";
            return;
        }
        fs::rename(source, destination);
        cout << "File moved from " << source << " to " << destination << "\n";
    } catch (const fs::filesystem_error& e) {
        cout << "Error moving file: " << e.what() << "\n";
    }
}

void changeDirectory(fs::path& currentPath, const fs::path& newPath) {
    fs::path targetPath = currentPath / newPath;
    if (fs::exists(targetPath) && fs::is_directory(targetPath)) {
        currentPath = fs::absolute(targetPath);
        cout << "Changed directory to: " << currentPath << "\n";
    } else {
        cout << "Directory does not exist: " << targetPath << "\n";
    }
}

void showHelp() {
    cout << "Available commands:\n";
    cout << "  ls                   : List files in the current directory.\n";
    cout << "  mkdir <name>        : Create a new directory with the specified name.\n";
    cout << "  cp <source> <destination> : Copy a file from source to destination.\n";
    cout << "  mv <source> <destination> : Move a file from source to destination.\n";
    cout << "  cd <directory>      : Change the current directory to the specified directory.\n";
    cout << "  exit                : Exit the program.\n";
}

int main() {
    string command;
    fs::path currentPath = fs::current_path();

    while (true) {
        cout << "\nCurrent directory: " << currentPath << "\n";
        cout << "Enter command (type 'help' for assistance): ";
        getline(cin, command);

        if (command == "exit") {
            break;
        } else if (command == "ls") {
            listFiles(currentPath);
        } else if (command == "help") {
            showHelp();
        } else if (command.substr(0, 6) == "mkdir ") {
            createDirectory(currentPath / command.substr(6));
        } else if (command.substr(0, 3) == "cp ") {
            istringstream iss(command.substr(3));
            string source, destination;
            iss >> source >> destination;
            if (iss && !destination.empty()) {
                copyFile(currentPath / source, currentPath / destination);
            } else {
                cout << "Usage: cp <source> <destination>\n";
            }
        } else if (command.substr(0, 3) == "mv ") {
            istringstream iss(command.substr(3));
            string source, destination;
            iss >> source >> destination;
            if (iss && !destination.empty()) {
                moveFile(currentPath / source, currentPath / destination);
            } else {
                cout << "Usage: mv <source> <destination>\n";
            }
        } else if (command.substr(0, 3) == "cd ") {
            changeDirectory(currentPath, command.substr(3));
        } else {
            cout << "Unknown command. Type 'help' for assistance.\n";
        }
    }
    return 0;
}


More Information
[LinkedIn Post](https://www.linkedin.com/posts/harsh-garg-792780305_cplusplus-filemanager-internship-activity-7258574777148227584-yLym?utm_source=share&utm_medium=member_desktop)


Task 3: Sudoku Solver

A program that solves a given Sudoku puzzle using backtracking. The program checks the validity of placements and recursively attempts to fill the board.

Features
- Displays the solved Sudoku board
- Handles invalid puzzles

Code
#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 9;

// Function to print the Sudoku board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Function to check if placing a number is valid
bool isValid(const vector<vector<int>>& board, int row, int col, int num) {
    for (int x = 0; x < SIZE; x++) {
        if (board[row][x] == num || board[x][col] == num || 
            board[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

// Backtracking function to solve the Sudoku
bool solveSudoku(vector<vector<int>>& board) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(board, row, col, num)) {
                        board[row][col] = num;

                        if (solveSudoku(board)) {
                            return true;
                        }

                        board[row][col] = 0; // Backtrack
                    }
                }
                return false; // No valid number found
            }
        }
    }
    return true; // Solved
}

int main() {
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board)) {
        printBoard(board);
    } else {
        cout << "No solution exists." << endl;
    }

    return 0;
}


More Information
[LinkedIn Post](https://www.linkedin.com/posts/harsh-garg-792780305_cplusplus-sudokusolver-internship-activity-7258574524495933440-m4vO?utm_source=share&utm_medium=member_desktop)



Task 4: Simple Chatbot

A basic chatbot that responds to user input with predefined responses. The chatbot can handle greetings, farewells, and a few common questions.

Features
- Responds to specific keywords
- Simple conversation loop

Code
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Chatbot {
private:
    map<string, string> responses;

public:
    Chatbot() {
        // Simple responses
        responses["hi"] = "Hello! How can I help you today?";
        responses["how are you"] = "I'm just a program, but thanks for asking!";
        responses["bye"] = "Goodbye! Have a great day!";
    }

    string getResponse(const string& input) {
        string lowerInput = input;
        transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);
        if (responses.find(lowerInput) != responses.end()) {
            return responses[lowerInput];
        }
        return "I'm sorry, I don't understand that.";
    }
};

int main() {
    Chatbot bot;
    string userInput;

    cout << "Chatbot: Hi! I'm here to assist you. Type 'bye' to exit." << endl;

    while (true) {
        cout << "You: ";
        getline(cin, userInput);
        if (userInput == "bye") {
            cout << "Chatbot: Goodbye!" << endl;
            break;
        }
        cout << "Chatbot: " << bot.getResponse(userInput) << endl;
    }

    return 0;
}


More Information
[LinkedIn Post](https://www.linkedin.com/posts/harsh-garg-792780305_cplusplus-aichatbot-internship-activity-7258574393054842881-Y-YZ?utm_source=share&utm_medium=member_desktop)



How to Run

1. Clone the repository:
   git clone https://github.com/harshgarg576/codealpha_tasks.git
   cd codealpha_tasks

2. Compile the C++ files using a C++ compiler, for example, g++:
   g++ -o guessing_game task1.cpp
   ./guessing_game
   (Replace `task1.cpp` with the appropriate file name for the other tasks.)

3. Follow the on-screen instructions for each program.


More Information

For further details and explanations of the code, you can check out my [LinkedIn Profile](https://www.linkedin.com/in/harsh-garg-792780305/).


Feel free to fill in the code sections and make any other adjustments you’d like! If you need more help, just let me know!
