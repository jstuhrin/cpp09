
/*
Syntactical validity:

data.csv LINE: DATE COMMA PRICE
input.txt LINE: DATE SPACE '|' SPACE PRICE
DATE: YEAR '-' MONTH '-' DAY
YEAR: [2009,2022]
MONTH: [1,12]
DAY: if MONTH in {1,3,5,7,8,10,12}: [1,31]
     if MONTH in {2}: if YEAR % 400 == 0 or (YEAR % 100 != 0 and YEAR % 4 == 0) : 29 else: [1,28]
     if MONTH in {4,6,9,11}: [1,30]
PRICE: [0,1000]
*/

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}



bool extractDataLine(const std::string& line)
{
  std::string::size_type comma = line.find(',', 0);
  if (comma == std::string::npos)
    return false;

  std::string date = line.substring(0, comma);
  if (!isValidDate(date))
    return false;

  std::string priceStr = line.substring(comma + 1, line.size());
  int price;
  if (!extractPrice(priceStr, price))
    return false;

  std::pair<std::map<std::string, int>::iterator, bool> result;
  result = history_.insert(date, price);
  if (result.second == false)
    return false;

  return true;
}

void consumeInputLine(const std::string& line)
{
  std::string::size_type delimiter = find(" | ", 0);
  if (delimiter == std::string::npos)
    return;

  std::string date = line.substring(0, delimiter);
  if (!isValidDate(date))
    return;

  std::string numStr = line.substring(delimiter + 3, line.size());
  float num;
  if (!extractNum(numStr, num))
    return;

  printLine(date, num);
}

bool BitcoinExchange::allDigits(const std::string& str, const size_t start, const size_t size) const
{
  for (size_t i = start; i < size; ++i)
  {
    if (!std::isdigit(static_cast<unsigned char>(str[i])))
      return false;
  }
  return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
  if (date.size() != 10)
    return false;

  if (!allDigits(date, 0, 4))
    return false;
  if (date[4] != '-')
    return false;
  if (!allDigits(date, 5, 2))
    return false;
  if (date[7] != '-')
    return false;
  if (!allDigits(date, 8, 2))
    return false;

  std::istringstream ss;
  ss.str(date.substr(0, 4));
  int year;
  ss >> year;
  ss.clear();
  ss.str(date.substr(5, 2));
  int month;
  ss >> month;
  ss.clear();
  ss.str(date.substr(8, 2));
  int day;
  ss >> day;

  return isValidYear(year) && isValidMonth(month) && isValidDay(year, month, day);
}

bool BitcoinExchange::isValidYear(const long year) const
{
  return year >= 2009 && year <= 2022;
}

bool BitcoinExchange::isValidMonth(const long month) const
{
  return month>= 1 && month <= 12;
}

bool BitcoinExchange::isLeapYear(const long year) const
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool BitcoinExchange::isValidDay(const long year, const long month, const long day) const
{
  switch (month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
      return day >=1 && day <= 31;
    case 2:
      if (isLeapYear(year))
        return day >= 1 && day <= 29;
      return day >= 1 && day <= 28;
    case 4:
    case 6:
    case 9:
    case 11:
      return day >= 1 && day <= 30;
  }
}

bool BitcoinExchange::extractPrice(const std::string& priceStr, int& price)
{
  if (priceStr.size() > 4)
    return false;

  if (!allDigits(priceStr, 0, priceStr.size()))
    return false;

  std::istringstream ss(priceStr);
  ss >> price;

  return price >= 0 && price <= 1000;
}

bool BitcoinExchange::extractNum()
{

}

void BitcoinExchange::printLine(const std::string& date, const float num)
{
  // todo: calculate value
  std::cout << date << " => " << num << " = " << value << "\n";
}