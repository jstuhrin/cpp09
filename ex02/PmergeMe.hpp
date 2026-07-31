
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

    void updateJacobsthal();

    void fordJohnsonDeque(int numElements, int sizeElements);
    void pairWiseSortDeque(int numElements, int sizeElements);
    void binaryInsertionDeque(int numElements, int sizeElements);

    void fordJohnsonList(int numElements, int sizeElements);
    int getSignificantInt(std::list<int>::iterator element, int sizeElements);
    void pairWiseSortList(int numElements, int sizeElements);
    void binaryInsertionList(int numElements, int sizeElements);

    
    void printList(std::list<int> currList, int sizeElements, int numElements);
    double log2(double x);
    int calculateMaxComparisons(int n);

    std::deque<int> deq_;
    std::list<int> list_;

    int numComparisons_;
    int currJacobsthal_;
    int prevJacobsthal_;

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#endif