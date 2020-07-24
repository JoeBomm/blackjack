#if defined(__unix__) || defined(__unix)
#   define DECK_OS_LINUX
#elif defined (_WIN32) || defined (_WIN64)
#   define DECK_OS_WINDOWS
#else
#   error unspported platform
#endif

#include <random>
#include <iostream>
#include "Deck.h"

using namespace std;

Deck::Deck()
{
  string ten;

  #if defined(DECK_OS_LINUX)
        ten = "\u2491";
  #else
        ten = "10";
  #endif

  index = 0;
  maxCards = 52;
  cards = new Card[maxCards];

  cards[0]  = Card("A", 1, Suit::Spades);
  cards[1]  = Card("2",  2, Suit::Spades);
  cards[2]  = Card("3",  3, Suit::Spades);
  cards[3]  = Card("4",  4, Suit::Spades);
  cards[4]  = Card("5",  5, Suit::Spades);
  cards[5]  = Card("6",  6, Suit::Spades);
  cards[6]  = Card("7",  7, Suit::Spades);
  cards[7]  = Card("8",  8, Suit::Spades);
  cards[8]  = Card("9",  9, Suit::Spades);
  cards[9]  = Card(ten,10, Suit::Spades);
  cards[10] = Card("J", 10, Suit::Spades);
  cards[11] = Card("Q", 10, Suit::Spades);
  cards[12] = Card("K", 10, Suit::Spades);

  cards[13] = Card("A", 1, Suit::Clubs);
  cards[14] = Card("2",  2, Suit::Clubs);
  cards[15] = Card("3",  3, Suit::Clubs);
  cards[16] = Card("4",  4, Suit::Clubs);
  cards[17] = Card("5",  5, Suit::Clubs);
  cards[18] = Card("6",  6, Suit::Clubs);
  cards[19] = Card("7",  7, Suit::Clubs);
  cards[20] = Card("8",  8, Suit::Clubs);
  cards[21] = Card("9",  9, Suit::Clubs);
  cards[22] = Card(ten,10, Suit::Clubs);
  cards[23] = Card("J", 10, Suit::Clubs);
  cards[24] = Card("Q", 10, Suit::Clubs);
  cards[25] = Card("K", 10, Suit::Clubs);

  cards[26] = Card("A", 1, Suit::Diamonds);
  cards[27] = Card("2",  2, Suit::Diamonds);
  cards[28] = Card("3",  3, Suit::Diamonds);
  cards[29] = Card("4",  4, Suit::Diamonds);
  cards[30] = Card("5",  5, Suit::Diamonds);
  cards[31] = Card("6",  6, Suit::Diamonds);
  cards[32] = Card("7",  7, Suit::Diamonds);
  cards[33] = Card("8",  8, Suit::Diamonds);
  cards[34] = Card("9",  9, Suit::Diamonds);
  cards[35] = Card(ten,10, Suit::Diamonds);
  cards[36] = Card("J", 10, Suit::Diamonds);
  cards[37] = Card("Q", 10, Suit::Diamonds);
  cards[38] = Card("K", 10, Suit::Diamonds);

  cards[39] = Card("A", 1, Suit::Hearts);
  cards[40] = Card("2",  2, Suit::Hearts);
  cards[41] = Card("3",  3, Suit::Hearts);
  cards[42] = Card("4",  4, Suit::Hearts);
  cards[43] = Card("5",  5, Suit::Hearts);
  cards[44] = Card("6",  6, Suit::Hearts);
  cards[45] = Card("7",  7, Suit::Hearts);
  cards[46] = Card("8",  8, Suit::Hearts);
  cards[47] = Card("9",  9, Suit::Hearts);
  cards[48] = Card(ten,10, Suit::Hearts);
  cards[49] = Card("J", 10, Suit::Hearts);
  cards[50] = Card("Q", 10, Suit::Hearts);
  cards[51] = Card("K", 10, Suit::Hearts);


}

