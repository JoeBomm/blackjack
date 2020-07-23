/*
  _   _   _   _   _   _     _   _   _   _   _
 / \ / \ / \ / \ / \ / \   / \ / \ / \ / \ / \
( C | a | s | i | n | o ) ( N | i | g | h | t )
 \_/ \_/ \_/ \_/ \_/ \_/   \_/ \_/ \_/ \_/ \_/

 /$$$$$$$  /$$                     /$$                               /$$
| $$__  $$| $$                    | $$                              | $$
| $$  \ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$ /$$  /$$$$$$   /$$$$$$$| $$   /$$
| $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/|__/ |____  $$ /$$_____/| $$  /$$/
| $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/  /$$  /$$$$$$$| $$      | $$$$$$/
| $$  \ $$| $$ /$$__  $$| $$      | $$_  $$ | $$ /$$__  $$| $$      | $$_  $$
| $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \  $$| $$|  $$$$$$$|  $$$$$$$| $$ \  $$
|_______/ |__/ \_______/ \_______/|__/  \__/| $$ \_______/ \_______/|__/  \__/
                                       /$$  | $$
                                      |  $$$$$$/
                                       \______/


                                                   a game by Joe Bommarito
fonts: http://www.patorjk.com/software/taag/#p=display&h=2&v=2&f=Big%20Money-ne&t=Blackjack



Dealer hand
##
Total: ##
Dealer Action




                    MESSAGE(Push/Winner)






Player Hand
##
Total: ###                                  Bet: $99
Player Action                            Wallet: $9999

Prompt.......:|||


*/

#include "Blackjack.h"
#include <iostream>
#include <iomanip>
#include "termcolor/termcolor.hpp"
#include <limits>


using namespace std;

Blackjack::Blackjack()
{
  bet = 0;
  playerStatus = "\n";
  dealerStatus = "\n";
  tableMessage = "\n";
  playerBust = false;
  dealerBust = false;
}

void Blackjack::game()
{
  int input;
  bool done = false;


  deck.shuffle();
  printTitle();
  cout << "Enter 1 to play or 2 for rules: ";

    cin  >> input;
    if(input==1)
    {
        do
        {
          if(playerWallet.getFunds()>0)
          {
            playHand();
            cout << "Play again? Enter 1 to play again: ";
            cin  >> input;
          }
          else
            input = 0;
        }
        while(input==1);
    }
    else if(input==2)
    {
        printRules();
        game();
    }
    if(playerWallet.getFunds()>0)
        cout << "Come back soon!\n";
    else
        cout << "Come back when you have more money.\n";
}


void Blackjack::placeBet(int amount)
{
    if (playerWallet.getFunds()>=amount && amount>0)
    {
        bet = amount;
        playerWallet.subtractFunds(amount);
    }
    else bet = 0;
}

void Blackjack::dealerDraw()
{
    dealerHand.draw(deck);
    dealerHand.blindDraw(deck);
}

void Blackjack::playerDraw()
{
    for(int i=0; i<2; i++)
        playerHand.draw(deck);
}

void Blackjack::hit(Hand & hand)
{
    hand.draw(deck);
}

void Blackjack::playHand()
{
      bool  done = false;
      playerBust = false;
      dealerBust = false;

      playerHand.discard();
      dealerHand.discard();
      playerStatus = "\n";
      dealerStatus = "\n";
      tableMessage = "\n";
      bet = 0;

      int amountToBet = 0;
      while(bet==0)
      {
          cout << "Enter Bet (Funds available $"
               << playerWallet.getFunds() <<"): ";
          cin  >> amountToBet;
          placeBet(amountToBet);
      }

      if(deck.getRemainingCards()<13)
      {
        deck.shuffle();
        cout << "Shuffling Cards\n";
      }

      dealerDraw();
      dealerHand.tallyCards();


      playerDraw();
      playerHand.tallyCards();

      print();

      if(dealerHand.getTotal()==21)
      {
          flipDealerCard();
          if(playerHand.getTotal()==21)
              push();
          else
              setTableMessage("Dealer Blackjack. Player Loses");
          done = true;
      }
      else if(playerHand.getTotal()==21)
      {
          setTableMessage("BLACKJACK!");
          flipDealerCard();
          payBlackJack();
          done = true;
      }

      while(!done)
      {
          playPlayerHand();
          if(!playerBust)
              setPlayerStatus("");
          playDealerHand();
          done=true;

          if(playerBust)
              setTableMessage("BUST");
          else if (dealerBust)
          {
              setTableMessage("WIN, DEALER BUST");
              playerWallet.addFunds(bet*2);
          }
          else if(playerHand.getTotal()>dealerHand.getTotal())
          {
            playerWallet.addFunds(bet*2);
            setTableMessage("Player Wins");
          }
          else if (playerHand.getTotal()<dealerHand.getTotal())
          {
            setTableMessage("Player Loses");
          }
          else
          {
            push();
          }
      }
      print();



}

