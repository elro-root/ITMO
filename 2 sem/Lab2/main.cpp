#include <iostream>
#include <vector>
#include <algorithm>
class CPolynomial{
public:
    CPolynomial(std::vector<int> pol){
        std::reverse(pol.begin(), pol.end());
        m_polynomial = pol;
    }
    ~CPolynomial(){
        m_polynomial.clear();
    }
    std::vector<int> getPolynomial() const {return m_polynomial;}
    void printPolynomial() const{
        int size = m_polynomial.size();
        for (int i = size - 1; i > 0; --i){
            if (m_polynomial[i] == 1)
                std::cout <<"x^" << i << "+";
            else
                std::cout << m_polynomial[i] << "x^" << i << "+";
        }
        std::cout << m_polynomial[0] << std::endl;
    }
private:
    std::vector<int> m_polynomial;
};
int main(){
    CPolynomial polynom = {std::vector<int>{1,2,3,3}};
    polynom.printPolynomial();

    return 0;
}