Deck::Deck(int decks)
{
  string ten;

  #if defined(DECK_OS_LINUX)
        ten = "\u2491";
  #else
        ten = "10";
  #endif

  index = 0;
  maxCards = 52*decks;
  cards = new Card[maxCards];

  for(int i=0; i<decks; i++)
  {
      cards[0+(52*i)]  = Card("A", 1, Suit::Spades);
      cards[1+(52*i)]  = Card("2",  2, Suit::Spades);
      cards[2+(52*i)]  = Card("3",  3, Suit::Spades);
      cards[3+(52*i)]  = Card("4",  4, Suit::Spades);
      cards[4+(52*i)]  = Card("5",  5, Suit::Spades);
      cards[5+(52*i)]  = Card("6",  6, Suit::Spades);
      cards[6+(52*i)]  = Card("7",  7, Suit::Spades);
      cards[7+(52*i)]  = Card("8",  8, Suit::Spades);
      cards[8+(52*i)]  = Card("9",  9, Suit::Spades);
      cards[9+(52*i)]  = Card(ten,10, Suit::Spades);
      cards[10+(52*i)] = Card("J", 10, Suit::Spades);
      cards[11+(52*i)] = Card("Q", 10, Suit::Spades);
      cards[12+(52*i)] = Card("K", 10, Suit::Spades);

      cards[13+(52*i)] = Card("A", 1, Suit::Clubs);
      cards[14+(52*i)] = Card("2",  2, Suit::Clubs);
      cards[15+(52*i)] = Card("3",  3, Suit::Clubs);
      cards[16+(52*i)] = Card("4",  4, Suit::Clubs);
      cards[17+(52*i)] = Card("5",  5, Suit::Clubs);
      cards[18+(52*i)] = Card("6",  6, Suit::Clubs);
      cards[19+(52*i)] = Card("7",  7, Suit::Clubs);
      cards[20+(52*i)] = Card("8",  8, Suit::Clubs);
      cards[21+(52*i)] = Card("9",  9, Suit::Clubs);
      cards[22+(52*i)] = Card(ten,10, Suit::Clubs);
      cards[23+(52*i)] = Card("J", 10, Suit::Clubs);
      cards[24+(52*i)] = Card("Q", 10, Suit::Clubs);
      cards[25+(52*i)] = Card("K", 10, Suit::Clubs);

      cards[26+(52*i)] = Card("A", 1, Suit::Diamonds);
      cards[27+(52*i)] = Card("2",  2, Suit::Diamonds);
      cards[28+(52*i)] = Card("3",  3, Suit::Diamonds);
      cards[29+(52*i)] = Card("4",  4, Suit::Diamonds);
      cards[30+(52*i)] = Card("5",  5, Suit::Diamonds);
      cards[31+(52*i)] = Card("6",  6, Suit::Diamonds);
      cards[32+(52*i)] = Card("7",  7, Suit::Diamonds);
      cards[33+(52*i)] = Card("8",  8, Suit::Diamonds);
      cards[34+(52*i)] = Card("9",  9, Suit::Diamonds);
      cards[35+(52*i)] = Card(ten,10, Suit::Diamonds);
      cards[36+(52*i)] = Card("J", 10, Suit::Diamonds);
      cards[37+(52*i)] = Card("Q", 10, Suit::Diamonds);
      cards[38+(52*i)] = Card("K", 10, Suit::Diamonds);

      cards[39+(52*i)] = Card("A", 1, Suit::Hearts);
      cards[40+(52*i)] = Card("2",  2, Suit::Hearts);
      cards[41+(52*i)] = Card("3",  3, Suit::Hearts);
      cards[42+(52*i)] = Card("4",  4, Suit::Hearts);
      cards[43+(52*i)] = Card("5",  5, Suit::Hearts);
      cards[44+(52*i)] = Card("6",  6, Suit::Hearts);
      cards[45+(52*i)] = Card("7",  7, Suit::Hearts);
      cards[46+(52*i)] = Card("8",  8, Suit::Hearts);
      cards[47+(52*i)] = Card("9",  9, Suit::Hearts);
      cards[48+(52*i)] = Card(ten,10, Suit::Hearts);
      cards[49+(52*i)] = Card("J", 10, Suit::Hearts);
      cards[50+(52*i)] = Card("Q", 10, Suit::Hearts);
      cards[51+(52*i)] = Card("K", 10, Suit::Hearts);
  }


}

