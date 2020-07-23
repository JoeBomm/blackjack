

class Wallet
{
public:
  Wallet();
  Wallet(int);
  void addFunds(int);
  void subtractFunds(int);
  int getFunds() const;
  void setFunds(int);
  void print() const;

private:
  int funds;
};
