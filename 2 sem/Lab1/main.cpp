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
    CPolyline& AddPoint(const CPoint &point){
        m_ListOfPoint.push_back(point);
        return *this;
    }
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
    bool convex(){
        int sum = 0;
        for(auto&n : m_ListOfAngles)
            sum += n;
        if (sum > 180 * (m_ListOfPoint.size() - 2))
            return false;
        return true;
    }
    double area(){
        int size = m_ListOfPoint.size() - 1;
        double area {0};
        if (convex()){
            for (int i = 0; i < size; ++i) {area += m_ListOfPoint[i].getX() * m_ListOfPoint[i+1].getY();}
            area += m_ListOfPoint[size].getX() * m_ListOfPoint[0].getY();
            for (int i = 0; i < size; ++i) {area -= m_ListOfPoint[i+1].getX() * m_ListOfPoint[i].getY();}
            area -= m_ListOfPoint[0].getX() * m_ListOfPoint[size].getY();
            return (0.5) * abs(area);
        }
        else{
            std::cout << "Вернул тебе нолик тк это невыпуклый многоугольник, прости" << std::endl;
            return 0.0;
        }
    }
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
        return *this;
    }
    std::vector<double> getAngles() {return m_ListOfAngles;}
    double getArea(){return area();}
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

class CTriangle : public CPolygon{
public:
    CTriangle(CPoint *ListOfPoint = nullptr) : CPolygon(ListOfPoint, 3){
        for (auto& n: getAngles()) {
            if (n == 180 or n == 0) {
                std::cout << "Это не треугольник" << std::endl;
                exit(1);
            }
        }
    }
    CTriangle(const CTriangle &triangle) = default;
    CTriangle& operator= (const CTriangle &triangle){
        if (this == &triangle)
            return *this;
        for (int i = 0; i < 3; ++i) {m_ListOfPoint[i] = triangle.m_ListOfPoint[i];}
        return *this;
    }
};

class CTrapezoid : public CPolygon{
public:
    CTrapezoid(CPoint *ListOfPoints = nullptr, int size = 0) : CPolygon(ListOfPoints, size){}

};
/*
class CRegularPolygon{

};
*/
int main() {
    CPoint triangle[3] = {CPoint {0, 0}, CPoint {0, 1}, CPoint {1, 0}};
    CPoint parallelogram[4] = {CPoint {0, 0}, CPoint {1, 2}, CPoint {3, 2}, CPoint {2, 0}};
    CPoint square[4] = {CPoint {0, 0}, CPoint {0, 1}, CPoint {1, 1}, CPoint {1, 0}};
    CPoint trapezoid[4] = {CPoint {0, 0}, CPoint {5,0}, CPoint{4, 3}, CPoint{2, 3}};
    CPolygon Square(square, 4);
    CTriangle Triangle(triangle);
    CTrapezoid Trapezoid(trapezoid, 4);
    std::cout << "Perimeter = " << Trapezoid.getLength() << "\nArea = " << Trapezoid.getArea() << std::endl;
    return 0;
}