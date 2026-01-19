#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
    std::vector<int> veclist;
    std::deque<int> deqList;
    long long num;

    for (int i = 1; i < ac; i++)
    {
        num = std::atoll(av[i]);
        if (num > std::numeric_limits<int>::max() || num < std::numeric_limits<int>::min())
        {
            std::cout << "Error!\n";
            return 1;
        }
        veclist.push_back(std::atoi(av[i]));
        deqList.push_back(std::atoi(av[i]));
    }
    PmergeMe::mergeInsertionSort(veclist, deqList);

    return 0;
}
