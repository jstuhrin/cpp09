
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>

class PmergeMe
{
  public:
    PmergeMe();
    ~PmergeMe();

    bool populate(int argc, char** argv);

  private:
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);

    std::deque<int> deq_;
    std::list<int> list_;
};

#endif