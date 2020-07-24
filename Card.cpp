#if defined(__unix__) || defined(__unix)
#   define CARD_OS_LINUX
#elif defined (_WIN32) || defined (_WIN64)
#   define CARD_OS_WINDOWS
#else
#   error unspported platform
#endif

#include "Card.h"
#include <iostream>
#include "termcolor/termcolor.hpp"

using namespace std;

Card::Card()
{
    name ="null";
    value = 0;
    active = 0;
    cardSuit = Suit::Spades;
}

Card::Card(string name, int value, Suit cardSuit,  bool active)
{
  this->name = name;
  this->value = value;
  this->active = active;
  this->cardSuit = cardSuit;
}

const Card& Card::operator =(const Card& otherCard)
{

        name = otherCard.name;
        value = otherCard.value;
        active = otherCard.active;
        cardSuit = otherCard.cardSuit;
        return *this;
}

string Card::getName()
{
    return name;
}

int Card::getValue()
{
    return value;
}

bool Card::getActive() const
{
    return active;
}
void Card::toggleActive()
{
    active=(!active);
}

void Card::print()
{
    cout << termcolor::on_white;
    if(active)
    {
        if(cardSuit==Suit::Diamonds||cardSuit==Suit::Hearts)
            cout << termcolor::red;
        else
            cout << termcolor::grey;
        cout << name;
        if(getSuit()!="Null")
            cout << getSuit();
    }
    else
    {

        cout << termcolor::dark << termcolor::white
             <<termcolor::on_blue << termcolor::bold;
        #if defined(CARD_OS_LINUX)
            cout << "\uFF04";
        #else
            cout << "$";
        #endif
    }

    cout << termcolor::reset;
}

string Card::getSuit()
{
    if(cardSuit==Suit::Hearts)
    {
    #if defined(CARD_OS_LINUX)
        return "\u2665";
    #else
        return "H";
    #endif
    }
    else if (cardSuit==Suit::Diamonds)
    {
    #if defined(CARD_OS_LINUX)
        return "\u2666";
    #else
        return "D";
    #endif

    }
    else if (cardSuit==Suit::Spades)
    {
    #if defined(CARD_OS_LINUX)
        return "\u2660";
    #else
        return "S";
    #endif
    }
    else if (cardSuit==Suit::Clubs)
    {
    #if defined(CARD_OS_LINUX)
        return "\u2663";
    #else
        return "C";
    #endif
    }
    else
        return "Null";
}