Deck::~Deck()
{
  delete [] cards;
}

void Deck::shuffle()
{
    random_device rdevice{};
    default_random_engine num{ rdevice() };
    uniform_int_distribution<int> randomNum{0, maxCards-1};

    int swap;
    Card temp;

    for(int i=0; i<maxCards*3; i++)
    {
        swap = randomNum(num);
        temp = cards[0];
        cards[0] = cards[swap];
        cards[swap] = temp;
    }
    index = 0;
}

void Deck::print()
{
    for(int i=index; i<maxCards; i++)
    {
        cards[i].print();
        cout << ' ';
    }
    cout << '\n';
}

Card Deck::draw()
{
    if(index>=maxCards)
        shuffle();

    return cards[index++];
}

void Deck::incrementIndex()
{
    index++;
}

int Deck::getIndex()
{
    return index;
}

int Deck::getRemainingCards()
{
    return maxCards-index+1;
}




// void Deck::pop(int index)
// {
//     Card nullCard = Card();
//     cards[index] = nullCard;
// }
//
// Card Deck::getCard(int index)
// {
//     return cards[index];
// }



// cards[0]  = /*aceSpades   =*/ Card("A",  11, Suit::Spades);
// cards[1]  = /*twoSpades   =*/ Card("2",   2, Suit::Spades);
// cards[2]  = /*threeSpades =*/ Card("3", 3, Suit::Spades);
// cards[3]  = /*fourSpades  =*/ Card("4",  4, Suit::Spades);
// cards[4]  = /*fiveSpades  =*/ Card("5",  5, Suit::Spades);
// cards[5]  = /*sixSpades   =*/ Card("6",   6, Suit::Spades);
// cards[6]  = /*sevenSpades =*/ Card("7", 7, Suit::Spades);
// cards[7]  = /*eightSpades =*/ Card("8", 8, Suit::Spades);
// cards[8]  = /*nineSpades  =*/ Card("9",  9, Suit::Spades);
// cards[9]  = /*tenSpades   =*/ Card("10",  10, Suit::Spades);
// cards[10] = /*jackSpades  =*/ Card("J", 10, Suit::Spades);
// cards[11] = /*queenSpades =*/ Card("Q",10, Suit::Spades);
// cards[12] = /*kingSpades  =*/ Card("K", 10, Suit::Spades);
//
// cards[13] = /*aceClubs   =*/ Card("A",  11, Suit::Clubs);
// cards[14] = /*twoClubs   =*/ Card("2",   2, Suit::Clubs);
// cards[15] = /*threeClubs =*/ Card("3", 3, Suit::Clubs);
// cards[16] = /*fourClubs  =*/ Card("4",  4, Suit::Clubs);
// cards[17] = /*fiveClubs  =*/ Card("5",  5, Suit::Clubs);
// cards[18] = /*sixClubs   =*/ Card("6",   6, Suit::Clubs);
// cards[19] = /*sevenClubs =*/ Card("7", 7, Suit::Clubs);
// cards[20] = /*eightClubs =*/ Card("8", 8, Suit::Clubs);
// cards[21] = /*nineClubs  =*/ Card("9",  9, Suit::Clubs);
// cards[22] = /*tenClubs   =*/ Card("10",  10, Suit::Clubs);
// cards[23] = /*jackClubs  =*/ Card("J", 10, Suit::Clubs);
// cards[24] = /*queenClubs =*/ Card("Q",10, Suit::Clubs);
// cards[25] = /*kingClubs  =*/ Card("K", 10, Suit::Clubs);
//
// cards[26] = /*aceDiamonds   =*/ Card("A",  11, Suit::Diamonds);
// cards[27] = /*twoDiamonds   =*/ Card("2",   2, Suit::Diamonds);
// cards[28] = /*threeDiamonds =*/ Card("3", 3, Suit::Diamonds);
// cards[29] = /*fourDiamonds  =*/ Card("4",  4, Suit::Diamonds);
// cards[30] = /*fiveDiamonds  =*/ Card("5",  5, Suit::Diamonds);
// cards[31] = /*sixDiamonds   =*/ Card("6",   6, Suit::Diamonds);
// cards[32] = /*sevenDiamonds =*/ Card("7", 7, Suit::Diamonds);
// cards[33] = /*eightDiamonds =*/ Card("8", 8, Suit::Diamonds);
// cards[34] = /*nineDiamonds  =*/ Card("9",  9, Suit::Diamonds);
// cards[35] = /*tenDiamonds   =*/ Card("10",  10, Suit::Diamonds);
// cards[36] = /*jackDiamonds  =*/ Card("J", 10, Suit::Diamonds);
// cards[37] = /*queenDiamonds =*/ Card("Q",10, Suit::Diamonds);
// cards[38] = /*kingDiamonds  =*/ Card("K", 10, Suit::Diamonds);
//
// cards[39] = /*aceHearts   =*/ Card("A",  11, Suit::Hearts);
// cards[40] = /*twoHearts   =*/ Card("2",   2, Suit::Hearts);
// cards[41] = /*threeHearts =*/ Card("3", 3, Suit::Hearts);
// cards[42] = /*fourHearts  =*/ Card("4",  4, Suit::Hearts);
// cards[43] = /*fiveHearts  =*/ Card("5",  5, Suit::Hearts);
// cards[44] = /*sixHearts   =*/ Card("6",   6, Suit::Hearts);
// cards[45] = /*sevenHearts =*/ Card("7", 7, Suit::Hearts);
// cards[46] = /*eightHearts =*/ Card("8", 8, Suit::Hearts);
// cards[47] = /*nineHearts  =*/ Card("9",  9, Suit::Hearts);
// cards[48] = /*tenHearts   =*/ Card("10",  10, Suit::Hearts);
// cards[49] = /*jackHearts  =*/ Card("J", 10, Suit::Hearts);
// cards[50] = /*queenHearts =*/ Card("Q",10, Suit::Hearts);
// cards[51] = /*kingHearts  =*/ Card("K", 10, Suit::Hearts);

