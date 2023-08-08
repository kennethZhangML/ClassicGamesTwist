#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ctime>

using namespace std;

void displayGameDetails(int maxTries);
string chooseSecretWord();
string initializeGuessWord(int length);
void displayWord(const string& word);
bool updateGuessedWord(string& guessWord, const string& secretWord, char letter);
void displayMan(int wrongAttempts);

unordered_set<string> playedWords;

unordered_map<int, vector<string>> wordsByLength;

void displayGameDetails(int maxTries) {
    cout << "\n"
        "        .-------------------------------------------------------------------------------.\n"
        "        |      _      _                                                                  |\n"
        "        |     | |    | |   __ _    _ __      __ _        /\\/\\      __ _    _ __          |\n"
        "        |     | |----| |  / _  |  |  _ \\    / _` |      /    \\    / _  |  |  _  \\        |\n"
        "        |     | |----| | | (_| |  | | | |  | (_| |     / /\\/\\ |  | (_| |  | | | |        |\n"
        "        |     |_|    |_|  \\_ _ |  |_| |_|   \\__, |     \\/    \\/   \\_ _ |  |_| |_|        |\n"
        "        |                                    |___/                                       |\n"
        "        .--------------------------------------------------------------------------------.\n";

    cout << "Welcome to the Hangman game!\n";
    cout << "Guess an animal name, chosen by the application\n";
    cout << "You can have " << maxTries << " wrong attempts\n";
    cout << "Let's play the game!\n\n";
}

string chooseSecretWord() {
    srand(time(NULL));

    vector<int> lengths;
    for (const auto& pair : wordsByLength) {
        lengths.push_back(pair.first);
    }

    int randomLengthIndex = rand() % lengths.size();
    int chosenLength = lengths[randomLengthIndex];

    const vector<string>& possibleWords = wordsByLength[chosenLength];
    int randomWordIndex = rand() % possibleWords.size();
    string chosenWord = possibleWords[randomWordIndex];

    while (playedWords.find(chosenWord) != playedWords.end()) {
        randomWordIndex = rand() % possibleWords.size();
        chosenWord = possibleWords[randomWordIndex];
    }

    playedWords.insert(chosenWord);
    return chosenWord;
}


string initializeGuessWord(int length) {
    return string(length, '-');
}

void displayWord(const string& word) {
    cout << word << endl;
}

bool updateGuessedWord(string& guessWord, const string& secretWord, char letter) {
    bool letterFound = false;
    for (size_t i = 0; i < secretWord.length(); i++) {
        if (secretWord[i] == letter) {
            if (guessWord[i] == letter) {
                cout << "\nYou have already guessed this letter. Try something else!" << endl;
                return true;  
            }
            else {
                guessWord[i] = letter;
                letterFound = true;
            }
        }
    }

    if (letterFound) {
        cout << "\nYay! You have found the letter" << endl;
    }
    else {
        cout << "\nWhoops! that letter is not present in the word" << endl;
    }

    return letterFound;
}

void displayMan(int wrongAttempts) {
    string man[] = {
        "  |       \n",
        "  |       O\n",
        "  |      /|\\\n",
        "  |      / \\\n"
    };

    cout << "--------------\n";
    for (int i = 0; i < wrongAttempts; ++i) {
        cout << man[i];
    }
    for (int i = wrongAttempts; i < 4; ++i) {
        cout << "  |\n";
    }
    cout << "--------------\n";
}


void startGame() {
    const int maxTries = 5;
    int remainingTries = maxTries;

    displayGameDetails(maxTries);

    string secretWord = chooseSecretWord();
    string guessWord = initializeGuessWord(secretWord.length());
    displayWord(guessWord);

    while (remainingTries > 0) {
        cout << "Enter your guess letter:" << endl;
        char guessLetter;
        cin >> guessLetter;

        if (!updateGuessedWord(guessWord, secretWord, guessLetter)) {
            remainingTries--;
            displayMan(maxTries - remainingTries);
        }

        cout << "You have " << remainingTries << " wrong attempts remaining" << endl;
        displayWord(guessWord);
        cout << endl;

        if (secretWord == guessWord) {
            cout << "\nCongratulations! You won." << endl;
            return;
        }
    }

    cout << "\nToo many Guesses! You have been hanged." << endl;
    cout << "\nThe secret word was: " << secretWord << endl;
}

int main() {
    vector<string> animals = { "puppy", "turtle", "rabbit", "raccoon", "kitten",
                              "hamster", "sheep", "turkey", "chicken", "horse",
                              "chimpanzee", "kangaroo", "koala", "elephant",
                              "leopard", "hippopotamus", "giraffe", "crocodile",
                              "alligator", "hedgehog" };

    for (const string& animal : animals) {
        wordsByLength[animal.length()].push_back(animal);
    }

    while (true) {
        cout << "\n---------------------------------\n";
        cout << "Hangman Game Menu\n";
        cout << "1. Start Game\n";
        cout << "2. Exit\n";
        cout << "Enter your choice (1/2): ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            startGame();
            break;
        case 2:
            cout << "Thanks for playing. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please select 1 or 2.\n";
        }
    }

    return 0;
}
