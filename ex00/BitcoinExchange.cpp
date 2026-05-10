
/*
Syntactical validity of data and input files:
data.csv HEADER LINE: 'date,price'
input.txt HEADER LINE: 'date | value'

data.csv LINE: DATE COMMA PRICE
input.txt LINE: DATE SPACE '|' SPACE NUM
DATE: YEAR '-' MONTH '-' DAY
YEAR: [0000,2022]
MONTH: [1,12]
DAY: if MONTH in {1,3,5,7,8,10,12}: [1,31]
     if MONTH in {2}: if YEAR % 400 == 0 or (YEAR % 100 != 0 and YEAR % 4 == 0) : [1,29] else: [1,28]
     if MONTH in {4,6,9,11}: [1,30]
NUM: [0,1000]
*/

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : dataFileName_("data.csv") {}

BitcoinExchange::~BitcoinExchange() {}

int BitcoinExchange::runBitcoinExchange(std::string inputFileName)
{
  std::ifstream dataFile(dataFileName_.c_str());
  if (!dataFile)
  {
    std::cerr << "Error: cannot open file " << dataFileName_ << "\n";
    return 1;
  }

  std::string dataLine;
  std::getline(dataFile, dataLine);
  if (dataLine != "date,price")
  {
    std::cerr << "Error: missing header line: " << dataFileName_ << "\n";
    return 1;
  }
  while (std::getline(dataFile, dataLine))
  {
    if (!extractDataLine(dataLine))
    {
      std::cerr << "Error: bad file: " << dataFileName_ << "\n";
      return 1;
    }
  }

  std::ifstream inputFile(inputFileName.c_str());
  if (!inputFile)
  {
    std::cerr << "Error: cannot open file: " << inputFileName << "\n";
    return 1;
  }

  std::string inputLine;
  std::getline(inputFile, inputLine);
  if (inputLine != "date | value")
  {
    std::cerr << "Error: missing header line: " << inputFileName << "\n";
    return 1;
  }
  int errorInputFile = 0;
  while (std::getline(inputFile, inputLine))
  {
    errorInputFile = consumeInputLine(inputLine) || errorInputFile;
  }

  return errorInputFile;
}

bool BitcoinExchange::extractDataLine(const std::string& line)
{
  std::string::size_type comma = line.find(',', 0);
  if (comma == std::string::npos)
    return false;

  std::string date = line.substr(0, comma);
  if (!isValidDate(date))
    return false;

  std::string priceStr = line.substr(comma + 1);
  double price;
  if (!extractPrice(priceStr, price))
    return false;

  std::pair<std::map<std::string, double>::iterator, bool> result;
  result = history_.insert(std::pair<std::string, double>(date, price));
  if (result.second == false)
    return false;

  return true;
}

int BitcoinExchange::consumeInputLine(const std::string& line)
{
  std::string::size_type delimiter = line.find(" | ", 0);
  if (delimiter == std::string::npos)
  {
    std::cerr << "Error: bad input => " << line << "\n";
    return 1;
  }

  std::string date = line.substr(0, delimiter);
  if (!isValidDate(date))
  {
    std::cerr << "Error: invalid date\n";
    return 1;
  }

  std::string numStr = line.substr(delimiter + 3);
  double num;
  if (!extractNum(line, numStr, num))
    return 1;

  printLine(date, num);
  return 0;
}

bool BitcoinExchange::allDigits(const std::string& str, const std::size_t start, const std::size_t size) const
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

  std::istringstream iss;
  iss.str(date.substr(0, 4));
  int year;
  iss >> year;
  iss.clear();
  iss.str(date.substr(5, 2));
  int month;
  iss >> month;
  iss.clear();
  iss.str(date.substr(8, 2));
  int day;
  iss >> day;

  return isValidYear(year) && isValidMonth(month) && isValidDay(year, month, day);
}

bool BitcoinExchange::isValidYear(const int year) const
{
  return year >= 0000 && year <= 2022;
}

bool BitcoinExchange::isValidMonth(const int month) const
{
  return month >= 1 && month <= 12;
}

bool BitcoinExchange::isLeapYear(const int year) const
{
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

bool BitcoinExchange::isValidDay(const int year, const int month, const int day) const
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
      return day >= 1 && day <= 31;
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
  assert(false && "invalid month in isValidDay");
  __builtin_unreachable();
}

bool BitcoinExchange::extractPrice(const std::string& priceStr, double& price)
{
  std::istringstream iss(priceStr);
  if (iss >> price && iss.eof())
    return true;
  return false;
}

bool BitcoinExchange::extractNum(const std::string& line, const std::string& numStr, double& num)
{
  std::istringstream iss(numStr);
  if (!(iss >> num && iss.eof()))
  {
    std::cerr << "Error: bad input => " << line << "\n";
    return false;
  }

  if (num < 0)
  {
    std::cerr << "Error: not a positive number\n";
    return false;
  }

  if (num > 1000)
  {
    std::cerr << "Error: number too large\n";
    return false;
  }

  return true;
}

void BitcoinExchange::printLine(const std::string& date, const double& num)
{
  double value = 0;
  std::map<std::string, double>::iterator it = history_.lower_bound(date);
  
  if (it == history_.begin() && it->first != date)
  {
    std::cerr << "Error: date too early\n";
    return;
  }
  
  if (it->first != date)
  {
    --it;
  }

  if (it->second > std::numeric_limits<double>::max() / num)
  {
    std::cerr << "Error: result of multiplication overflows: " << it->second << " * " << num << "\n";
    return;
  }

  value = it->second * num;
  std::cout << date << " => " << num << " = " << std::setprecision(10) << value << "\n";
}
