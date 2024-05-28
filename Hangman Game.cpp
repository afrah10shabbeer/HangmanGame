// Hangman Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>  // for system()
using namespace std;

// Number of tries the user has
int tries = 3;
// Message to display to the user
string message = "You have 3 chances!";

// Function to display the hangman state
void hang_man(char state)
{
    string head_string = "| ";
    if (state == 'f')
        head_string = "  ";

    // ASCII art for the hangman
    cout << "\t\t\t\t__________________ " << endl;
    cout << "\t\t\t\t          " << head_string << "     |" << endl;
    cout << "\t\t\t\t          O      |" << endl;
    cout << "\t\t\t\t         / \\     |" << "\t       " << message << endl;
    cout << "\t\t\t\t          |      |" << "\t       /" << endl;
    cout << "\t\t\t\t         / \\     |             O  " << endl;
    cout << "\t\t\t\t     =========== |            / \\" << endl;
    cout << "\t\t\t\t     |         | |             |" << endl;
    cout << "\t\t\t\t     |         | |            / \\" << endl;
    cout << "\t\t\t\t =========================================" << endl;
}

// Function to check the guessed letter
int checkGuess(char letter_guessed, string real_month, string& hidden_month)
{
    int matches = 0;
    int len = real_month.length();

    // Loop through each character in the real month
    for (int i = 0; i < len; i++)
    {
        // If the letter is already guessed, return 0
        if (letter_guessed == hidden_month[i])
            return 0;
        // If the letter matches, reveal it in the hidden month
        if (letter_guessed == real_month[i])
        {
            hidden_month[i] = letter_guessed;
            matches++;
        }
    }
    return matches;
}

int main()
{
    char letter;  // Character guessed by the user
    string month;  // The month to be guessed

    // List of months
    vector<string> months = { "january", "february", "march", "april", "may",
                              "june", "july", "august", "september", "october",
                              "november", "december" };

    // Seed the random number generator and choose a random month
    srand(time(NULL));
    int month_number = rand() % 12;
    month = months[month_number];

    // Create a hidden version of the month with all letters replaced by 'X'
    string hide_month(month.length(), 'X');
    system("cls");  // Clear the console screen

    // Main game loop
    while (tries != 0)
    {
        hang_man('n');  // Display the hangman state
        cout << "\t\t\t\tLife: " << tries << endl;  // Show remaining tries
        cout << "\t\t\t\t" << hide_month << endl;  // Show hidden month
        cout << "\t\t\t\tGuess a letter: ";
        cin >> letter;  // Get the user's guess

        system("cls");  // Clear the console screen

        // Check if the guessed letter is in the month
        if (checkGuess(letter, month, hide_month) == 0)
        {
            message = "Incorrect Letter!";  // Update message for incorrect guess
            tries--;  // Decrement the number of tries
        }
        else
        {
            message = "Nice! Correct Guess";  // Update message for correct guess
        }

        // If the user has guessed the entire month
        if (hide_month == month)
        {
            message = "You're Free!";  // Update message for winning
            hang_man('f');  // Display the final hangman state
            cout << "\t\t\t\tLife: " << tries << endl;  // Show remaining tries
            cout << "\t\t\t\The month is: " << month << endl;  // Show the guessed month
            break;  // Exit the loop
        }
    }

    // If the user runs out of tries
    if (tries == 0)
    {
        message = "You're Hanged!";  // Update message for losing
        hang_man('h');  // Display the final hangman state
        cout << "\t\t\t\tLife: " << tries << endl;  // Show remaining tries
        cout << "\t\t\t\The month is: " << month << endl;  // Show the correct month
    }
}
