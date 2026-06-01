
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
  public:
    PmergeMe();
    ~PmergeMe();

  private:
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
};

#endif