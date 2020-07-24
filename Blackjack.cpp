// fonts from http://www.patorjk.com/software/taag/#p=display&h=2&v=2&f=Big%20Money-ne&t=Blackjack

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
          do // loop to keep playing hands
          {
              if(playerWallet.getFunds()>0)
              {
                  playHand();
                  cout << "Play again? Enter 1 to play again: ";
                  cin  >> input;
              }
              else // end game if player runs out of money
                  input = 0;
          }
          while(input==1);
    }
    else if(input==2)
    {
        printRules();
        game();
    }
    if(playerWallet.getFunds()>0) // messages for ending the game
        cout << "Come back soon!\n";
    else
        cout << "Come back when you have more money.\n";
}

void Blackjack::placeBet()
{
    int amountToBet;
    bool inputDone = false;
    string inputString = "Bet must be a number.\n";

    do
    {
        cout << "Enter Bet (Funds available $"
        << playerWallet.getFunds() <<"): ";
        try // exceptions for proper bet input
        {
            cin >> amountToBet;
            if(!cin)
                throw inputString;
            else if(amountToBet > playerWallet.getFunds())
            {
                cout << "You don't have that kind of cash\n";
            }
            else if(amountToBet < 1)
            {
                cout << "We don't have time for this. Make a real bet\n";
            }
            else
                inputDone = true;
        }
        catch(string s)
        {
            cout << s;
            cin.clear();
            cin.ignore(100, '\n');
        }
    }
    while(!inputDone);

    bet = amountToBet;
    playerWallet.subtractFunds(bet);
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
      // set variables
      bool  done = false;
      playerBust = false;
      dealerBust = false;

      playerHand.discard();
      dealerHand.discard();
      playerStatus = "";
      dealerStatus = "";
      tableMessage = "\n";
      bet = 0;

      // get player bet
      placeBet();

      // shuffle cards if down to 13
      if(deck.getRemainingCards()<13)
      {
        deck.shuffle();
        cout << "Shuffling Cards\n";
      }

      // draw and tally player and dealer cards
      playerDraw();
      playerHand.tallyCards();
      dealerDraw();
      dealerHand.tallyCards();

      //print the board
      print();

      // check for blackjacks
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

      // skip this if blackjack
      while(!done)
      {
          // play out player hand
          playPlayerHand();
          if(!playerBust) // keep bust message til end of hand
              setPlayerStatus("");
          playDealerHand();
          done=true;


          // winning and losing with bet payouts
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
      playerWallet.addFunds(bet*2.5);
}

void Blackjack::push()
{
    // on a tie pay back player bet
    playerWallet.addFunds(bet);
    bet = 0;
    setTableMessage("PUSH");
}

void Blackjack::playPlayerHand()
{
    //main logic for playing a hand
    // set variables
    int input;
    bool done = false;
    bool inputDone = false;
    int hands = 0;
    string inputString = "Quit fooling around. 1, 2, or 3 only.\n";
    while (!done) // loop to draw cards until stay or bust
    {
      hands++;



      do // loop for exception handling
      {
        cout << "1 to hit. 2 to stay, 3 to double down: ";
        try // player input exceptions for hand decisions
        {
          cin >> input;
          if(!cin)
            throw inputString;
          else
            inputDone = true;
        }
        catch(string s)
        {
          cout << s;
          cin.clear();
          cin.ignore(100, '\n');
        }
      }
      while(!inputDone); // end try block while loop

      if(input==1) // hit
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
      else if(input==2) // stay
      {
          setPlayerStatus("Player Stands");
          done = true;
      }
      else if(input == 3) // double
      {
          if(hands == 1)
          {
              if (playerWallet.getFunds()>=bet)
              {
                  setPlayerStatus("Player Double Down");
                  playerWallet.subtractFunds(bet);
                  bet*=2;

                  hit(playerHand);
                  playerHand.tallyCards();
                  if(playerHand.getTotal()>21)
                  {
                    setPlayerStatus("Bust");
                    playerBust = true;
                  }
                  done=true;
              }
              else
              {
                setPlayerStatus("Not enough funds to double");
              }
          }
          else
            setPlayerStatus("You can only double for the first hit");
      }
      else
          setPlayerStatus("That is not an option."); // anything numbers other
                                                     // than 1, 2, and 3
      print();
    }
}

void Blackjack::playDealerHand()
{
    // logic for dealer hand
    bool done = false;

    flipDealerCard();
    print();

    do
    {
        if(dealerHand.getTotal()>21) // bust
        {
            dealerBust = true;
            setDealerStatus("Dealer Busts");
            done = true;
        }
        else if(dealerHand.getTotal()<17) // dealer hits for everything
        {                                 // under soft 17
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
    // function to print board
    int widthBuffer;

    if(playerHand.getTotal()<10) // variable to set proper
        widthBuffer = 51;        // spacing for "Wallet:$XXX"
    else
        widthBuffer = 50;
    // whitespace for terminal buffer
    cout << string( 6, '\n' );
    cout << "Dealer hand: ";
    dealerHand.print();
    cout << '\n';

    // only print dealer total after the blind
    // card has been flipped
    if (dealerHand.getCard(1).getActive()==true)
        cout << "Dealer total: "
        << dealerHand.getTotal() << "\n";
    else
        cout << "\n"; // print new line to match
    if (dealerStatus!="")
        cout << dealerStatus << '\n';

    cout << string( 6, '\n' )
         << setw(40) << tableMessage  // empty space with
         << string( 6, '\n' );        // message in the middle

    cout << "\nPlayer hand: ";
    playerHand.print();
    cout << setw(35) << "Bet: $" << bet << '\n';
    cout << "Player total: "
         << playerHand.getTotal() << setw(widthBuffer)
         << "Wallet: $" << playerWallet.getFunds() << '\n';
    if(playerStatus!="")
        cout << playerStatus << "\n\n";
    else
        cout << "\n\n";
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
  // function to print intro title
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
  // function to print rules
  int input;
  string inputString = "Input a number to return: ";
  bool done = false;
  cout << "\n\n\n\n\nBLACKJACK RULES:\n\n\n\n\n"
       << "Dealer stays on soft 17.\n"
       << "Over 21 is a bust.\n"
       << "Blackjack beats 21. Blackjack pushes blackjack\n"
       << "Blackjack is only an Ace and a 10 value card (10 or face)\n"
       << "Blackjack is only counted on the first deal of a hand.\n"
       << "If there is a blackjack on either side on open, the hand ends.\n"
       << "Hit means you want another card.\n"
       << "Stay/stand means you don't want anymore cards.\n"
       << "Double down means you only want 1 card, but you'll double your bet.\n"
       << "Double down is only allowed on the first hit.\n"
       << "You can only double if you have the available funds.\n\n\n"
       << "Enter 1 to return: ";
  do
  {
    try
    {
      cin >> input;
      if(!cin)
        throw inputString;
      else
        done = true;
    }
    catch(string s)
    {
      cout << s;
      cin.clear();
      cin.ignore(100, '\n');
    }
  }
  while(!done);
}

void Blackjack::flipDealerCard() const
{
    dealerHand.getCard(1).toggleActive();
}
