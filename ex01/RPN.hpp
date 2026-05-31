
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <list>
#include <string>
#include <iostream>
#include <limits>

class RPN
{
  public:
    RPN();
    ~RPN();

    int calculate(const std::string input);

  private:
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);

    bool expectToken(const std::string& input, std::size_t& i);
    bool performOperation(const char op);
    bool evaluateOutcome();
    bool expectWhiteSpace(const std::string& input, std::size_t& i);
    bool acceptWhiteSpace(const std::string& input, std::size_t& i);

    std::stack<long, std::list<long> > nums_;
};

#endif