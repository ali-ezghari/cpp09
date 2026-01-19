#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};
PmergeMe::PmergeMe(const PmergeMe &other)
{
    (void)other;
}
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    (void)(other);
    return *this;
}
PmergeMe::~PmergeMe() {};

template <typename T>

void printList(T &list)
{
    for (std::vector<int>::const_iterator it = list.begin(); it != list.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

int jackobsthalNum(int index)
{
    return round((pow(2, index) - pow(-1, index)) / 3);
}

std::vector<int> PmergeMe::PmergeMeVec(std::vector<int> &list)
{
    if (list.size() <= 1)
        return (list);
    if (list.size() == 2)
    {
        if (list[0] > list[1])
            std::swap(list[0], list[1]);
        return (list);
    }
    std::vector<int> winners;
    std::vector<int> losers;
    std::vector<std::pair<int, int> > pairs;

    for (size_t i = 0; i + 2 <= list.size(); i += 2)
    {
        winners.push_back(list[i] > list[i + 1] ? list[i] : list[i + 1]);
        losers.push_back(list[i] > list[i + 1] ? list[i + 1] : list[i]);
        pairs.push_back(std::make_pair(losers.back(), winners.back()));
    }

    // ? resursive part : we have to sort the winners array with our ford johnson algo
    winners = PmergeMeVec(winners);

    // labeling
    losers.clear();
    for (size_t i = 0; i < winners.size(); i++)
    {
        for (std::vector<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            if (winners[i] == it->second)
            {
                losers.push_back(it->first);
                break;
            }
        }
    }
    // main chain
    std::vector<int> mainChain = winners;

    mainChain.insert(mainChain.begin(), *losers.begin());
    losers.erase(losers.begin());
    winners.clear(); // for cleaning

    // ? inserting elements into mainChain with jackobsthal sequence
    for (int index = 3; index < 10; index++)
    {
        int jackNum = jackobsthalNum(index);
        int diff = jackobsthalNum(index) - jackobsthalNum(index - 1);

        for (int i = 0; i < diff; i++)
        {
            size_t listIndex = jackNum - i - 1; // jackNum - i - 1 =>  - 1 means (we previously moved b1 from losers to mainChain so we take into account that its b1 and its already moved 
            //     listIndex = losers.size() - 1;
            // mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), listIndex), listIndex);
            std::cout << listIndex << " ";
        }
    }
    if (list.size() % 2 != 0)
        mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), list.back()), list.back());

    return mainChain;
}

std::deque<int> PmergeMe::PmergeMeDeq(std::deque<int> &list)
{
    if (list.size() <= 1)
        return (list);
    if (list.size() == 2)
    {
        if (list[0] > list[1])
            std::swap(list[0], list[1]);
        return (list);
    }
    std::deque<int> winners;
    std::deque<int> losers;
    std::deque<std::pair<int, int> > pairs;

    for (size_t i = 0; i + 2 <= list.size(); i += 2)
    {
        winners.push_back(list[i] > list[i + 1] ? list[i] : list[i + 1]);
        losers.push_back(list[i] > list[i + 1] ? list[i + 1] : list[i]);
        pairs.push_back(std::make_pair(losers.back(), winners.back()));
    }

    // ? resursive part : we have to sort the winners array with our ford johnson algo
    winners = PmergeMeDeq(winners);

    // labeling
    losers.clear();
    for (size_t i = 0; i < winners.size(); i++)
    {
        for (std::deque<std::pair<int, int> >::const_iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            if (winners[i] == it->second)
            {
                losers.push_back(it->first);
                break;
            }
        }
    }
    // main chain
    std::deque<int> mainChain = winners;

    mainChain.insert(mainChain.begin(), *losers.begin());
    losers.erase(losers.begin());
    winners.clear(); // for cleaning

    // ? inserting elements into mainChain
    for (size_t i = 0; i < losers.size(); i++)
        mainChain.insert(lower_bound(mainChain.begin(), mainChain.end(), losers[i]), losers[i]);
    if (list.size() % 2 != 0)
        mainChain.insert(lower_bound(mainChain.begin(), mainChain.end(), list.back()), list.back());

    return (mainChain);
}

void PmergeMe::mergeInsertionSort(std::vector<int> vecList, std::deque<int> deqList)
{
    clock_t start, end;
    double time_spent;

    std::cout << "Before: ";
    printList(vecList);

    start = clock();
    vecList = PmergeMeVec(vecList);
    end = clock();

    std::cout << "\nAfter: ";
    printList(vecList);
    time_spent = 1e6 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vecList.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << time_spent << " us\n";

    start = clock();
    deqList = PmergeMeDeq(deqList);
    end = clock();
    time_spent = 1e6 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << deqList.size() << " elements with std::deque : " << std::fixed << std::setprecision(5) << time_spent << " us\n";
}