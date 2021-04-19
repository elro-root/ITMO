#include <iostream>
#include <vector>
#include "algorithms.hpp"
#include "test_class.hpp"

int main(){
    std::vector<double> array {-1.25, 2.45, 3, 4, 5, 7, 8, 11};

    std::cout << "vector: ";
    for (auto &i:array) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    if (boom::all_of(array.begin(), array.end(), [](int i){return i > 0;}))
        std::cout << "all of is bigger than 0" << std::endl;
    else
        std::cout << "all of isn't bigger than 0" << std::endl;
    if (boom::any_of(array.begin(), array.end(), [](int i){return i > 0;}))
        std::cout << "any of is bigger than 0" << std::endl;
    else
        std::cout << "any of isn't bigger than 0" << std::endl;
    if (boom::none_of(array.begin(), array.end(), [](int i){return i > 0;}))
        std::cout << "none of is bigger than 0" << std::endl;
    else
        std::cout << "none of isn't bigger than 0" << std::endl;

    if (boom::one_of(array.begin(), array.end(), boom::unary_predicate<double>))
        std::cout << "one of is bigger than 10" << std::endl;
    else
        std::cout << "no one of is bigger than 10" << std::endl;

    if (boom::is_sorted(array.begin(), array.end()))
        std::cout << "sorted" << std::endl;
    else
        std::cout << "not sorted" << std::endl;

    if (boom::is_partitioned(array.begin(), array.end(), [](int i){return i > 4 == 0;}))
        std::cout << "partitioned" << std::endl;
    else
        std::cout << "not partitioned" << std::endl;

    std::cout << "find not: " << boom::find_not(array.begin(), array.end(), 4) << std::endl;

    std::cout << "find back: " << boom::find_backward(array.begin(), array.end(), 4) << std::endl;

    if (boom::is_palindrome(array.begin(), array.end(), boom::binary_predicate<double>))
        std::cout << "palindrome" << std::endl;
    else
        std::cout << "not palindrome" << std::endl;

    Vector<int> a(3);
    a[0] = 5;
    a[1] = 9;
    a[2] = 41;
    std::cout << "test class" << std::endl;

    if (boom::all_of(a.begin(), a.end(), [](int i){return i > 6;}))
        std::cout << "all of is bigger than 6" << std::endl;
    else
        std::cout << "all of isn't bigger than 6" << std::endl;

    if (boom::any_of(a.begin(), a.end(), [](int i){return i > 0;}))
        std::cout << "any of is bigger than 0" << std::endl;
    else
        std::cout << "any of isn't bigger than 0" << std::endl;
    if (boom::none_of(a.begin(), a.end(), [](int i){return i > 0;}))
        std::cout << "none of is bigger than 0" << std::endl;
    else
        std::cout << "none of isn't bigger than 0" << std::endl;

    if (boom::one_of(a.begin(), a.end(), boom::unary_predicate<double>))
        std::cout << "only one of is bigger than 10" << std::endl;
    else
        std::cout << "no only one of is bigger than 10" << std::endl;

    if (boom::is_sorted(a.begin(), a.end()))
        std::cout << "sorted" << std::endl;
    else
        std::cout << "not sorted" << std::endl;

    if (boom::is_partitioned(a.begin(), a.end(), [](int i){return i > 4 == 0;}))
        std::cout << "partitioned" << std::endl;
    else
        std::cout << "not partitioned" << std::endl;

    std::cout << "find not: " << boom::find_not(a.begin(), a.end(), 4) << std::endl;

    std::cout << "find back: " << boom::find_backward(a.begin(), a.end(), 41) << std::endl;

    if (boom::is_palindrome(a.begin(), a.end(), boom::binary_predicate<double>))
        std::cout << "palindrome" << std::endl;
    else
        std::cout << "not palindrome" << std::endl;

    return 0;
} // approved