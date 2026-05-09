
#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <list>
#include <string>
#include <iostream>

class RPN
{
  public:
    RPN();
    ~RPN();

    void calculate(const std::string input);

  private:
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);

    bool consumeToken(const std::string& input, std::size_t& i);
    bool performOperation(const char op);
    void evaluateOutcome() const;
    bool traverseWhiteSpace(const std::string& input, std::size_t& i);
    bool isOperator(const char c) const;
    bool isValidToken(const char c) const;

    std::stack<int, std::list<int> > nums_;
};

#endif