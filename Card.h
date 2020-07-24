#include <string>
#include "Suit.h"

using namespace std;

class Card
{
public:
  Card();
  Card(string, int, Suit, bool active=0);
  const Card& operator =(const  Card&);
  string getName();
  int getValue();
  bool getActive() const;
  void toggleActive();
  void print();
  string getSuit();

private:
  string name;
  int value;
  Suit cardSuit;
  bool active;
};
