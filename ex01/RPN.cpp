
#include "RPN.hpp"

namespace
{
  void traverseWhiteSpace(std::string input, std::size_t& i)
  {
    while (std::isspace(input[i]))
    {
      ++i;
    }
  }

  bool isOperator(char c)
  {
    return c == '+' || c == '-' || c == '*' || c == '/';
  }

  bool isValidToken(char c)
  {
    return std::isdigit(c) || isOperator(c);
  }
}


///////// constructors //////////

RPN::RPN() {}

RPN::~RPN() {}


////////// methods //////////

void RPN::calculate(std::string input)
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

    if (!std::isspace(input[i]))
    {
      std::cerr << "ERROR: missing space\n";
      return;
    }

    traverseWhiteSpace(input, i);
  }

  if (nums_.size() != 1)
  {
    std::cerr << "ERROR\n";
    return;
  }
  std::cout << nums_.top() << "\n";
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
    const char* current = input.data() + i;
    char* end;
    long val = std::strtol(current, &end, 10);
    nums_.push(static_cast<int>(val));
  }
  else if (isOperator(input[i]))
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