#include <PmergeMe.hpp>

// void PmergeMe::

// void  PmergeMeVec(vector<int> &list)
// {
//     if (list.size() <= 1)
//         return (list);
//     if (list.size() == 2)
//     {
//         if (list[0] > list[1])
//             std::swap(list[0], list[1]);
//         return (list);
//     }
//     vector<int> winners;
//     vector<int> losers;
//     vector<std::pair<int, int>> pairs;

//     for (size_t i = 0; i + 2 <= list.size(); i += 2)
//     {
//         winners.push_back(list[i] > list[i + 1] ? list[i] : list[i + 1]);
//         losers.push_back(list[i] > list[i + 1] ? list[i + 1] : list[i]);
//         pairs.push_back(std::make_pair(losers.back(), winners.back()));
//     }

//     // ? resursive part : we have to sort the pairs with our ford johnson algo
//     // sort(winners.begin(), winners.end());
//     winners = PmergeMeExec(winners);

//     // labeling
//     losers.clear();
//     for (size_t i = 0; i < winners.size(); i++)
//     {
//         for (vector<std::pair<int, int>>::const_iterator it = pairs.begin(); it != pairs.end(); it++)
//         {
//             if (winners[i] == it->second)
//             {
//                 losers.push_back(it->first);
//                 continue;
//             }
//         }
//     }
//     // main chains
//     vector<int> mainChain = winners;

//     mainChain.insert(mainChain.begin(), *losers.begin());
//     losers.erase(losers.begin());
//     winners.clear(); // for cleaning

//     // ? inserting elements into mainChain
//     for (size_t i = 0; i < losers.size(); i++)
//         mainChain.insert(lower_bound(mainChain.begin(), mainChain.end(), losers[i]), losers[i]);
//     if (list.size() % 2 != 0)
//         mainChain.insert(lower_bound(mainChain.begin(), mainChain.end(), list.back()), list.back());
    
    
// }