#include "Wallet.h"
#include <iostream>
#include <iomanip>
using namespace std;

Wallet::Wallet()
{
  funds = 0;
}

Wallet::Wallet(int amount)
{
    funds = amount;
}

void Wallet::addFunds(int amount)
{
    funds+=amount;
}

void Wallet::subtractFunds(int amount)
{
    if(funds>=amount)
        funds-=amount;
}

int Wallet::getFunds() const
{
    return funds;
}

void Wallet::setFunds(int amount)
{
    funds = amount;
}

void Wallet::print() const
{
    cout << fixed << setprecision(2)
         << "Wallet Total: $" << funds << '\n';
}
