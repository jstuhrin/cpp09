
#include "RPN.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "ERROR: please provide exactly one argument\n";
    return 1;
  }
  RPN rpn;
  return (rpn.calculate(argv[1]));
}