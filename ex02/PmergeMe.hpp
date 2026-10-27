#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <list>
#include <vector>
#include <utility>
#include <ctime>

class PmergeMe
{
  public:
    PmergeMe(int argc, char** argv);
    ~PmergeMe();
    void sort();
    void printResult();

  private:
    void populate(int argc, char** argv);
    void updateJacobsthal(int& currJacobsthal, int& prevJacobsthal) const;
    int getCurrElementIdx(const int currJacobsthal, const int numPendingElements) const;
    double log2(const double x) const;
    int calculateMaxComparisons(const int n) const;

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
    template <typename Container>
    void printContainer(Container& cont) const;
    template <typename it>
    bool isSorted(it first, it last);
    template <typename it>
    int getSignificantInt(it element, const int sizeElements);
    template <typename it>
    void swapElements(it leftIt, it rightIt, const int sizeElements);
    template <typename it, typename container>
    void populateContainers(it iter, container& mainChain, container& pending, container& bounds,
                              const int numElements, const int sizeElements);
    template <typename container>
    typename container::iterator getCurrentIt(container& d, const int currElementIdx, const int sizeElements);

    std::vector<int> origin_;
    std::deque<int> deq_;
    std::vector<int> vec_;

    int maxComparisons_;
    int numComparisons_;

    clock_t startDeq_;
    clock_t endDeq_;
    clock_t startVec_;
    clock_t endVec_;
    double elapsedMicrosecondsDeq_;
    double elapsedMicrosecondsVec_;

    PmergeMe(const PmergeMe& other); // private and not implemented, since there is no reason to make a copy
    PmergeMe& operator=(const PmergeMe& other);
};

#include "PmergeMe.tpp"

#endif