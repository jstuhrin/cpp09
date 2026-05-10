
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <limits>
#include <iomanip>


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
    int consumeInputLine(const std::string& line);
    bool allDigits(const std::string& str, const std::size_t start, const std::size_t size) const;
    bool isValidDate(const std::string& date) const;
    bool isValidYear(const int year) const;
    bool isValidMonth(const int month) const;
    bool isLeapYear(const int year) const;
    bool isValidDay(const int year, const int month, const int day) const;
    bool extractPrice(const std::string& priceStr, double& price);
    bool extractNum(const std::string& line, const std::string& numStr, double& num);
    int printLine(const std::string& date, const double& num);

    const std::string dataFileName_;
    std::map<std::string, double> history_;
};

#endif
