/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA 2
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
    int j;
    int temp;
    for (int i = 51; i > 0; i--){
          j = rand();
          j %= (i + 1);
          temp = cards[i];
          cards[i] = cards[j];
          cards[j] = temp;
    }
    cout << endl;
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  int num;
  num = (id % 13) + 2;
  if (num < 11){
      cout << num;
  } else if (num == 11){
      cout << 'J';
  } else if (num == 12){
      cout << 'Q';
  } else if (num == 13){
      cout << 'K';
  } else {
      cout << 'A';
  }
  cout << '-';
  if (id < 13){
      cout << 'H';
  } else if (id < 26){
      cout << 'S';
  } else if (id < 39){
      cout << 'D';
  } else {
      cout << 'C';
  }
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  int value;
  value = (id % 13) + 2;
  if ((value >= 11) && (value <= 13)){
      value = 10;
  } else if (value == 14){
        value = 11;
  }
  return value;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    for (int i = 0; i < numCards; i++){
        printCard(hand[i]);
        cout << ' ';
    }
    cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
    int accum = 0;
    int ace = 0;
    for (int i = 0; i < numCards; i++){
        accum += cardValue(hand[i]);
    }
    for (int i = 0; i < numCards; i++){
      if (cardValue(hand[i]) == 11){
        ace = 1;
      }
    }
    if ((ace == 1) && (accum > 21)){
        accum -= 10;
    }
    return accum;
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------
   char ynInput;
   char sInput;
   int cardNum;
   int deNum;
   int plyNum;
   int scorePly;
   int scoreDe = 0;
   
    for (int i = 0; i < 52; i++){
      cards[i] = i;
    }

    do {
        cardNum = 0;
        deNum = 0;
        plyNum = 0;
        scorePly = 0;
        scoreDe = 0;
        
        for (int i = 0; i < 52; i++){
          cards[i] = i;
        }
        shuffle(cards);
        cout << endl;
        phand[plyNum] = cards[cardNum];
        plyNum++;
        cardNum++;
        dhand[deNum] = cards[cardNum];
        deNum++;
        cardNum++;
        phand[plyNum] = cards[cardNum];
        plyNum++;
        cardNum++;
        dhand[deNum] = cards[cardNum];
        deNum++;
        cardNum++;
        cout << "Dealer: ? ";
        printCard(dhand[deNum - 1]);
        cout << endl;
        cout << "Player: ";
        printHand(phand, plyNum);
        
        scorePly = getBestScore(phand, plyNum);
        if (scorePly < 21){
          cout << "Type 'h' to hit and 's' to stay:" << endl;
          cin >> sInput;
        }

        while ((sInput == 'h') && (scorePly < 21)){
          phand[plyNum] = cards[cardNum];
          cout << "Player: ";
          printHand(phand, plyNum + 1);
          plyNum++;
          cardNum++;
          scorePly = getBestScore(phand, plyNum);
          if (scorePly >= 21){
            break;
          }
          cout << "Type 'h' to hit and 's' to stay:" << endl;
          cin >> sInput;
        }

        scoreDe = getBestScore(dhand, deNum);
        if (scorePly > 21){
            cout << "Player busts" << endl;
            cout << "Lose " << scorePly << " " << scoreDe << endl;
        } else {
            while (scoreDe < 17){
                dhand[deNum] = cards[cardNum];
                deNum++;
                cardNum++;
                scoreDe = getBestScore(dhand, deNum);
            }
            cout << "Dealer: ";
            printHand(dhand, deNum);
            if (scoreDe > 21){
                cout << "Dealer busts" << endl;
                cout << "Win " << scorePly << " " << scoreDe << endl;
            } else if (scorePly > scoreDe){
                cout << "Win " << scorePly << " " << scoreDe << endl;
            } else if (scorePly < scoreDe){
                cout << "Lose " << scorePly << " " << scoreDe << endl;
            } else {
                cout << "Tie " << scorePly << " " << scoreDe << endl;
            }
        }
        cout << endl;
        cout << "Play again? [y/n]" << endl;
        cin >> ynInput;
  
    } while (ynInput == 'y');

  return 0;
}