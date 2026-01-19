// using namespace std;




// void PmergeMe(vector<int> &list)
// {
//     clock_t start, end;
//     double time_spent;
//     vector<int> result;

//     cout << "Before: ";
//     printList(list);

//     start = clock();
//     result = PmergeMeExec(list);
//     end = clock();

//     cout << "\nAfter: ";
//     printList(result);
//     cout << "Tested With is_sorted() => " << (::is_sorted(result) ? "Sorted ✓" : "Not Sorted❌") << std::endl;
//     time_spent = static_cast<double>(end - start) / CLOCKS_PER_SEC;
//     cout << "Time to process a range of " << list.size() << " elements with std::vector : " << std::fixed << std::setprecision(5) << time_spent << " us\n";
// }

// int main(int ac, char *av[])
// {
//     vector<int> list;
//     vector<int> result;

//     for (int i = 1; i < ac; i++)
//     {
//         list.push_back(std::atoi(av[i]));
//     }
//     PmergeMe(list);

//     return 0;
// }
