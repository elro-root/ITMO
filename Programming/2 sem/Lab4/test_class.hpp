//
// Created by Patrik Duksin on 2021-04-17.
//

#ifndef LAB4_TEST_CLASS_HPP
#define LAB4_TEST_CLASS_HPP
template<class T>
class Vector {
private:
    T *arr;
    int n_;
public:
    Vector(int n = 1) {
        arr = new T[n];
        n_ = n;
    }
    ~Vector() {
        delete arr;
    }

    T &operator[](int index) {
        if (index > n_ || index < 0) {
            throw std::out_of_range("Error!");
        }
        return arr[index];
    }

    class Iterator {
    private:
        T *cur;
    public:
        Iterator(T *first) {
            cur = first;
        }

        Iterator &operator= (const Iterator &a) {
            cur = a.cur;
            return *this;
        }

        const T &operator*() {
            return *cur;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            cur++;
            return tmp;
        }
        Iterator operator--(int) {
            Iterator tmp = *this;
            cur--;
            return tmp;
        }

        Iterator &operator++() {
            ++cur;
            return *this;
        }

        Iterator &operator--() {
            --cur;
            return *this;
        }

        T &operator+(int n) {
            return *(cur + n);
        }

        T &operator-(int n) {
            return *(cur - n);
        }

        bool operator==(const Iterator &it) {
            return cur == it.cur;
        }

        bool operator!=(const Iterator &it) {
            return cur != it.cur;
        }
    };

    Iterator begin() const {
        return arr;
    }

    Iterator end() const {
        return arr + n_;
    }
};
#endif //LAB4_TEST_CLASS_HPP