void Blackjack::payBlackJack()
{
      playerWallet.addFunds(bet*1.5);
}

void Blackjack::push()
{
    playerWallet.addFunds(bet);
    bet = 0;
    setTableMessage("PUSH");
}

void Blackjack::playPlayerHand()
{
    int input;
    bool done = false;
    while (!done)
    {
      cout << "\n1 to hit. 2 to stay: ";
      cin  >> input;
      cout << string( 6, '\n' );

      if(input==1)
      {
          hit(playerHand);
          setPlayerStatus("Player Hits");
          playerHand.tallyCards();
          if(playerHand.getTotal()>21)
          {
            setPlayerStatus("Bust");
            playerBust = true;
            done=true;
          }
      }
      else if(input==2)
      {
          setPlayerStatus("Player Stands");
          done = true;
      }

      print();
    }
}

void Blackjack::playDealerHand()
{
    bool done = false;

    flipDealerCard();
    print();

    do
    {
        if(dealerHand.getTotal()>21)
        {
            dealerBust = true;
            setDealerStatus("Dealer Busts");
            done = true;
        }
        else if(dealerHand.getTotal()<17)
        {
            hit(dealerHand);
            setDealerStatus("Dealer Hits");
            dealerHand.tallyCards();
        }
        else
        {
          setDealerStatus("Dealer Stands");
          done = true;
        }
        print();
    }
    while(!done);
}

void Blackjack::print() const
{
    cout << "\nDealer hand: ";
    dealerHand.print();
    cout << '\n';

    if (dealerHand.getCard(1).getActive()==true)
        cout << "Dealer total: "
        << dealerHand.getTotal() << '\n';
    if (dealerStatus!="")
        cout << dealerStatus << '\n';

    cout << string( 6, '\n' );
    cout << setw(40) << tableMessage;
    cout << string( 6, '\n' );


    cout << "\nPlayer hand: ";
    playerHand.print();
    cout << setw(50) << "Bet: $" << bet << '\n';
    cout << "Player total: "
         << playerHand.getTotal() << setw(50)
         << "Wallet: $" << playerWallet.getFunds() << '\n';
     if(playerStatus!="")
        cout << playerStatus << '\n';
}

void Blackjack::setPlayerStatus(string status)
{
    playerStatus = status;
}

void Blackjack::setDealerStatus(string status)
{
    dealerStatus = status;
}

void Blackjack::setTableMessage(string message)
{
    tableMessage = message;
}

void Blackjack::printTitle()
{
  cout << termcolor::blink << "\n\n"
       <<"\t\t  _   _   _   _   _   _     _   _   _   _   _\n"
       <<"\t\t / \\ / \\ / \\ / \\ / \\ / \\   / \\ / \\ / \\ / \\ / \\\n"
       <<"\t\t( C | a | s | i | n | o ) ( N | i | g | h | t )\n"
       <<"\t\t \\_/ \\_/ \\_/ \\_/ \\_/ \\_/   \\_/ \\_/ \\_/ \\_/ \\_/\n\n"
       << termcolor::reset << termcolor::green
       <<"  /$$$$$$$  /$$                     /$$                               /$$\n"
       <<" | $$__  $$| $$                    | $$                              | $$\n"
       <<" | $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$ /$$  /$$$$$$   /$$$$$$$| $$   /$$\n"
       <<" | $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/|__/ |____  $$ /$$_____/| $$  /$$/\n"
       <<" | $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/  /$$  /$$$$$$$| $$      | $$$$$$/\n"
       <<" | $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$ | $$ /$$__  $$| $$      | $$_  $$\n"
       <<" | $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$\n"
       <<" |_______/ |__/ \\_______/ \\_______/|__/  \\__/| $$ \\_______/ \\_______/|__/  \\__/\n"
       <<"                                        /$$  | $$\n"
       <<"                                       |  $$$$$$/\n"
       <<"                                        \\______/\n\n\n"
       <<"                                                    a game by Joe Bommarito\n\n\n"
       << termcolor::reset;

}

void Blackjack::continueMessage() const
{
    cout << "Press Enter to Continue";
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
}

void Blackjack::printRules() const
{
  int input;
  cout << "These are the rules\n";
  cout << "Enter 1 to return: ";
  cin >> input;

}

void Blackjack::flipDealerCard() const
{
    dealerHand.getCard(1).toggleActive();
}
