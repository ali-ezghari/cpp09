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

void printList(const T &list)
{
    for (typename T::const_iterator it = list.begin(); it != list.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

static int jackobsthalNum(int index)
{
    return round((pow(2, index) - pow(-1, index)) / 3);
}

template <typename T>
void mainChainInsertion(T &mainChain, T &losers)
{
    size_t count = 0;
    size_t listIndex = 0;
    size_t diff, jackNum;

    if (losers.size() == 1)
    {
        mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), losers[0]), losers[0]);
        return ;
    }

    for (size_t index = 3; count < losers.size(); index++)
    {
        diff = jackobsthalNum(index) - jackobsthalNum(index - 1);
        jackNum = jackobsthalNum(index);

        for (size_t k = 0; k < diff; k++)
        {
            if (count >= losers.size())
                break;
            listIndex = jackNum - k - 2;
            if (listIndex >= losers.size())
            {
                listIndex = losers.size() - 1; // when jackobsthal numbers are out of bound
                jackNum = jackobsthalNum(index - 1) - 2;
                while (listIndex > jackNum)
                {
                    mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), losers[listIndex]), losers[listIndex]);
                    listIndex--;
                    count++;
                }
                break;
            }
            mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), losers[listIndex]), losers[listIndex]);
            count++;
        }
    }
}

std::vector<int> PmergeMe::PmergeMeVec(std::vector<int> &list)
{
    if (list.size() <= 1)
        return (list);

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
        for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            if (winners[i] == it->second)
            {
                losers.push_back(it->first);
                pairs.erase(it);
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
    mainChainInsertion(mainChain, losers);

    if (list.size() % 2 != 0)
        mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), list.back()), list.back());

    return (mainChain);
}

std::deque<int> PmergeMe::PmergeMeDeq(std::deque<int> &list)
{
    if (list.size() <= 1)
        return (list);

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
        for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            if (winners[i] == it->second)
            {
                losers.push_back(it->first);
                pairs.erase(it);
                break;
            }
        }
    }

    // main chain
    std::deque<int> mainChain = winners;

    mainChain.insert(mainChain.begin(), *losers.begin());
    losers.erase(losers.begin());
    winners.clear(); // for cleaning

    // ? inserting elements into mainChain with jackobsthal sequence
    mainChainInsertion(mainChain, losers);

    if (list.size() % 2 != 0)
        mainChain.insert(std::lower_bound(mainChain.begin(), mainChain.end(), list.back()), list.back());

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

    (void)deqList;
    start = clock();
    deqList = PmergeMeDeq(deqList);
    end = clock();
    time_spent = 1e6 * (end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << deqList.size() << " elements with std::deque : " << std::fixed << std::setprecision(5) << time_spent << " us\n";
}