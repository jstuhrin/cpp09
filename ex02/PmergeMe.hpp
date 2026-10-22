
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>
#include <utility>

class PmergeMe
{
  public:
    PmergeMe(int argc, char** argv);
    ~PmergeMe();
    void sort();

  private:
    void populate(int argc, char** argv);

    void updateJacobsthal(int& currJacobsthal, int& prevJacobsthal);

    void fordJohnsonDeque(const int numElements, const int sizeElements);
    int getSignificantIntDeque(std::deque<int>::const_iterator element, const int sizeElements);
    void swapElementsDeque(std::deque<int>::iterator leftIt, std::deque<int>::iterator rightIt, const int sizeElements);
    void pairWiseSortDeque(const int numElements, const int sizeElements);
    void populateDeques(std::deque<int>& main, std::deque<int>& pending, std::deque<int>& bounds, const int numElements, const int sizeElements);
    std::pair<int, std::deque<int>::iterator> binarySearch(std::deque<int>& mainChain, const int value, const int rightBound, const int sizeElements);
    void updateBounds(std::deque<int>& bounds, const int insertPos);
    int getCurrElementIdx(const int currJacobsthal, const int numPendingElements);
    std::deque<int>::iterator getCurrentIt(std::deque<int>& d, const int currElementIdx, const int sizeElements);
    void insertElements(std::deque<int>& mainChain, std::deque<int>& pending, std::deque<int>& bounds, const int sizeElements);
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

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#endif