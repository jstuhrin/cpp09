
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

    void fordJohnsonDeque(const int numElements, const int sizeElements);
    int getSignificantIntDeque(std::deque<int>::const_iterator element, const int sizeElements);
    void swapElementsDeque(std::deque<int>::iterator leftIt, std::deque<int>::iterator rightIt, const int sizeElements);
    void pairWiseSortDeque(const int numElements, const int sizeElements);
    void binaryInsertionDeque(const int numElements, const int sizeElements);

    void fordJohnsonList(const int numElements, const int sizeElements);
    int getSignificantInt(std::list<int>::const_iterator element, const int sizeElements) const;
    void pairWiseSortList(const int numElements, const int sizeElements);
    void binaryInsertionList(const int numElements, const int sizeElements);

    
    void printDeque(const std::deque<int>& deq, const int sizeElements, const int numElements) const;
    void printList(const std::list<int>& currList, const int sizeElements, const int numElements) const;
    void printList(const std::list<std::list<int>::iterator>& currList) const;
    double log2(const double x) const;
    int calculateMaxComparisons(const int n) const;

    std::deque<int> deq_;
    std::list<int> list_;

    int numComparisonsList_;
    int numComparisonsDeque_;
    int currJacobsthal_;
    int prevJacobsthal_;

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#endif