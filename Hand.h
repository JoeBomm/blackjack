#include "Deck.h"

using namespace std;

class Hand
{
public:
  Hand();
  ~Hand();
  void tallyCards();
  void draw(Deck&);
  void blindDraw(Deck&);
  void discard(int);
  void discard();
  void print() const;
  int getTotal() const;
  void checkAce();
  void incHandLength();
  void decHandLength();
  int getHandLength();
  Card &getCard(int) const;


private:
    Card *handList;
    int handLength;
    int total;
    int aces;
    // bool aceInHand;
    // bool checked;
};
