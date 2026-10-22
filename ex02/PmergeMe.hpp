
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>
#include <vector>
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

    int getCurrElementIdx(const int currJacobsthal, const int numPendingElements); 

    template <typename container>
    std::pair<int, typename container::iterator> binarySearch(container& mainChain, const int value, const int rightBound, const int sizeElements);
    template <typename it>
    void pairWiseSort(it leftIt, const int numElements, const int sizeElements);
    template <typename Container>
    void binaryInsertion(Container& cont, const int numElements, const int sizeElements);
    template <typename container>
    void insertElements(container& mainChain, container& pending, container& bounds, const int sizeElements);
    template <typename container>
    void fordJohnson(container& cont, const int numElements, const int sizeElements);

 

    void fordJohnsonList(const int numElements, const int sizeElements);
    // int getSignificantInt(std::list<int>::const_iterator element, const int sizeElements) const;
    void pairWiseSortList(const int numElements, const int sizeElements);
    void binaryInsertionList(const int numElements, const int sizeElements);

    
    void printDeque(const std::deque<int>& deq, const int sizeElements, const int numElements) const;
    void printList(const std::list<int>& currList, const int sizeElements, const int numElements) const;
    void printList(const std::list<std::list<int>::iterator>& currList) const;
    double log2(const double x) const;
    int calculateMaxComparisons(const int n) const;

    std::deque<int> deq_;
    std::vector<int> vec_;
    std::list<int> list_;

    int maxComparisons_;
    int numComparisons_;

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#include "PmergeMe.tpp"

#endif