// cards[0]  = aceSpades;
// cards[1]  = twoSpades;
// cards[2]  = threeSpades;
// cards[3]  = fourSpades;
// cards[4]  = fiveSpades;
// cards[5]  = sixSpades;
// cards[6]  = sevenSpades;
// cards[7]  = eightSpades;
// cards[8]  = nineSpades;
// cards[9]  = tenSpades;
// cards[10] = jackSpades;
// cards[11] = queenSpades;
// cards[12] = kingSpades;
//
// cards[13]  = aceClubs;
// cards[14]  = twoClubs;
// cards[15]  = threeClubs;
// cards[16]  = fourClubs;
// cards[17]  = fiveClubs;
// cards[18]  = sixClubs;
// cards[19]  = sevenClubs;
// cards[20]  = eightClubs;
// cards[21]  = nineClubs;
// cards[22]  = tenClubs;
// cards[23] = jackClubs;
// cards[24] = queenClubs;
// cards[25] = kingClubs;
//
// cards[26]  = aceDiamonds;
// cards[27]  = twoDiamonds;
// cards[28]  = threeDiamonds;
// cards[29]  = fourDiamonds;
// cards[30]  = fiveDiamonds;
// cards[31]  = sixDiamonds;
// cards[32]  = sevenDiamonds;
// cards[33]  = eightDiamonds;
// cards[34]  = nineDiamonds;
// cards[35]  = tenDiamonds;
// cards[36] = jackDiamonds;
// cards[37] = queenDiamonds;
// cards[38] = kingDiamonds;
//
// cards[39]  = aceHearts;
// cards[40]  = twoHearts;
// cards[41]  = threeHearts;
// cards[42]  = fourHearts;
// cards[43]  = fiveHearts;
// cards[44]  = sixHearts;
// cards[45]  = sevenHearts;
// cards[46]  = eightHearts;
// cards[47]  = nineHearts;
// cards[48]  = tenHearts;
// cards[49] = jackHearts;
// cards[50] = queenHearts;
// cards[51] = kingHearts;
