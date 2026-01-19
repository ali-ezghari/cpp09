#pragma once

#include <iterator>
#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
#include <utility>
#include <math.h>
#include <iomanip>

template <typename T>

class PmergeMe
{
public:
    T List;
    std::vector<int> sortedVec;
    std::deque<int> sortedDeq;

    PmergeMe(T &list);

    void printList(T &list)
    {
        for (vector<int>::const_iterator it = list.begin(); it != list.end(); it++)
            cout << *it << " ";
        cout << endl;
    }

    bool is_sorted(T &list)
    {
        if (list.empty())
            return true;
        int prev = list[0];
        for (size_t i = 1; i < list.size(); i++)
        {
            if (prev > list[i])
                return false;
            prev = list[i];
        }
        return true;
    }

    // void PmergeMe(T &list)
    {
        clock_t start, end;
        double time_spent;

        cout << "Before: ";
        printList(list);

        start = clock();
        result = PmergeMeVec(list);
        end = clock();

        cout << "\nAfter: ";
        printList(result);
        time_spent = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        cout << "Time to process a range of " << list.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << time_spent << " us\n";
        
        start = clock();
        result = PmergeMeDeq(list);
        end = clock();
        cout << "Time to process a range of " << list.size() << " elements with std::deque : " << std::fixed << std::setprecision(5) << time_spent << " us\n";
    }

    void PmergeMeVec(vector<int> list);

    ~PmergeMe();
};

void PmergeMe::PmergeMeVec(std::vector<int> &list){}

template <typename T>

PmergeMe<T>::PmergeMe(T &list) : List(list)
{
}

template <typename T>

PmergeMe<T>::~PmergeMe()
{
}
