#include <iostream>
#include <vector>
#include <algorithm>
class CPolynomial{

public:
    CPolynomial(std::vector<int> pol){
        std::reverse(pol.begin(), pol.end());
        m_polynomial = pol;
    }

    CPolynomial(const CPolynomial &polynomial): m_polynomial {polynomial.m_polynomial}{}

    ~CPolynomial(){
        m_polynomial.clear();
    }

    CPolynomial& operator= (const CPolynomial &polynomial){
        if (this == &polynomial)
            return *this;
        m_polynomial = polynomial.m_polynomial;
        return *this;
    }

    friend bool operator== (const CPolynomial &polynomial1, const CPolynomial &polynomial2){
        if (polynomial1.m_polynomial.size() != polynomial2.m_polynomial.size())
            return false;
        for (int i = 0; i < polynomial1.m_polynomial.size(); ++i){
            if (polynomial1.m_polynomial[i] != polynomial2.m_polynomial.size())
                return false;
        }
        return true;
    }

    friend bool operator!= (const CPolynomial &polynomial1, const CPolynomial &polynomial2){
        return !(polynomial1 == polynomial2);
    }

    CPolynomial& operator- (CPolynomial &polynomial){
        if (m_polynomial.size() < polynomial.m_polynomial.size()){
            for (int i = m_polynomial.size(); i < polynomial.m_polynomial.size() ; ++i){
                m_polynomial.insert(m_polynomial.end(), 0);
            }
        }
        for(int i = 0; i < polynomial.m_polynomial.size(); i++)
            m_polynomial[i]=m_polynomial[i] - polynomial.m_polynomial[i];
        return *this;
    }

    CPolynomial& operator-= (CPolynomial &polynomial){
        *this = *this - polynomial;
        return *this;
    }

    CPolynomial& operator+ (CPolynomial &polynomial){
        if (m_polynomial.size() < polynomial.m_polynomial.size()){
            for (int i = m_polynomial.size(); i < polynomial.m_polynomial.size() ; ++i){
                m_polynomial.insert(m_polynomial.end(), 0);
            }
        }
        for(int i = 0; i < polynomial.m_polynomial.size(); i++)
            m_polynomial[i]=m_polynomial[i] + polynomial.m_polynomial[i];
        return *this;
    }

    CPolynomial& operator+= (CPolynomial &polynomial){
        *this = *this + polynomial;
        return *this;
    }

    CPolynomial& operator* (CPolynomial &polynomial){
        if (m_polynomial.size() < polynomial.m_polynomial.size()){
            for (int i = m_polynomial.size(); i < polynomial.m_polynomial.size() ; ++i){
                m_polynomial.insert(m_polynomial.end(), 0);
            }
        }
        for(int i = 0; i < polynomial.m_polynomial.size(); i++)
            m_polynomial[i]=m_polynomial[i] * polynomial.m_polynomial[i];
        return *this;
    }

    CPolynomial& operator *= (CPolynomial &polynomial){
        *this = *this * polynomial;
        return *this;
    }

    CPolynomial& operator/ (int &n){
        for (int i = 0; i < m_polynomial.size(); ++i) {
            m_polynomial[i] /= n;
        }
        return *this;
    }

    CPolynomial& operator/= (int &n){
        *this = *this / n;
        return *this;
    }

    int& operator[] (const int n){
        return this->m_polynomial[this->m_polynomial.size() - n];
    }

    CPolynomial operator-() const{
        CPolynomial polynomial = *this;
        for (int i = 0; i < m_polynomial.size(); ++i){
            polynomial.m_polynomial[i] *= -1;
        }
        return polynomial;
    }

    std::vector<int> getPolynomial() const{
        return m_polynomial;
    }

    void printPolynomial() const {
        int size = m_polynomial.size() - 1;
        if (m_polynomial[size] > 0){
            if (m_polynomial[size] == 1)
                std::cout << "x^" << size;
            else
                std::cout << m_polynomial[size] << "x^" << size;
        }
        if (m_polynomial[size] < 0){
            if (m_polynomial[size] == -1)
                std::cout << "-x^" << size;
            else
                std::cout << m_polynomial[size] << "x^" << size;
        }
        for (int i = size - 1; i > -1; --i){
            if (i == 0 || i == 1){
                if (i == 0){
                    if (m_polynomial[i] < 0)
                        std::cout << m_polynomial[i];
                    else
                        std::cout << "+" << m_polynomial[i];
                }
                if (i == 1){
                    if (m_polynomial[i] < 0)
                        std::cout << m_polynomial[i] << "x";
                    else
                        std::cout << "+" << m_polynomial[i] << "x";
                }
            }else{
                if (m_polynomial[i] > 0){
                    if (m_polynomial[i] == 1)
                        std::cout << "+" << "x^" << i;
                    else
                        std::cout << "+" << m_polynomial[i] << "x^" << i;
                }
                if (m_polynomial[i] < 0){
                    if (m_polynomial[i] == -1)
                        std::cout << "-" << "x^" << i;
                    else
                        std::cout << m_polynomial[i] << "x^" << i;
                }
            }
        }

    }

private:
    std::vector<int> m_polynomial;
};
int main(){
    CPolynomial polynom1 = {std::vector<int>{1, 2, 3, 4}};
    CPolynomial polynom2 = {std::vector<int>{1, 2, 3, 3, 12}};
    if (polynom1 == polynom2)
        std::cout << "pol1 equal pol2" << std::endl;
    if (polynom1 != polynom2)
        std::cout << "pol1 not equal pol2" << std::endl;

    std::cout << polynom1[3] << std::endl;

    polynom1.printPolynomial();

    return 0;
}
