
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <cstdlib>

class RPN
{
  public:
    RPN();
    ~RPN();

    int calculate(const std::string input);

  private:
    RPN(const RPN& other); // private and not implemented, since there is no reason to ever make a copy of this class
    RPN& operator=(const RPN& other);

    bool expectToken(const std::string& input, std::size_t& i);
    bool performOperation(const char op);
    bool evaluateOutcome();
    bool expectWhiteSpace(const std::string& input, std::size_t& i);
    bool acceptWhiteSpace(const std::string& input, std::size_t& i);

    std::stack<double> nums_;
};

#endif