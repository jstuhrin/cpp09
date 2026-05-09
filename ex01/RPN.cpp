
#include "RPN.hpp"


///////// constructors //////////

RPN::RPN() {}

RPN::~RPN() {}


////////// methods //////////

void RPN::calculate(const std::string input)
{
  std::size_t i = 0;
  traverseWhiteSpace(input, i);
  while (true)
  {
    if (input[i] == '\0')
    {
      break;
    }
    if (!consumeToken(input, i))
    {
      return;
    }
    if (input[i] == '\0')
    {
      break;
    }
    if (!traverseWhiteSpace(input, i))
    {
      std::cerr << "ERROR: missing space\n";
      return;
    }
  }
  evaluateOutcome();
}

bool RPN::consumeToken(const std::string& input, std::size_t& i)
{
  if (!isValidToken(input[i]))
  {
    std::cerr << "ERROR: invalid token\n";
    return false;
  }
  if (std::isdigit(input[i]))
  {
    nums_.push(input[i] - '0');
  }
  else
  {
    if (!performOperation(input[i]))
    {
      return false;
    }
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
  int second = nums_.top();
  nums_.pop();
  int first = nums_.top();
  nums_.pop();
  if (op == '/' && second == 0)
  {
    std::cerr << "ERROR: division by zero\n";
    return false;
  }
  int currentResult = 0;
  switch (op)
  {
    case '+':
      currentResult = first + second;
      break;
    case '-':
      currentResult = first - second;
      break;
    case '*':
      currentResult = first * second;
      break;
    case '/':
      currentResult = first / second;
      break;
  }
  nums_.push(currentResult);
  return true;
}

void RPN::evaluateOutcome() const
{
  if (nums_.size() < 1)
  {
    std::cerr << "ERROR: missing number\n";
    return;
  }
  if (nums_.size() > 1)
  {
    std::cerr << "ERROR: missing operator\n";
    return;
  }
  std::cout << nums_.top() << "\n";
}

bool RPN::traverseWhiteSpace(const std::string& input, std::size_t& i)
{
  std::string::size_type first;
  first = input.find_first_of(' ', i);
  if (first != i)
  {
    return false;
  }
  std::string::size_type last;
  last = input.find_first_not_of(' ', i);
  i = last == std::string::npos ? input.size() : last;
  return true;
}

bool RPN::isOperator(const char c) const
{
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool RPN::isValidToken(const char c) const
{
  return std::isdigit(c) || isOperator(c);
}