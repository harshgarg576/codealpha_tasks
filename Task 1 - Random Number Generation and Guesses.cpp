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
