
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>

class PmergeMe
{
  public:
    PmergeMe(int argc, char** argv);
    ~PmergeMe();
    void sort();

  private:
    void populate(int argc, char** argv);

    void fordJohnsonDeque(int numElements, int sizeElements);
    void pairWiseSortDeque(int numElements, int sizeElements);
    void binaryInsertionDeque(int numElements, int sizeElements);

    void fordJohnsonList(int numElements, int sizeElements);
    void pairWiseSortList(int numElements, int sizeElements);
    void binaryInsertionList(int numElements, int sizeElements);

    double log2(double x);
    int calculateMaxComparisons(int n);
    int numComparisons_;

    std::deque<int> deq_;
    std::list<int> list_;

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#endif