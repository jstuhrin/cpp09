
#include "RPN.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "ERROR: please provide exactly one argument\n";
    return 1;
  }
  RPN rpn;
  rpn.calculate(argv[1]);
  return 0;
}