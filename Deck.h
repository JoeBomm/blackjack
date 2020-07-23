#include "Card.h"
#include <string>

using namespace std;

class Deck
{

public:
  Deck();
  Deck(int);
  ~Deck();
  void shuffle();
  void print();
  Card draw();
  int getIndex();
  void incrementIndex();
  int getRemainingCards();

private:
  int index;
  int maxCards;
  Card *cards;
};









// void pop(int);
// Card getCard(int);
// Card
//   aceSpades, twoSpades, threeSpades, fourSpades,
//   fiveSpades, sixSpades, sevenSpades, eightSpades,
//   nineSpades, tenSpades, jackSpades, queenSpades,
//   kingSpades,
//   aceClubs, twoClubs, threeClubs, fourClubs,
//   fiveClubs, sixClubs, sevenClubs, eightClubs,
//   nineClubs, tenClubs, jackClubs, queenClubs,
//   kingClubs,
//   aceDiamonds, twoDiamonds, threeDiamonds, fourDiamonds,
//   fiveDiamonds, sixDiamonds, sevenDiamonds, eightDiamonds,
//   nineDiamonds, tenDiamonds, jackDiamonds, queenDiamonds,
//   kingDiamonds,
//   aceHearts, twoHearts, threeHearts, fourHearts,
//   fiveHearts, sixHearts, sevenHearts, eightHearts,
//   nineHearts, tenHearts, jackHearts, queenHearts,
//   kingHearts;
