
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
  : numComparisonsList_(0)
  , numComparisonsDeque_(0)
  , currJacobsthal_(1)
  , prevJacobsthal_(1)
{
  populate(argc, argv);
}

PmergeMe::~PmergeMe() {}

void PmergeMe::sort()
{
  assert(calculateMaxComparisons(4) == 5);
  assert(calculateMaxComparisons(5) == 7);
  assert(calculateMaxComparisons(21) == 66);

  fordJohnsonDeque(deq_.size(), 1);
  // fordJohnsonList(list_.size(), 1);
  
  std::cout << "Max allowed comparisons: " << calculateMaxComparisons(deq_.size()) << "\nPerformed comparisons deque: " << numComparisonsDeque_ << "\n";
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
  }
  assert(deq_.size() == list_.size());
  assert(deq_.size() == static_cast<unsigned long>(argc - 1));
}

void PmergeMe::updateJacobsthal()
{
  int temp = currJacobsthal_;
  currJacobsthal_ = 2 * prevJacobsthal_ + currJacobsthal_;
  prevJacobsthal_ = temp;
}


//////////////// Ford Johnson Deque ////////////////////

void PmergeMe::fordJohnsonDeque(const int numElements, const int sizeElements)
{
  if (numElements == 1)
  {
    return;
  }
  std::cout << "Num elements: " << numElements << " size elements: " << sizeElements << '\n'
    << " deque currently: ";
  printDeque(deq_, sizeElements, numElements);
  std::cout << '\n';

  pairWiseSortDeque(numElements, sizeElements);
  fordJohnsonDeque(numElements / 2, sizeElements * 2);
  binaryInsertionDeque(numElements, sizeElements);
}

int PmergeMe::getSignificantIntDeque(std::deque<int>::const_iterator element, const int sizeElements)
{
  std::advance(element, sizeElements - 1);
  return *element;
}

void PmergeMe::swapElementsDeque(std::deque<int>::iterator leftIt, std::deque<int>::iterator rightIt, const int sizeElements)
{
  std::deque<int>::iterator endIt = rightIt + sizeElements;
  std::rotate(leftIt, rightIt, endIt);
}

void PmergeMe::pairWiseSortDeque(const int numElements, const int sizeElements)
{
  std::deque<int>::iterator leftIt = deq_.begin();
  std::deque<int>::iterator rightIt = leftIt + sizeElements;
  for (int i = 0; i < numElements / 2; ++i)
  {
    ++numComparisonsDeque_;
    if (getSignificantIntDeque(leftIt, sizeElements) > getSignificantIntDeque(rightIt, sizeElements))
    {
      swapElementsDeque(leftIt, rightIt, sizeElements);
    }
    leftIt += (2 * sizeElements);
    rightIt += (2 * sizeElements);
  }
}

void PmergeMe::populateDeques(std::deque<int>& main, std::deque<int>& pending, std::deque<int>& bounds,
                              const int numElements, const int sizeElements)
{
  std::deque<int>::iterator mainIt = deq_.begin() + sizeElements;
  std::deque<int>::iterator pendingIt = deq_.begin();
  main.insert(main.end(), pendingIt, pendingIt + sizeElements);
  int numPartner = 3;
  for (int i = 1; i < numElements / 2; ++i)
  {
    main.insert(main.end(), mainIt, mainIt + sizeElements);
    pending.insert(pending.end(), pendingIt, pendingIt + sizeElements);
    bounds.push_back(numPartner++);
  }
}

void PmergeMe::binaryInsertionDeque(const int numElements, const int sizeElements)
{
  std::deque<int> main;
  std::deque<int> pending;
  std::deque<int> bounds;

  populateDeques(main, pending, bounds, numElements, sizeElements);
  

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