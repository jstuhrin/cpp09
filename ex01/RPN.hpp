
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <iostream>
#include <cstdlib>

class RPN
{
  public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();

    void calculate(std::string input);

  private:
    bool consumeToken(const std::string& input, std::size_t& i);
    bool performOperation(const char op);

    std::stack<int> nums_;
};

#endif