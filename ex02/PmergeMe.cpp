
#include "PmergeMe.hpp"

#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cassert>
#include <algorithm>

#include <iostream>


////////// public //////////

PmergeMe::PmergeMe(int argc, char** argv)
  : numComparisons_(0)
{
  populate(argc, argv);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort()
{
  fordJohnson(deq_, deq_.size(), 1);
  assert(isSorted(deq_.begin(), deq_.end()));
  assert(numComparisons_ <= maxComparisons_);
  numComparisons_ = 0;
  
  fordJohnson(vec_, vec_.size(), 1);
  assert(isSorted(vec_.begin(), vec_.end()));
  assert(numComparisons_ <= maxComparisons_);

  // fordJohnsonList(list_.size(), 1);
}

////////// private //////////

void PmergeMe::populate(int argc, char** argv)
{
  for (int i = 1; i < argc; ++i)
  {
    int current = 0;
    std::istringstream iss(argv[i]);
    iss >> current;
    if (iss.fail() || !iss.eof() || current < 0)
    {
      throw std::runtime_error(std::string("invalid input: ") + argv[i]);
    }
    list_.push_back(current);
    deq_.push_back(current);
    vec_.push_back(current);
    maxComparisons_ = calculateMaxComparisons(deq_.size());
  }
}

void PmergeMe::updateJacobsthal(int& currJacobsthal, int& prevJacobsthal)
{
  int temp = currJacobsthal;
  currJacobsthal = 2 * prevJacobsthal + currJacobsthal;
  prevJacobsthal = temp;
}

int PmergeMe::getCurrElementIdx(const int currJacobsthal, const int numPendingElements)
{
  return currJacobsthal - 2 > numPendingElements - 1 ? numPendingElements - 1 : currJacobsthal - 2;
}
































// ////////////// Ford Johnson List /////////////////

// void PmergeMe::fordJohnsonList(const int numElements, const int sizeElements)
// {
//   // std::cout << "fordJohnsonList(): sizeElements: " << sizeElements << " numElements: " << numElements << '\n';
//   if (numElements == 1)
//   {
//     return;
//   }
//   pairWiseSortList(numElements, sizeElements);
//   fordJohnsonList(numElements / 2, sizeElements * 2);
//   binaryInsertionList(numElements, sizeElements);
// }

// int PmergeMe::getSignificantInt(std::list<int>::const_iterator element, const int sizeElements) const
// {
//   std::advance(element, sizeElements - 1);
//   return *element;
// }

// void PmergeMe::pairWiseSortList(const int numElements, const int sizeElements)
// {
//   // std::cout << "list before pair wise sorting: ";
//   // printList(list_, sizeElements, numElements);
//   // std::cout << '\n';

//   std::list<int>::iterator left = list_.begin();
//   std::list<int>::iterator right = list_.begin();
//   std::advance(right, sizeElements);

//   for (int i = 0; i < numElements / 2; ++i)
//   {
//     std::list<int>::iterator newLeft = left;
//     std::advance(newLeft, sizeElements * 2);
//     std::list<int>::iterator newRight = right;
//     std::advance(newRight, sizeElements * 2);

//     ++numComparisonsList_;
//     if (getSignificantInt(left, sizeElements) > getSignificantInt(right, sizeElements))
//     {
//       std::list<int>::iterator endRight = right;
//       std::advance(endRight, sizeElements);
//       list_.splice(left, list_, right, endRight);
//     }

//     // std::cout << "*left: " << *left << '\n';
//     // std::cout << "*right: " << *right << '\n';
//     left = newLeft;
//     right = newRight;
//   }

//   // std::cout << "list after pair wise sorting: ";
//   // printList(list_, sizeElements, numElements);
//   // std::cout << '\n';
// }

// void PmergeMe::binaryInsertionList(const int numElements, const int sizeElements)
// {
//   std::cout << "\nentering binaryInsertionList:\n";

//   std::list<int> mainChain;
//   std::list<int> bChain;
//   std::list<std::list<int>::iterator> rightBounds;

//   std::cout << "list_: "; printList(list_, sizeElements, numElements); std::cout << '\n';

//   // populate mainChain, bChain, and list with iterators to partners
//   for (int i = 0; i < numElements; ++ i)
//   {
//     std::list<int>::iterator endElement = list_.begin();
//     std::advance(endElement, sizeElements);
//     if (i % 2 == 0)
//     {
//       bChain.splice(bChain.end(), list_, list_.begin(), endElement);
//     }
//     else
//     {
//       rightBounds.push_back(list_.begin());
//       mainChain.splice(mainChain.end(), list_, list_.begin(), endElement);
//     }
//   }

//   std::cout << "mainChain: "; printList(mainChain, sizeElements, numElements); std::cout << '\n';
//   std::cout << "bChain: "; printList(bChain, sizeElements, numElements); std::cout << '\n';
//   std::cout << "rightBounds: "; printList(rightBounds); std::cout << '\n';

//   // prepend first bChain element to mainChain
//   std::list<int>::iterator endElement = bChain.begin();
//   std::advance(endElement, sizeElements);
//   mainChain.splice(mainChain.begin(), bChain, bChain.begin(), endElement);
//   updateJacobsthal();

//   // insert from bChain into mainChain
//   std::list<int>::iterator rightBound = *rightBounds.begin();
//   std::advance(rightBound, sizeElements * (currJacobsthal_ - prevJacobsthal_));
//   std::list<int>::iterator subsequenceBegin = bChain.begin();
//   std::advance(subsequenceBegin, sizeElements * (currJacobsthal_ - prevJacobsthal_));
//   std::list<int>::iterator current = subsequenceBegin;
//   std::list<int>::iterator subsequenceEnd = bChain.begin();

//   while (true)
//   {
    
//     std::cout << "mainChain: "; printList(mainChain, sizeElements, numElements); std::cout << '\n';
//     std::cout << "bChain: "; printList(bChain, sizeElements, numElements); std::cout << '\n';
//     std::cout << "rightBounds: "; printList(rightBounds); std::cout << '\n';

//     while (current != subsequenceEnd)
//     {
//       std::list<int>::iterator insertPos = binarySearchList(mainChain, );
//       std::list<int>::iterator currentEnd = current;
//       std::advance(currentEnd, sizeElements);
//       std::list<int>::iterator next = current;
//       std::advance(next, -sizeElements);
//       mainChain.splice(insertPos, bChain, current, currentEnd);
//       current = next;
//       std::advance(rightBound, -1);
//     }
//     updateJacobsthal();
//     if (prevJacobsthal_ >= numElements)
//     {
//       break;
//     }
//     subsequenceEnd = subsequenceBegin;
//     std::advance(subsequenceBegin, sizeElements * (currJacobsthal_ - prevJacobsthal_));
//     current = subsequenceBegin;
//     std::advance(rightBound, sizeElements * (currJacobsthal_ - prevJacobsthal_));
//   }


//   std::cout << "\nexiting binaryInsertionList\n";
//   std::cout << "mainChain: "; printList(mainChain, sizeElements, numElements); std::cout << '\n';
//   std::cout << "bChain: "; printList(bChain, sizeElements, numElements); std::cout << '\n';
//   std::cout << "rightBounds: "; printList(rightBounds); std::cout << '\n';

//   list_.splice(list_.begin(), mainChain);
// }

// std::list<int>::iterator binarySearchList(std::list<int> mainChain, std::list<int>::iterator rightBound, const int target, const int sizeElements)
// {
//   std::list<int>::iterator leftBound = mainChain.begin();

//   while (leftBound < rightBound)
//   {
//     std::list<int>::iterator mid = 
//   }
// }

// std::list<int>::iterator findMiddleSubList(std::list<int> mainChain, std::list<int>::iterator rightBound, const int sizeElements)
// {
//   std::list<int>::iterator fast = mainChain.begin();
//   std::list<int>::iterator slow = mainChain.begin();

//   while (fast != )
// }


///////////////// validation ////////////////////////

double PmergeMe::log2(const double x) const
{
  return std::log(x) / std::log(2.0);
}

int PmergeMe::calculateMaxComparisons(const int n) const
{
  int sum = 0;
  for (int k = 1; k <= n; ++k)
  {
    sum += std::ceil(log2((3.0 / 4.0) * k));
  }
  return sum;
}


//////////////// debugging //////////////////////

void PmergeMe::printDeque(const std::deque<int>& deq, const int sizeElements, const int numElements) const
{
  int elementMember = 1;
  int num = 1;
  for (std::deque<int>::const_iterator it = deq.begin(); it != deq.end(); ++it)
  {
    if (elementMember == 1)
    {
      std::cout << '[';
    }
    std::cout << *it;
    if (elementMember == sizeElements)
    {
      std::cout << ']';
    }
    std::cout << ' ';
    
    if (elementMember == sizeElements)
    {
      if (num == numElements)
      {
        break;
      }
      ++num;
      elementMember = 1;
    }
    else
    {
      ++elementMember;
    }
  }
}

void PmergeMe::printList(const std::list<int>& currList, const int sizeElements, const int numElements) const
{
  int elementMember = 1;
  int num = 1;
  for (std::list<int>::const_iterator it = currList.begin(); it != currList.end(); ++it)
  {
    if (elementMember == 1)
    {
      std::cout << '[';
    }
    std::cout << *it;
    if (elementMember == sizeElements)
    {
      std::cout << ']';
    }
    std::cout << ' ';
    
    if (elementMember == sizeElements)
    {
      if (num == numElements)
      {
        break;
      }
      ++num;
      elementMember = 1;
    }
    else
    {
      ++elementMember;
    }
  }
}

void PmergeMe::printList(const std::list<std::list<int>::iterator>& currList) const
{
  for (std::list<std::list<int>::iterator>::const_iterator it = currList.begin(); it != currList.end(); ++it)
  {
    std::cout << **it << ' ';
  }
}