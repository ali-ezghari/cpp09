#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <math.h>
#include <iomanip>

using namespace std;

void printList(vector<int> &list)
{
    for (vector<int>::const_iterator it = list.begin(); it != list.end(); it++)
        cout << *it << " ";
    cout << endl;
}

vector<int> PmergeMeExec(vector<int> &list)
{
    if (list.size() <= 1)
        return (list);

    vector<int> winners;
    vector<int> losers;
    vector<std::pair<int, int>> pairs;

    for (size_t i = 0; i + 2 <= list.size(); i += 2)
    {
        winners.push_back(list[i] > list[i + 1] ? list[i] : list[i + 1]);
        losers.push_back(list[i] > list[i + 1] ? list[i + 1] : list[i]);
        pairs.push_back(std::make_pair(losers.back(), winners.back()));
    }

    // ? resursive part : we have to sort the pairs with our ford johnson algo
    sort(winners.begin(), winners.end());

    // labeling
    losers.clear();
    for (size_t i = 0; i < winners.size(); i++)
    {
        for (vector<std::pair<int, int>>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
        {
            if (winners[i] == it->second)
            {
                losers.push_back(it->first);
                continue;
            }
        }
    }

    // main chains
    vector<int> mainChain = winners;

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

void PmergeMe(vector<int> &list)
{
    clock_t start, end;
    double time_spent;
    vector<int> result;

    cout << "Before: ";
    printList(list);

    start = clock();
    result = PmergeMeExec(list);
    end = clock();

    cout << "\nAfter: ";
    printList(result);
    time_spent = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Time to process a range of " << list.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << time_spent << " us\n";
}

// bool is_sorted(vector<int> &list)
// {
//     if (list.empty())
//         return true;
//     int prev = list[0];
//     for (size_t i = 1; i < list.size(); i++)
//     {
//         if (prev > list[i])
//             return false;
//         prev = list[i];
//     }
//     return true;
// }

int main(int ac, char *av[])
{
    vector<int> list;
    vector<int> result;

    for (int i = 1; i < ac; i++)
    {
        list.push_back(std::atoi(av[i]));
    }
    PmergeMe(list);

    return 0;
}
