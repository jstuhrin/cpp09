
#include "PmergeMe.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Error: missing parameters\n";
    return 1;
  }

  PmergeMe pmergeMe(argc, argv);

  pmergeMe.FordJohnsonList();

  pmergeMe.FordJohnsonDeque();

  return 0;
}