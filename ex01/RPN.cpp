
#include "RPN.hpp"

///////// constructors //////////

RPN::RPN() {}

RPN::~RPN() {}

////////// methods //////////

int RPN::calculate(const std::string input)
{
  std::size_t i = 0;

  acceptWhiteSpace(input, i);

  while (true)
  {
    if (i == input.size())
    {
      break;
    }
    if (!expectToken(input, i))
    {
      return 1;
    }
    if (i == input.size())
    {
      break;
    }
    if (!expectWhiteSpace(input, i))
    {
      return 1;
    }
  }

  if (!evaluateOutcome())
  {
    return 1;
  }
  return 0;
}

bool RPN::expectToken(const std::string& input, std::size_t& i)
{
  if (std::isdigit(static_cast<unsigned char>(input[i])))
  {
    nums_.push(input[i] - '0');
  }
  else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
  {
    if (!performOperation(input[i]))
    {
      return false;
    }
  }
  else
  {
    std::cerr << "ERROR: invalid token\n";
    return false;
  }
  ++i;
  return true;
}

bool RPN::performOperation(const char op)
{
  if (nums_.size() < 2)
  {
    std::cerr << "ERROR: missing number value before operator\n";
    return false; 
  }

  DataType second = nums_.top();
  nums_.pop();
  DataType first = nums_.top();
  nums_.pop();

  switch (op)
  {
    case '+':
      if (first > std::numeric_limits<DataType>::max() - second)
      {
        std::cerr << "ERROR: overflow\n";
        return false;
      }
      nums_.push(first + second);
      break;
    case '-':
      if (first < std::numeric_limits<DataType>::min() + second)
      {
        std::cerr << "ERROR: underflow\n";
        return false;
      }
      nums_.push(first - second);
      break;
    case '*':
      if (first > std::numeric_limits<DataType>::max() / second || first < std::numeric_limits<DataType>::min() / second)
      {
        std::cerr << "ERROR: overflow/underflow\n";
        return false;
      }
      nums_.push(first * second);
      break;
    case '/':
      if (second == 0)
      {
        std::cerr << "ERROR: division by zero\n";
        return false;
      }
      nums_.push(first / second);
      break;
  }
  return true;
}

bool RPN::evaluateOutcome()
{
  if (nums_.size() < 1)
  {
    std::cerr << "ERROR: missing number\n";
    return false;
  }
  if (nums_.size() > 1)
  {
    std::cerr << "ERROR: missing operator\n";
    return false;
  }
  std::cout << nums_.top() << "\n";
  nums_.pop();
  return true;
}

bool RPN::expectWhiteSpace(const std::string& input, std::size_t& i)
{
  if (!acceptWhiteSpace(input, i))
  {
    std::cerr << "ERROR: missing space\n";
    return false;
  }
  return true;
}

bool RPN::acceptWhiteSpace(const std::string& input, std::size_t& i)
{
  if (!std::isspace(static_cast<unsigned char>(input[i])))
  {
    return false;
  }
  i = input.find_first_not_of(" \f\n\r\t\v", i);
  if (i == std::string::npos)
  {
    i = input.size();
  }
  return true;
}