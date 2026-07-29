
#include <iostream>
#include <stdexcept>

#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Error: missing parameters\n";
    return 1;
  }

  try
  {
    PmergeMe pmergeMe(argc, argv);
    pmergeMe.sort();
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}