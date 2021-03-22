#include <iostream>
#include <cmath>
#include <vector>
#define PI 3.141592653589793238463
class CPoint{
public:
    CPoint(double x = 0.0, double y = 0.0) : m_x {x}, m_y {y} {} //конструктор со списком инциализации членов
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
    double getX() const {return m_x;}
    double getY() const {return m_y;}
    //два сеттера
    void setX (float x = 0) {m_x = x;}
    void setY (float y = 0) {m_y = y;}
private:
    double m_x;
    double m_y;
};

class CPolyline{
protected:
    std::vector<CPoint> m_ListOfPoint;
    double distance (const CPoint& a, const CPoint& b) const {
        return sqrt(pow((a.getX() - b.getX()),2) + pow((a.getY() - b.getY()),2));
    }
    double length() const{
        double len = 0;
        for (int i = 1; i < m_ListOfPoint.size(); ++i) {
            len += distance(m_ListOfPoint[i], m_ListOfPoint[i-1]);
        }
        len += distance(m_ListOfPoint[m_ListOfPoint.size()-1], m_ListOfPoint[0]);
        return len;
    }
public:
    CPolyline(CPoint *ListOfPoint = nullptr, int size = 0){
        for (int i = 0; i < size; ++i) {m_ListOfPoint.push_back(ListOfPoint[i]);}
    }//конструктор для ломанной
    CPolyline(const CPolyline &polyline){
        int size = polyline.m_ListOfPoint.size();
        for (int i = 0; i < size; ++i) {m_ListOfPoint[i] = polyline.m_ListOfPoint[i];}
    }//конструктор копирования
    CPolyline& operator= (const CPolyline &polyline){
        if (this == &polyline)
            return *this;
        int size = polyline.m_ListOfPoint.size();
        for (int i = 0; i < size; ++i) {m_ListOfPoint[i] = polyline.m_ListOfPoint[i];}
        return *this;
    }//оператор присваивания
    CPoint getPoint (int i) const {return m_ListOfPoint[i];}
    double getLength() const {return length();}

};

class CClosePolyline : public CPolyline{
public:
    CClosePolyline(CPoint *ListOfPoint = nullptr, int size = 0) : CPolyline(ListOfPoint, size){}
    CClosePolyline(const CClosePolyline &closePolyline) : CPolyline(closePolyline){}
    CClosePolyline& operator= (const CClosePolyline &closePolyline){
        if (this == &closePolyline)
            return *this;
        int size = closePolyline.m_ListOfPoint.size();
        for (int i = 0; i < size; ++i) {m_ListOfPoint[i] = closePolyline.m_ListOfPoint[i];}
        return *this;
    }
};

class CPolygon : public CClosePolyline{
protected:
    std::vector<double> m_ListOfAngles;
public:
    CPolygon(CPoint *ListOfPoint = nullptr, int size = 0) : CClosePolyline(ListOfPoint, size) {
        m_ListOfAngles = angles();
    }
    CPolygon(const CPolygon &polygon) : CClosePolyline(polygon){
        m_ListOfAngles = angles();
    }
    CPolygon& operator= (const CPolygon &polygon){
        if (this == &polygon)
            return *this;
        int size = polygon.m_ListOfPoint.size();
        for (int i = 0; i < size; ++i) {m_ListOfPoint[i] = polygon.m_ListOfPoint[i];}
    }
    std::vector<double> getAngles(){return m_ListOfAngles;}
private:
    std::vector<double> angles(){
        int size = m_ListOfPoint.size() - 1;
        std::vector<double> ListOfAngles;
        std::vector<std::pair<double, double>> vector;
        for (int i = 0; i < size; ++i) {
            vector.push_back(std::make_pair(m_ListOfPoint[i+1].getX() - m_ListOfPoint[i].getX(),
                                            m_ListOfPoint[i+1].getY() - m_ListOfPoint[i].getY()));
        }
        vector.push_back(std::make_pair(m_ListOfPoint[0].getX() - m_ListOfPoint[size].getX(),
                                        m_ListOfPoint[0].getY() - m_ListOfPoint[size].getY()));

        std::vector<double> ListOfLength;
        for (int i = 0; i < size; ++i) {
            ListOfLength.push_back(distance(m_ListOfPoint[i], m_ListOfPoint[i+1]));
        }
        ListOfLength.push_back(distance(m_ListOfPoint[size], m_ListOfPoint[0]));

        for (int i = 0; i < size; ++i) {
            ListOfAngles.push_back(acos(-1*(vector[i].first * vector[i+1].first + vector[i].second * vector[i+1].second)/
                                   (ListOfLength[i] * ListOfLength[i+1])));
        }
        ListOfAngles.push_back(acos(-1*(vector[size].first * vector[0].first + vector[size].second * vector[0].second)/
                               (ListOfLength[size] * ListOfLength[0])));

        for (int i = 0; i < size + 1; ++i) {
            ListOfAngles[i] = ListOfAngles[i] * (180.0/PI);
        }
        return ListOfAngles;
    }
};
/*
class CTriangle{

};
class CTrapezoid{

};

class CRegularPolygon{

};
*/
int main() {
    CPoint triangle[3] = {CPoint {0, 0}, CPoint {0, 1}, CPoint {1, 0}};
    CPoint parallelogram[4] = {CPoint {0, 0}, CPoint {1, 2}, CPoint {3, 2}, CPoint {2, 0}};
    CPoint square[4] = {CPoint {0, 0}, CPoint {0, 1}, CPoint {1, 1}, CPoint {0, 1}};
    CPolygon Square(square, 4);
    CPolygon Parallelogram(parallelogram, 4);
    CPolygon Triangle(triangle, 3);
    std::cout<<Square.getLength()<<std::endl;
    return 0;
}