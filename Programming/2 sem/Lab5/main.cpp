#include <iostream>
#include <algorithm>
#include <iterator>

template<class T>
class circular_buffer {
private:
    int m_capacity = 0;
    T *m_arr = new T[m_capacity];
    T *m_first, *m_last, *m_cur_first, *m_cur_last; // m_first и m_last указывают на первый последний и неизменимы
public:
    // Итератор
    class iter : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *p;
    public:
        iter() : p(nullptr) {}

        iter(T *p) : p(p) {}

        iter(const iter &it) : p(it.p) {}

        iter &operator+=(int x) {
            p += x;
            return *this;
        }

        iter &operator-=(int x) {
            p -= x;
            return *this;
        }

        iter operator++() {
            p++;
            return *this;
        }

        iter &operator--() {
            p--;
            return *this;
        }

        iter operator++(int) {
            iter tmp(*this);
            ++p;
            return tmp;
        }

        iter operator--(int) {
            iter tmp(*this);
            --p;
            return tmp;
        }

        auto operator-(const iter &it) {
            return (p - it.p);
        }

        iter operator+(int x) {
            return iter(p + x);
        }

        iter operator-(int x) {
            return iter(p - x);
        }

        T &operator*() const {
            return *p;
        }

        T *operator->() const {
            return p;
        }

        T &operator[](const int x) {
            return p[x];
        }

        bool operator==(const iter &x) const {
            return x.p == this->p;
        }

        bool operator!=(const iter &x) const {
            return x.p != this->p;
        }

        bool operator<(const iter &x) const {
            return x.p < this->p;
        }

        bool operator>(const iter &x) const {
            return x.p > this->p;
        }

        bool operator>=(const iter &x) const {
            return x.p >= this->p;
        }

        bool operator<=(const iter &x) const {
            return x.p <= this->p;
        }
    };


    // Конструктор по умолчанию, конструктор копирования и деструктор
    circular_buffer(int size_ = 0) {
        this->m_capacity = size_;
        this->m_first = &m_arr[0];
        this->m_last = &m_arr[m_capacity - 1];
        this->m_cur_first = &m_arr[0];
        this->m_cur_last= &m_arr[m_capacity - 1];
    }
    circular_buffer(const circular_buffer& buf) : m_capacity{buf.m_capacity}, m_arr{buf.m_arr}, m_cur_first{buf.m_cur_first},
    m_cur_last{buf.m_cur_last}, m_first{buf.m_first}, m_last{buf.m_last} {}

    ~circular_buffer() {
        delete[] m_arr;
    }

    iter begin() { // возвращает первый элемент
        return (m_arr);
    }
    iter end() {// возвращает последний элемент
        return iter(m_arr + m_capacity);
    }
    int capacity_buffer() const { // возвращает капасити
        return m_capacity;
    }

    void push_back(const T& value) { // вставка элемента в конец
        *m_cur_first = value;
        m_last == m_cur_first ? m_cur_first = m_first : m_cur_first++;
    }
    void push_front(const T& value) {// вставка элемента в начало
        *m_cur_last = value;
        m_first == m_cur_last ? m_cur_last = m_last : m_cur_last--;
    }
    void pop_back() { // удаление элемента с конца
        *m_cur_first = 0;
        m_cur_first == m_first ? m_cur_first = m_last : m_cur_first++;
    }
    void pop_front() { // удаление элемента с начала
        *m_cur_last = 0;
        m_cur_last == m_last ? m_cur_last = m_first : m_cur_last++;
    }
    T operator [] (int i) const { // возвращает i-ый член
        return m_arr[i % m_capacity];
    }
    void change_capacity(const int& value) {
        T* temp = new T[value];
        int size = std::min(m_capacity, value);
        for (int i = 0; i < size; ++i)
            temp[i] = m_arr[i];
        m_capacity = value;
        m_arr = new T[value];
        for (int i = 0; i < value; ++i)
            m_arr[i] = temp[i];
        m_first = &m_arr[0];
        m_last = &m_arr[m_capacity - 1];
        m_cur_first = m_last;
        m_cur_last = m_first;
        delete[] temp;
    }

    friend std::ostream& operator<< (std::ostream &out, circular_buffer<T> &circularBuffer){
        for (auto i = &circularBuffer.m_arr[0]; i != &circularBuffer.m_arr[circularBuffer.m_capacity - 1]; ++i)
            out << *i << ' ';
        out << circularBuffer.m_arr[circularBuffer.m_capacity - 1];
        return out;
    }
};

template<class T>
class CPoint {
public:
    CPoint(T x = 0, T y = 0) : m_x{x}, m_y{y} {}

    friend std::ostream& operator<< (std::ostream &out, CPoint &point){
        out << "(" << point.m_x << "; " << point.m_y << ")";
        return out;
    }
private:
    T m_x, m_y;
};

int main() {
    circular_buffer<float> buf_float(3);
    buf_float.push_back(1.1);
    std::cout << buf_float << std::endl;
    buf_float.push_back(2.2);
    std::cout << buf_float << std::endl;
    buf_float.push_back(3.3);
    std::cout << buf_float << std::endl;
    buf_float.change_capacity(4);
    buf_float.push_back(-5.5);

    if (is_sorted(buf_float.begin(), buf_float.end())){
        std::cout << "good" << std::endl;
    } else {
        std::cout << "not good" << std::endl;
    }

    sort(buf_float.begin(), buf_float.end());

    if (is_sorted(buf_float.begin(), buf_float.end())){
        std::cout << "good" << std::endl;
    } else {
        std::cout << "not good" << std::endl;
    }
    std::cout << buf_float << std::endl;

    circular_buffer<CPoint<float>> buf_CPoint(3);
    CPoint<float> a(1.1, 1.1), b(2.2, 2.2), c(3.3, 3.3);
    buf_CPoint.push_back(a);
    buf_CPoint.push_back(b);
    buf_CPoint.push_back(c);
    buf_CPoint.push_back(c);
    std::cout << buf_CPoint << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
} //approved
