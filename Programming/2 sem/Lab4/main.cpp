#include <iostream>
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

    template<class InputIterator>
    const InputIterator &find_not(const InputIterator &first, const InputIterator &last,
                                  const InputIterator &find) {
        for (; first != last; ++first)
            if (first != find)
                return first;
        return last;
    }

    template<class InputIterator, class Predicate>
    bool is_partitioned(InputIterator first, InputIterator last, Predicate pred) {
        for (; first != last; ++first)
            if (!pred(*first))
                break;
        if (first == last)
            return true;
        ++first;
        for (; first != last; ++first)
            if (pred(*first))
                return false;
        return true;
    }
}

int main(){
    std::vector<int> array {1, 2, 3, 4, 5, 7, 8};
    for (auto &i:array) {
        std::cout << i << " ";
    }
    if (boo::one_of(array.begin(), array.end(), [](int i){return i % 3 == 0;})){
        std::cout << std::endl << "3" ;
    }
    return 0;
}