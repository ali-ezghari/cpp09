#pragma once

#include <iterator>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <utility>
#include <math.h>
#include <iomanip>
#include <limits>
class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    static void mergeInsertionSort(std::vector<int> vecList, std::deque<int> deqList);

    static std::vector<int> PmergeMeVec(std::vector<int> &list);
    static std::deque<int> PmergeMeDeq(std::deque<int> &list);
};

