//
// Created by Patrik Duksin on 2021-04-17.
//

#ifndef LAB4_ALGORITHMS_HPP
#define LAB4_ALGORITHMS_HPP
namespace boom {
    template<class T>
    bool unary_predicate(const T &el) {
        return el > 10;
    }

    template<class T>
    bool binary_predicate(const T &l, const T &r) {
        return l == r;
    }

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
        for (; first != last; ++first)
            if (pred(*first))
                return false;
        return true;
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
        InputIterator tmp = first;
        ++first;
        if (*first >= *tmp){
            for (; first != last; ++first, ++tmp) {
                if (*first >= *tmp)
                    continue;
                else
                    return false;
            }
            return true;
        } else{
            for (; first != last; ++first, ++tmp) {
                if (*first <= *tmp)
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
    int find_not(InputIterator first, InputIterator last, const Find& find) {
        for (int i = 0; first != last; ++first, ++i)
            if (*first != find)
                return ++i;
        return 0;
    }

    template<class InputIterator, class Find>
    int find_backward(InputIterator first, InputIterator last, const Find& find){
        for (int i = 0; last != first; --last, ++i)
            if (*last == find)
                return i;
        return 0;
    }

    template<class InputIterator, class Predicate>
    bool is_palindrome(InputIterator begin, InputIterator end, Predicate p) {
        if(begin == end)
            return true;
        --end;
        while(begin != end) {
            if(!p(*begin, *end))
                return false;
            ++begin;
            if(begin == end)
                break;
            --end;
        }
        return true;
    }
}

#endif //LAB4_ALGORITHMS_HPP
