#include "pugixml/pugixml.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <cmath>

class Transport_station {

public:
    // Конструктор
    Transport_station(int num = 0, std::string type_of_vehicle = "", std::string name_stopping = "",
                      std::string the_official_name ="", std::vector<std::string> location ={},
                      std::vector<std::string> routes = {}, std::pair<double, double> coordinates = {0, 0})
                      : m_num {num}, m_coordinates {coordinates}, m_location {location}, m_name_stopping {name_stopping},
                      m_routes {routes}, m_the_official_name {the_official_name}, m_type_of_vehicle {type_of_vehicle} {}

    int get_num() const {
        return m_num;
    }
    
    std::string get_type_of_vehicle() const {
        return m_type_of_vehicle;
    }
    
    std::string get_name_stopping() const {
        return m_name_stopping;
    }
    
    std::string get_the_official_name() const {
        return m_the_official_name;
    }
    
    std::vector<std::string> get_location() const {
        return m_location;
    }
    
    std::vector<std::string> get_routes () const {
        return m_routes;
    }
    
    double get_coordinates_x() const {
        return m_coordinates.first;
    }
    
    double get_coordinates_y() const {
        return m_coordinates.second;
    }
    
    std::string route_i(int i) const {
        return m_routes[i];
    }
    
    int route_size() const {
        return m_routes.size();
    }

private:
    int m_num;
    std::string m_type_of_vehicle;
    std::string m_name_stopping;
    std::string m_the_official_name;
    std::vector<std::string> m_location;
    std::vector<std::string> m_routes;
    std::pair<double, double> m_coordinates;
};

class Routes {
public:
    std::string route;
    std::vector<Transport_station> Trolleybus;
    std::vector<Transport_station> Bus;
    std::vector<Transport_station> Tram;
};

