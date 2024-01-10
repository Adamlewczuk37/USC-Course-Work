// game.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;
  int targetWordLength;
  int lettersGuessed = 0;
  int temp;

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];

  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
                  // It should be initialized with *'s and then
                  //  change them to the actual letters when the 
                  //  user guesses the letter

    targetWordLength = strlen(targetWord);
    temp = targetWordLength;
    for(int i = 0; i < targetWordLength; i++){
        word[i] = '*';
    }
    cout << "Current word: ";
    for (int i = 0; i < temp; i++){
        cout << word[i];
    }
    cout << endl;
    cout << numTurns << " remain...Enter a letter to guess:" << endl;
    cin >> guess;
    while ((numTurns > 0) && (wordGuessed == false)){
        lettersGuessed = processGuess(word, targetWord, guess);
        if (lettersGuessed == 0){
            numTurns--;
            if (numTurns == 0){
                break;
            }
            cout << "Current word: ";
            for (int i = 0; i < temp; i++){
                cout << word[i];
            }
            cout << endl;
            cout << numTurns << " remain...Enter a letter to guess:" << endl;
            cin >> guess;
        } else {
            targetWordLength -= lettersGuessed;
            cout << "Current word: ";
            for (int i = 0; i < temp; i++){
                cout << word[i];
            }
            cout << endl;
            cout << numTurns << " remain...Enter a letter to guess:" << endl;
            cin >> guess;
        }
        if (targetWordLength == 0){
            wordGuessed = true;
        }
    }
    if (targetWordLength == 0){
        cout << "Too many turns...You lose!" << endl;
    } else {
        cout << "The word was: ";
        for (int i = 0; i < temp; i++){
            cout << word[i];
        }
        cout << ". You win!" << endl;
    }

  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess) {
    int accum = 0;
    for (int i = 0; i < strlen(targetWord); i++){
        if (*(targetWord + i) == guess){
            accum++;
            *(word + i) = guess;
        }
    }
    return accum;
}