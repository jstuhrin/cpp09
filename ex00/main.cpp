
#include "BitcoinExchange.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Error: cannot open file\n";
    return 1;
  }

  BitcoinExchange bce;

  int result = bce.runBitcoinExchange(argv[1]);

  return result;
}