#include "include/figure.hpp"
#include "include/Rhomb.hpp"
#include "include/Trapezoid.hpp"
#include "include/Pentagon.hpp"
#include "include/point.hpp"
#include "include/array.hpp"
#include <sstream>

int main() {

    Array<std::shared_ptr<Rhomb<double>>> R;
    auto rh1 = std::make_shared<Rhomb<double>>();
    std::istringstream R1("0.0 2.0 2.0 0.0 0.0 -2.0 -2.0 0.0");
    R1 >> *rh1;

    auto rh2 = std::make_shared<Rhomb<double>>();
    std::istringstream R2("0.0 4.0 3.5 0.0 0.0 -4.0 -3.5 0.0");
    R2 >> *rh2;

    R.push_back(rh1);
    R.push_back(rh2);

    std::cout << R.get_size() << std::endl;

    Array<std::shared_ptr<Trapezoid<double>>> T;
    auto tr1 = std::make_shared<Trapezoid<double>>();
    std::istringstream T1("-3.0 0.0 3.0 0.0 1.5 2.0 -1.5 2.0");
    T1 >> *tr1;

    auto tr2 = std::make_shared<Trapezoid<double>>();
    std::istringstream T2("-4.0 0.0 4.0 0.0 2.5 3.0 -2.5 3.0");
    T2 >> *tr2;

    T.push_back(tr1);
    T.push_back(tr2);

    std::cout << T.get_size() << std::endl;

    Array<std::shared_ptr<Pentagon<double>>> P;
    auto pn1 = std::make_shared<Pentagon<double>>();
    std::istringstream P1("0.0 3.0 2.85 0.93 1.76 -2.43 -1.76 -2.43 -2.85 0.93");
    P1 >> *pn1;

    auto pn2 = std::make_shared<Pentagon<double>>();
    std::istringstream P2("0.0 4.0 3.8 1.2 2.5 -3.5 -2.5 -3.5 -3.8 1.2");
    P2 >> *pn2;

    P.push_back(pn1);
    P.push_back(pn2);

    std::cout << P.get_size() << std::endl;
    P.erase(0);
    std::cout << P.get_size() << std::endl;
    //--------------------------------------------------------------------------------------

    int16_t n = 0;
    int16_t i = 0;
    char current_fig;
    std::cout << "Введите количество фигур" << std::endl;
    std::cin >> n;
    Array<std::shared_ptr<Figure<double>>> figures;  


    while (true) {
        std::cout << "Введите тип фигуры где: r-ромб, t-трапеция, p-пятиугольник" << std::endl;
        std::cin >> current_fig;
        if (current_fig == 'r' ) {
            auto r = std::make_shared<Rhomb<double>>();
            std::cin >> *r;
            figures.push_back(r);
            ++i;
        }

        if (current_fig == 't' ) {
            auto t = std::make_shared<Trapezoid<double>>();
            std::cin >> *t;
            figures.push_back(t);
            ++i;
        }

        if (current_fig == 'p' ) {
            auto p = std::make_shared<Pentagon<double>>();
            std::cin >> *p;
            figures.push_back(p);
            ++i;
        }

        if (i == n) {
            break;
        }
    }

    char action;

    while (true) {
        std::cout << "Введите команду, которая вам нужна: p - площадь фигуры, t - общая площадь, d - удалить фигуру, c - центр фигуры, e - выйти " << std::endl;
        std::cin >> action;
        if (action == 'p') {
            std::cout << "Введите индекс" << std::endl;
            int16_t ind = 0;
            std::cin >> ind;
            if (ind <= figures.get_size()) {
                std::cout << "Total area: " << double(*figures[ind]) << std::endl;
            }
        }

        if (action == 't') {
            std::cout << "Total area: " << figures.total_area() << std::endl;
        }
        
        if (action == 'd') {
            std::cout << "Введите индекс" << std::endl;
            int16_t ind = 0;
            std::cin >> ind;
            figures.erase(ind);
        }

        if (action == 'c') {
            std::cout << "Введите номер фигуры " << std::endl;
            int16_t k = 0;
            std::cin >> k;
            if (k <= figures.get_size()){
                std::cout << figures[k]->calc_geom_center();
            }
        }

        if (action == 'e') {
            break;
        }
    }

}