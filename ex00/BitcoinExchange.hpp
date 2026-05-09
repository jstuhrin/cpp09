
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>


class BitcoinExchange
{
  public:
    BitcoinExchange();
    ~BitcoinExchange();

    void processData();

  private:
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    std::map<std::string, int> history_;
}

#endif