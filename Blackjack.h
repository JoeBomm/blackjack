#include "Hand.h"
#include "Wallet.h"
#include <string>

using namespace std;

class Blackjack
{
public:
  Blackjack();
  void game();
  void placeBet();
  void dealerDraw();
  void playerDraw();
  void hit(Hand&);
  void playHand();
  void payBlackJack();
  void push();
  void playPlayerHand();
  void playDealerHand();
  void print() const;
  void setPlayerStatus(string);
  void setDealerStatus(string);
  void printTitle();
  void printRules() const;
  void setTableMessage(string);
  void flipDealerCard() const;




private:
  Deck deck = Deck(4);
  Hand dealerHand, playerHand;
  Wallet playerWallet= Wallet(1000);
  int bet;
  string playerStatus, dealerStatus, tableMessage;
  bool playerBust, dealerBust;

};
