
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>

class PmergeMe
{
  public:
    PmergeMe();
    ~PmergeMe();

  private:
    bool populate(int argc, char** argv);
    void fordJohnsonDeque();
    void pairWiseSortDeque();
    void binaryInsertionDeque();
    void fordJohnsonList();
    void pairWiseSortList();
    void binaryInsertionList();

    std::deque<int> deq_;
    std::list<int> list_;

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#endif