
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange
{
  public:
    BitcoinExchange();
    ~BitcoinExchange();

    void processData();

  private:
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    std::map<>
}

#endif