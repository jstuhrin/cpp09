
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>


class BitcoinExchange
{
  public:
    BitcoinExchange();
    ~BitcoinExchange();

    int runBitcoinExchange(std::string inputFileName);

  private:
    BitcoinExchange(const BitcoinExchange& other);
    BitcoinExchange& operator=(const BitcoinExchange& other);

    bool extractDataLine(const std::string& line);
    void consumeInputLine(const std::string& line);
    bool allDigits(const std::string& str, const size_t start, const size_t size) const;
    bool isValidDate(const std::string& date) const;
    bool isValidYear(const long year) const;
    bool isValidMonth(const long month) const;
    bool isLeapYear(const long year) const;
    bool isValidDay(const long year, const long month, const long day) const;
    bool extractPrice(const std::string& priceStr, double& price);
    bool extractNum(const std::string& line, const std::string& numStr, double& num);
    void printLine(const std::string& date, const double& num);

    const std::string dataFileName_;
    std::map<std::string, double> history_;
};

#endif
