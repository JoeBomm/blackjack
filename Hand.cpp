#include "Hand.h"
#include <iostream>
#include <iomanip>

using namespace std;

Hand::Hand()
{
    handList = new Card[0];
    total = 0;
    // aceInHand = false;
    handLength = 0;
    // checked = false;
    aces = 0;
}

Hand::~Hand()
{
    delete [] handList;
    handList = nullptr;
}

void Hand::tallyCards()
{
    total = 0;

    // checkAce();
    for(int i=0; i<handLength; i++)
    {
        total += handList[i].getValue();
        if(handList[i].getValue()==1)
            aces++;
    }
    checkAce();

}


void Hand::blindDraw(Deck &drawPile)
{
    incHandLength();
    handList[handLength-1] = drawPile.draw();
}

void Hand::draw(Deck &drawPile)
{
    blindDraw(drawPile);
    handList[handLength-1].toggleActive();

}

void Hand::discard(int index)
{
    for(int i=index; i<handLength; i++)
    {
        handList[i]=handList[i+1];
    }
    decHandLength();
}
void Hand::discard()
{
  delete [] handList;
  handList = new Card[0];
  total = 0;
  handLength = 0;
  aces = 0;
}

void Hand::print() const
{

    for(int i=0; i<handLength; i++)
    {
          handList[i].print();
          cout << ' ';
    }
    for(int i=0; i<6-handLength; i++)
        cout << "   ";
}

int Hand::getTotal() const
{
      return total;
}

void Hand::checkAce()
{
      if(aces>0)
      {
          if(total<=11)
              total+=10;
      }
}

void Hand::incHandLength()
{
    Card *temp = new Card[handLength];
    for(int i=0; i<handLength; i++)
    {
        temp[i]=handList[i];
    }
    delete [] handList;

    handLength++;

    handList = new Card[handLength];
    for(int i=0; i<handLength-1; i++)
    {
      handList[i] = temp[i];
    }
    delete [] temp;
    temp = nullptr;
}

void Hand::decHandLength()
{
  if (handLength!=0)
  {
      handLength--;
      Card *temp = new Card[handLength];
      for(int i=0; i<handLength; i++)
      {
          temp[i]=handList[i];
      }
      delete [] handList;

      handList = new Card[handLength];
      for(int i=0; i<handLength; i++)
      {
          handList[i] = temp[i];
      }
      delete [] temp;
      temp = nullptr;
  }
  else
      cout << "Hand length cannot be less than 0\n";
}

int Hand::getHandLength()
{
    return handLength;
}

Card& Hand::getCard(int index) const
{
    if(handLength>index)
    {
        return handList[index];
    }
}
