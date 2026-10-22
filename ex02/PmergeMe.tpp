#include <algorithm>
#include <utility>
#include <iostream>
#include <cassert>

template <typename it>
bool PmergeMe::isSorted(it first, it last)
{
	bool result = true;
	if (first == last)
	{
		return result;
	}
	for (it next = first + 1; next != last; ++first, ++next)
	{
		if (*next < *first)
		{
			std::cerr << "isSorted: " << *first << " > " << *next << '\n';
			result = false;
		}
	}
	return result;
}

template <typename it>
int getSignificantInt(it element, const int sizeElements)
{
  element += sizeElements - 1;
  return *element;
}

template <typename it>
void swapElements(it leftIt, it rightIt, const int sizeElements)
{
  it endIt = rightIt + sizeElements;
  std::rotate(leftIt, rightIt, endIt);
}

template <typename it, typename container>
void populateContainers(it iter, container& mainChain, container& pending, container& bounds,
                              const int numElements, const int sizeElements)
{
  int bound = 3;
  for (int i = 1; i <= numElements; ++i)
  {
    if (i == 1 || i % 2 == 0)
    {
      mainChain.insert(mainChain.end(), iter, iter + sizeElements);
    }
    else
    {
      pending.insert(pending.end(), iter, iter + sizeElements);
      bounds.push_back(bound++);
    }
    iter += sizeElements;
  }
}

template <typename container>
typename container::iterator getCurrentIt(container& d, const int currElementIdx, const int sizeElements)
{
  return d.begin() + currElementIdx * sizeElements;
}

template <typename container>
void updateBounds(container& bounds, const int insertPos)
{
  for (std::size_t i = bounds.size(); i > 0; --i)
  {
    if (insertPos <= bounds[i - 1])
    {
      bounds[i - 1] += 1;
    }
    else
    {
      break;
    }
  }
}

template <typename container>
std::pair<int, typename container::iterator> PmergeMe::binarySearch(container& mainChain, const int value, const int rightBound, const int sizeElements)
{
  int leftElement = 1;
  int rightElement = rightBound;

  while (leftElement < rightElement)
  {
    int midElement = leftElement + (rightElement - leftElement) / 2;
    ++numComparisons_;
    if (mainChain[midElement * sizeElements - 1] < value)
    {
      leftElement = midElement + 1;
    }
    else
    {
      rightElement = midElement;
    }
  }
  return std::make_pair(leftElement, mainChain.begin() + (leftElement - 1) * sizeElements);
}

template <typename it>
void PmergeMe::pairWiseSort(it leftIt, const int numElements, const int sizeElements)
{
  it rightIt = leftIt + sizeElements;
  for (int i = 0; i < numElements / 2; ++i)
  {
    ++numComparisons_;
    if (getSignificantInt(leftIt, sizeElements) > getSignificantInt(rightIt, sizeElements))
    {
      swapElements(leftIt, rightIt, sizeElements);
    }
    leftIt += (2 * sizeElements);
    rightIt += (2 * sizeElements);
  }
}

template <typename container>
void PmergeMe::insertElements(container& mainChain, container& pending, container& bounds, const int sizeElements)
{
  int numPendingElements = pending.size() / sizeElements;
  int currJacobsthal = 3;
  int prevJacobsthal = 1;
  int currElementIdx = getCurrElementIdx(currJacobsthal, numPendingElements);

  for (int n = numPendingElements; n > 0; --n)
  {
    typename container::iterator currIt = getCurrentIt(pending, currElementIdx, sizeElements);
    std::pair<int, typename container::iterator> result = binarySearch(mainChain, getSignificantInt(currIt, sizeElements), bounds[currElementIdx], sizeElements);
    mainChain.insert(result.second, currIt, currIt + sizeElements);
    updateBounds(bounds, result.first);
    --currElementIdx;
    if (currElementIdx == prevJacobsthal - 2)
    {
      updateJacobsthal(currJacobsthal, prevJacobsthal);
      currElementIdx = getCurrElementIdx(currJacobsthal, numPendingElements);
    }
  }
}

template <typename Container>
void PmergeMe::binaryInsertion(Container& cont, const int numElements, const int sizeElements)
{
  Container mainChain;
  Container pending;
  Container bounds;

  populateContainers(cont.begin(), mainChain, pending, bounds, numElements, sizeElements);
  insertElements(mainChain, pending, bounds, sizeElements);
  if (!isMainChainSorted(mainChain.begin(), numElements, sizeElements))
  {
  	printContainer(mainChain, sizeElements, numElements); std::cout << '\n';
  }
  std::swap(cont, mainChain);
  cont.insert(cont.end(), mainChain.begin() + numElements * sizeElements, mainChain.end());
}

template <typename container>
void PmergeMe::fordJohnson(container& cont, const int numElements, const int sizeElements)
{
  if (numElements == 1)
  {
    return;
  }
  pairWiseSort(cont.begin(), numElements, sizeElements);
  isPairWiseSorted(cont.begin(), numElements, sizeElements);
  fordJohnson(cont, numElements / 2, sizeElements * 2);
  binaryInsertion(cont, numElements, sizeElements);
}

template <typename Container>
void PmergeMe::printContainer(Container& cont) const
{
	for (typename Container::const_iterator it = cont.begin(); it != cont.end(); ++it)
	{
		std::cout << *it << ' ';
	}
}

//////////////// debugging //////////////////////

template <typename Container>
void PmergeMe::printContainer(Container& cont, const int sizeElements, const int numElements) const
{
  int elementMember = 1;
  int num = 1;
  for (typename Container::const_iterator it = cont.begin(); it != cont.end(); ++it)
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

template <typename Container>
void PmergeMe::printPairs(Container& cont, const int sizeElements, const int numElements) const
{
  int elementMember = 1;
  int num = 1;
  int pairMember = 1;
  for (typename Container::const_iterator it = cont.begin(); it != cont.end(); ++it)
  {
    if (elementMember == 1)
    {
      std::cout << '[';
    }
    std::cout << *it;
    if (elementMember == sizeElements)
    {
      std::cout << "] ";
      if (pairMember == 1)
      {
    	++pairMember;
      }
      else
      {
    	std::cout << '\n';
    	pairMember = 1;
      }
    }
    else
    {
      std::cout << ' ';
    }

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

template <typename it>
bool PmergeMe::isPairWiseSorted(it left, const int numElements, const int sizeElements)
{
	it right = left + sizeElements;
	bool result = true;
	for (int n = 0; n < numElements / 2; ++n)
	{
		if (getSignificantInt(left, sizeElements) > getSignificantInt(right, sizeElements))
		{
			std::cerr << "isPairWiseSorted: " << getSignificantInt(left, sizeElements) << " > " << getSignificantInt(right, sizeElements) << '\n';
			result = false;
		}
		left += 2 * sizeElements;
		right += 2 * sizeElements;
	}
	return result;
}

template <typename it>
bool PmergeMe::isMainChainSorted(it left, const int numElements, const int sizeElements)
{
	it right = left + sizeElements;
	bool result = true;
	for (int n = 0; n < numElements / 2; ++n)
	{
		if (getSignificantInt(left, sizeElements) > getSignificantInt(right, sizeElements))
		{
			std::cerr << "isMainChainSorted: " << getSignificantInt(left, sizeElements) << " > " << getSignificantInt(right, sizeElements) << '\n';
			result = false;
		}
		left += 2 * sizeElements;
		right += 2 * sizeElements;
	}
	return result;
}