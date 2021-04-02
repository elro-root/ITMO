#include <iostream>
#include <vector>
#include <algorithm>

class CPolynomial{

public:
    CPolynomial(std::vector<double> pol = {0}){
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
            if (polynomial1.m_polynomial[i] != polynomial2.m_polynomial[i])
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

    friend std::istream& operator>> (std::istream &in, CPolynomial &polynomial){
        int n;
        std::cout << "Enter the number of members of the polynomial: ";
        std::cin >> n;
        double k;
        std::cout << "Enter the coefficients of the polynomial, separated by a space: ";
        for (int i = 0; i < n; ++i) {
            in >> k;
            polynomial.m_polynomial.push_back(k);
        }
        polynomial.m_polynomial.erase(polynomial.m_polynomial.begin());
        std::reverse(polynomial.m_polynomial.begin(), polynomial.m_polynomial.end());
        return in;
    }

    friend std::ostream& operator<< (std::ostream &out, CPolynomial &polynomial){
        int size = polynomial.m_polynomial.size() - 1;
        if (polynomial.m_polynomial[size] > 0){
            if (polynomial.m_polynomial[size] == 1)
                out  << "x^" << size;
            else
                out  << polynomial.m_polynomial[size] << "x^" << size;
        }
        if (polynomial.m_polynomial[size] < 0){
            if (polynomial.m_polynomial[size] == -1)
                out  << "-x^" << size;
            else
                out  << polynomial.m_polynomial[size] << "x^" << size;
        }
        for (int i = size - 1; i > -1; --i){
            if (i == 0 || i == 1){
                if (i == 0){
                    if (polynomial.m_polynomial[i] < 0)
                        out  << polynomial.m_polynomial[i];
                    else
                        out << polynomial.m_polynomial[i];
                }
                if (i == 1){
                    if (polynomial.m_polynomial[i] < 0)
                        out  << polynomial.m_polynomial[i] << "x";
                    else if (polynomial.m_polynomial[i] != 0)
                        out  << "+" << polynomial.m_polynomial[i] << "x+";
                }
            }else{
                if (polynomial.m_polynomial[i] > 0){
                    if (polynomial.m_polynomial[i] == 1)
                        out  << "+" << "x^" << i;
                    else
                        out  << "+" << polynomial.m_polynomial[i] << "x^" << i;
                }
                if (polynomial.m_polynomial[i] < 0){
                    if (polynomial.m_polynomial[i] == -1)
                        out  << "-" << "x^" << i;
                    else
                        out  << polynomial.m_polynomial[i] << "x^" << i;
                }
            }
        }
        return out;
    }

    double& operator[] (const int n){
        return this->m_polynomial[this->m_polynomial.size() - n];
    }

    CPolynomial operator-() const{
        CPolynomial polynomial = *this;
        for (int i = 0; i < m_polynomial.size(); ++i){
            polynomial.m_polynomial[i] *= -1;
        }
        return polynomial;
    }

    std::vector<double> getPolynomial() const{
        return m_polynomial;
    }

private:
    std::vector<double> m_polynomial;
};

int main(){
    CPolynomial polynom1;
    std::cin >> polynom1;
    CPolynomial polynom2 = {std::vector<double>{1, 3, 6, 9, 12}};
    std::cout << polynom2 - polynom1 << std::endl;
    return 0;
}