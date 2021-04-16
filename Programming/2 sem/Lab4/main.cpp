#include <iostream>
#include <iterator>
#include <vector>
namespace boo {
    template<class InputIterator, class Predicate>
    bool all_of(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first)
            if (!pred(*first))
                return false;
        return true;
    }

    template<class InputIterator, class Predicate>
    bool any_of(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first)
            if (pred(*first))
                return true;
        return false;
    }

    template<class InputIterator, class Predicate>
    bool none_of(InputIterator first, InputIterator last, Predicate pred) {
        return !all_of(first, last, pred);
    }

    template<class InputIterator, class Predicate>
    bool one_of(InputIterator first, InputIterator last, Predicate pred) {
        bool flag = false;
        for (; first != last; ++first) {
            if (pred(*first) && !flag)
                flag = true;
            else if (pred(*first) && flag)
                return false;
        }
        return flag;
    }

    template <class InputIterator>
    bool is_sorted(InputIterator first, InputIterator last) {
        ++first;
        if (*first >= *(first - 1)){
            for (; first != last; ++first) {
                if (*first >= *(first - 1))
                    continue;
                else
                    return false;
            }
            return true;
        } else{
            for (; first != last; ++first) {
                if (*first <= *(first - 1))
                    continue;
                else
                    return false;
            }
            return true;
        }
    }

    template<class InputIterator, class Predicate>
    bool is_partitioned(InputIterator first, InputIterator last, Predicate pred) {
        bool flag = true;
        InputIterator fr = first;
        InputIterator ls = last;
        if (first == last)
            return flag;
        for (; first != last; ++first)
            if (!pred(*first))
                break;
        ++first;
        for (; first != last; ++first)
            if (pred(*first))
                flag = false;
        if (flag)
            return flag;
        flag = true;
        last = ls;
        first = fr;
        for (; last != first; --last)
            if (!pred(*last))
                break;
        --last;
        for (; last != first; --last)
            if (pred(*last))
                flag = false;
        return flag;
    }

    template<class InputIterator, class Find>
    auto find_not(InputIterator first, InputIterator last, const Find& find) {
        for (; first != last; ++first)
            if (*first != find)
                return *first;
        return *last;
    }
}

int main(){
    std::vector<double> array {1.25, 2.45, 3, 4, 5, 7, 8};
    for (auto &i:array) {
        std::cout << i << " ";
    }
    if (boo::one_of(array.begin(), array.end(), [](int i){return i % 3 == 0;})){
        std::cout << std::endl << "3 " ;
    }
    std::cout << boo::find_not(array.begin(), array.end(), 1.25) << "\n\n";

    std::vector<int> digits{5, 4, 3, 2, 0, 1};

    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: " << std::boolalpha
              << boo::is_sorted(digits.begin(), digits.end()) << '\n';

    std::sort(std::begin(digits), std::end(digits));

    for (auto i : digits) std::cout << i << ' ';
    std::cout << ": is_sorted: "
              << boo::is_sorted(digits.begin(), digits.end()) << '\n';
    std::vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    auto is_even = [](int i){ return i % 2 == 0; };
    auto is_odd = [](int i){return i % 2 != 0;};
    std::cout.setf(std::ios_base::boolalpha);
    std::cout << boo::is_partitioned(v.begin(), v.end(), is_even) << '\n';

    std::partition(v.begin(), v.end(), is_even);
    for (auto &i:v) {
        std::cout << i << " ";
    }
    std::cout << "\n" << boo::is_partitioned(v.begin(), v.end(), is_even) << '\n';

    std::reverse(v.begin(), v.end());
    for (auto &i:v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << boo::is_partitioned(v.begin(), v.end(), is_even) << '\n';
    std::cout << boo::is_partitioned(v.rbegin(), v.rend(), is_even) << '\n';
    return 0;
}