// Функция подсчёта растояний между двумя координатами
double distCoord(const Transport_station &a, const Transport_station &b) {
    double lat1, lat2, long1, long2, delta_lat, delta_long, ans;
    lat1 = a.get_coordinates_x() * M_PI / 180;
    long1 = a.get_coordinates_y() * M_PI / 180;
    lat2 = b.get_coordinates_x() * M_PI / 180;
    long2 = b.get_coordinates_y() * M_PI / 180;
    delta_lat = lat2 - lat1;
    delta_long = long2 - long1;
    ans = pow(sin(delta_lat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(delta_long / 2), 2);
    ans = 2 * asin(sqrt(ans)) * 6371;
    return ans;
}

// Функция для считывания данных без запятой
void separator(const std::string &str, std::string &str1, std::string &str2) {
    std::string separator = ","; // указываем раздилитель
    int start = 0; // начало
    int finish = str.find(separator); // и конец строки
    while (finish != -1) {
        str1 = str.substr(start, finish - start); // записываем первую чать строки
        start = finish + separator.length(); // переводим указатели старт и финиш на след. пункт
        finish = str.find(separator, start);
    }
    str2 = str.substr(start, finish); // записываем вторую часть строки
}

// Функция для обрезания строки
std::string correction_location(std::string &str) { // errors хранит всё то, что можно обрезать
    std::vector<std::string> errors {"ул.", " ул.", " УЛ.", " ш.", " Ш.", " шоссе", " ШОССЕ",
                                    " пер.", " ПЕР.", " переулок", " ПЕРЕУЛОК", " улица", "улица", " УЛИЦА",
                                    " бул", " БУЛ", " бульвар", " БУЛЬВАР", " пр", " ПР", " проспект", " ПРОСПЕКТ"};
    for (auto &i: errors) {
        if (str.find(i) != -1) {
            int first = str.find(i);
            int second = first + i.size();
            str.erase(first, second);
        }
    }
    if (str[str.size() - 1] == ' ')
        str.erase(str.end() - 1);
    return str;
}

// Парсинг
void parsing_file(std::vector<Transport_station> &a, std::map<std::string, Routes> &Map_routes, std::set<std::string> &Name_routes, std::map<std::string, int> &Locations) {
    pugi::xml_document doc; // создаем обьект
    doc.load_file("data-20210322T085457-structure-20190416T084545.xml"); // используем файл
    pugi::xml_node data = doc.child("dataset"); // находи первого ребёнка
    // идём по детям dataset считывая нужную информацию
    for (pugi::xml_node i = data.child("transport_station"); i; i = i.next_sibling("transport_station")) {
        // координаты
        std::string str1, str2;
        separator(i.child_value("coordinates"), str1, str2); // используем сепоратор
        float coord1, coord2;
        coord1 = stof(str1); // преобразуем строку в float
        coord2 = stof(str2);
        std::pair<double, double> coordinates;
        coordinates.first = coord1;
        coordinates.second = coord2;
        // маршрут
        str1 = "";
        str2 = "";
        std::string str_routes = i.child_value("routes"), segment; // segment - пустая строка
        std::vector<std::string> routes;
        std::stringstream tempR(str_routes);  // создаём строковый поток
        if (count(str_routes.begin(), str_routes.end(), ',')) // заполняем вектор routes
            while (getline(tempR, segment, ',')) // корректируя данные для дальнейшей работы
                routes.push_back(segment);
        else
            while (getline(tempR, segment, '.'))
                routes.push_back(segment);
        // локация
        str1 = "";
        str2 = "";
        std::string str_location = i.child_value("location");
        std::vector<std::string> locations;
        std::stringstream tempL(str_location); // создаём строковый поток
        if (count(str_location.begin(), str_location.end(), ',') && !str_location.empty()) { // корректируем и разделяем локации для дальнейшей работы
            while (getline(tempL, segment, ',')) {
                if (segment[0] == ' ')
                    segment.erase(segment.begin());
                locations.push_back(correction_location(segment));
                Locations[correction_location(segment)] += 1;
            }
        }
        else if (!str_location.empty()) {
            locations.push_back(correction_location(str_location));
            Locations[correction_location(str_location)] += 1;
        }
        // помещаем данные в экземпляр класса
        int num = std::stoi(i.child_value("number"));
        std::string type_of_vehicle = i.child_value("type_of_vehicle");
        std::string name_stopping = i.child_value("name_stopping");
        std::string the_official_name = i.child_value("the_official_name");
        Transport_station Tran_st(num, type_of_vehicle, name_stopping, the_official_name, locations, routes, coordinates);
        a.emplace_back(Tran_st);
        if (strcmp(i.child_value("type_of_vehicle"), "Трамвай") == false) {
            for (auto &j: routes) {
                Map_routes[j].Tram.emplace_back(Transport_station(num, type_of_vehicle, name_stopping,
                                                                  the_official_name, locations, routes, coordinates));
                Map_routes[j].route = j;
                Name_routes.insert(j);
            }
        }
        if (strcmp(i.child_value("type_of_vehicle"), "Автобус") == false) {
            for (auto &j: routes) {
                Map_routes[j].Bus.emplace_back(Transport_station(num, type_of_vehicle, name_stopping, the_official_name,
                                                                 locations, routes, coordinates));
                Map_routes[j].route = j;
                Name_routes.insert(j);
            }
        }
        if (strcmp(i.child_value("type_of_vehicle"), "Троллейбус") == false) {
            for (auto &j: routes) {
                Map_routes[j].Trolleybus.emplace_back(Transport_station(num, type_of_vehicle, name_stopping,
                                                                        the_official_name, locations, routes, coordinates));
                Map_routes[j].route = j;
                Name_routes.insert(j);
            }
        }
    }
}

int main() {
    std::vector<Transport_station> TransportStation;
    std::map<std::string, Routes> routes;
    std::set<std::string> name_routes;
    std::map<std::string, int> locations;
    parsing_file(TransportStation, routes, name_routes, locations);
    // создаём хеш-таблицу, которая будет хранить маршруты и кол-во остановок
    std::map<std::string, int> tram_routes, bus_routes, trolleybus_routes;
    for (auto const& i: TransportStation) { // заполняем кол-во станция для каждого вида транспорта
        if (i.get_type_of_vehicle() == "Трамвай")
            for (int j = 0; j < i.route_size(); j++)
                tram_routes[i.route_i(j)] += 1;
        else if (i.get_type_of_vehicle() == "Автобус")
            for (int j = 0; j < i.route_size(); j++)
                bus_routes[i.route_i(j)] += 1;
        else if (i.get_type_of_vehicle() == "Троллейбус")
            for (int j = 0; j < i.route_size(); j++)
                trolleybus_routes[i.route_i(j)] += 1;
    }

    // Пункт 1. Маршрут с наибольшим количеством остановок по отдельными видам транспорта.
    std::string max_tram_routes, max_bus_routes, max_trolleybus_routes; // номера маршрутов
    int k_tram_routes = 0, k_bus_routes = 0, k_trolleybus_routes = 0; // кол-во остановок
    // подсчёт наибольшего кол-ва остановок и номер этого маршрута
    for (auto const& i: tram_routes)
        if (i.second > k_tram_routes) {// ищем саксимальное кол-во остановок для каждого вида транспорта
            k_tram_routes = i.second;
            max_tram_routes = i.first;
        }
    for (auto const& i: bus_routes)
        if (i.second > k_bus_routes) {
            k_bus_routes = i.second;
            max_bus_routes = i.first;
        }
    for (auto const& i: trolleybus_routes)
        if (i.second > k_trolleybus_routes) {
            k_trolleybus_routes = i.second;
            max_trolleybus_routes = i.first;
        }
    std::cout << "1. Маршрут с наибольшим количеством остановок по отдельными видам транспорта." << std::endl;
    std::cout << "Маршрут №" << max_tram_routes
    << " имеет максимальное кол-во остановок среди трамваев, равное: " << k_tram_routes << " остановок." << std::endl;
    std::cout << "Маршрут №" << max_bus_routes
    << " имеет максимальное кол-во остановок среди автобусов, равное: " << k_bus_routes << " остановок." << std::endl;
    std::cout << "Маршрут №" << max_trolleybus_routes
    << " имеет максимальное кол-во остановок среди троллейбусов, равное: " << k_trolleybus_routes << " остановок." << std::endl;


    // Пункт 2. Наиболее длинный маршрут (основывая на координатах) по отдельным видам транспорта.
    std::map<std::string, double> size_tram_routes, size_bus_routes, size_trolleybus_routes;
    for (const auto &i: name_routes) {
        if (routes[i].Tram.size() > 1)
            for (int j = 0; j < routes[i].Tram.size() - 1; j++)
                size_tram_routes[routes[i].route] += distCoord(routes[i].Tram[j], routes[i].Tram[j + 1]);
        if (routes[i].Bus.size() > 1)
            for (int j = 0; j < routes[i].Bus.size() - 1; j++)
                size_bus_routes[routes[i].route] += distCoord(routes[i].Bus[j], routes[i].Bus[j + 1]);
        if (routes[i].Trolleybus.size() > 1)
            for (int j = 0; j < routes[i].Trolleybus.size() - 1; j++)
                size_trolleybus_routes[routes[i].route] += distCoord(routes[i].Trolleybus[j], routes[i].Trolleybus[j + 1]);
    }
    std::string max_tram_routes1, max_bus_routes1, max_trolleybus_routes1;
    double k_tram_routes1 = 0, k_bus_routes1 = 0, k_trolleybus_routes1 = 0;
    for (auto const& i : size_tram_routes)
        if (i.second > k_tram_routes1) {
            k_tram_routes1 = i.second;
            max_tram_routes1 = i.first;
        }
    for (auto const& i : size_bus_routes)
        if (i.second > k_bus_routes1) {
            k_bus_routes1 = i.second;
            max_bus_routes1 = i.first;
        }
    for (auto const& i : size_trolleybus_routes)
        if (i.second > k_trolleybus_routes1) {
            k_trolleybus_routes1 = i.second;
            max_trolleybus_routes1 = i.first;
        }
    std::cout << "\n2. Наиболее длинный маршрут (основывая на координатах) по отдельным видам транспорта." << std::endl;
    std::cout << "Наидлинейший маршрут трамвая: " << max_tram_routes1 << std::endl;
    std::cout << "Наидлинейший маршрут автобуса: " << max_bus_routes1 << std::endl;
    std::cout << "Наидлинейший маршрут троллейбуса: " << max_trolleybus_routes1 << std::endl;

    // Пункт 3. Улица с наибольшим числом остановок.
    int max_street = 0; // ищем максимальное кол-во остановок и улицу, на котрой они рассположенны
    std::string str_max_street;
    for (auto const& i: locations)
        if (i.second) {
            max_street = i.second;
            str_max_street = i.first;
        }
    std::cout << "\n3. Улица с наибольшим числом остановок." << std::endl;
    std::cout << "Улица " << "\"" << str_max_street << "\"" << " имеет наибольшее количество остановок, целых  " << max_street << " штук." << std::endl;
    std::cout << std::endl;
    return 0;
} //aproved