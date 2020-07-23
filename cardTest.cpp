#include "Wallet.h"
#include "Hand.h"

#include <iostream>

using namespace std;

int main()
{
  int decks = 3;
  Deck myDeck = Deck();
  Hand myHand = Hand();
  Hand otherHand = Hand();
  // Wallet myWallet = Wallet(1000);
  //
  // myWallet.print();


  myDeck.shuffle();
  // myHand.draw(myDeck);
  // myHand.draw(myDeck);
  // myHand.draw(myDeck);
  // myHand.draw(myDeck);
  //
  //
  // for(int i=0; i<52*decks; i++)
  // {
    myHand.draw(myDeck);
  // }
  myHand.print();
  // myDeck.print();
  // myHand.draw(myDeck);
  // myDeck.print();
  // cout << '\n';
  // //
  // myDeck.shuffle();
  // // myDeck.print();
  // //
  // cout << '\n';
  // cout << "Index before draw: " << myDeck.getIndex() << '\n';
  // myHand.draw(myDeck);
  // cout << '\n';
  // cout << "Index after draw: " << myDeck.getIndex() << '\n';
  // cout << "hand length: " << myHand.getHandLength() << '\n';
  // cout << "card active: " << myHand.getCard(0).getActive() << '\n';
  // myDeck.print();
  // myHand.tallyCards();
  // cout << myHand.getTotal() << '\n';


  return 0;
}
