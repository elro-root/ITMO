#include <iostream>
#include <cmath>
#include <vector>
class CPoint{
public:
    CPoint(float x = 0.0, float y = 0.0) : m_x {x}, m_y {y} {} //конструктор со списком инциализации членов
    CPoint(const CPoint &point) : m_x {point.m_x}, m_y {point.m_y} {} //конструктор копирования
    void getPoint() const {
        std::cout << "X coordinate = " << m_x << "; Y coordinate = " << m_y << std::endl;
    }
    CPoint& operator= (const CPoint &point){
        if (this == &point) //this - указатель на объект класса, который вызывает метод getPoint
            return *this;
        m_x = point.m_x;
        m_y = point.m_y;
        return *this;
    }//оператор присваивания
    //два геттера
    float getX() const {return m_x;}
    float getY() const {return m_y;}
    //два сеттера
    void setX (float x = 0) {m_x = x;}
    void setY (float y = 0) {m_y = y;}
private:
    float m_x;
    float m_y;
};

class CPolyline{
protected:
    std::vector<CPoint> listOfPoint;
    double length() const{
        double len = 0;
        for (int i = 1; i < listOfPoint.size(); ++i) {
            len += distance(listOfPoint[i], listOfPoint[i-1]);
        }
        return len;
    }
public:
    CPolyline(CPoint *arr = nullptr, int n = 0){
        for (int i = 0; i < n; ++i) {listOfPoint.push_back(arr[i]);}
    }//конструктор для ломанной
    CPolyline(const CPolyline &polyline){
        int n = polyline.listOfPoint.size();
        for (int i = 0; i < n; ++i) {listOfPoint[i] = polyline.listOfPoint[i];}
    }//конструктор копирования
    CPolyline& operator= (const CPolyline &polyline){
        if (this == &polyline)
            return *this;
        int n = polyline.listOfPoint.size();
        for (int i = 0; i < n; ++i) {listOfPoint[i] = polyline.listOfPoint[i];}
        return *this;
    }//оператор присваивания
    CPoint getPoint (int i) const {return listOfPoint[i];}
    double getLength() const {return length();}

private:
    double distance (const CPoint& a, const CPoint& b) const {
        return sqrt(pow((a.getX() - b.getX()),2) + pow((a.getY() - b.getY()),2));
    }
};
/*
class CClosePolyline{

};

class CPolygon{

};

class CTriangle{

};
class CTrapezoid{

};

class CRegularPolygon{

};
*/
int main() {
    CPoint points[2] = {CPoint {0, 1}, CPoint {1, 1}};
    CPolyline polyline(points, 2);
    return 0;
}