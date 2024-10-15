#include "include/figure.h"
#include "include/Rhomb.h"
#include "include/Trapezoid.h"
#include "include/Pentagon.h"
#include "include/point.h"
int main() {
    int16_t n = 0;
    int16_t i = 0;
    char current_fig;
    double total_area = 0.0;
    std::cout << "Введите количество фигур" << std::endl;
    std::cin >> n;
    Figure** figures = new Figure*[n];

    while (true) {
        std::cout << "Введите тип фигуры где: r-ромб, t-трапеция, p-пятиугольник" << std::endl;
        std::cin >> current_fig;
        if (current_fig == 'r' ) {
            Rhomb* r = new Rhomb();
            std::cin >> *r;
            figures[i] = r;
            total_area += double(*figures[i]);
            ++i;
        }

        if (current_fig == 't' ) {
            Trapezoid* t = new Trapezoid();
            std::cin >> *t;
            figures[i] = t;
            total_area += double(*figures[i]);
            ++i;
        }

        if (current_fig == 'p' ) {
            Pentagon* p = new Pentagon();
            std::cin >> *p;
            figures[i] = p;
            total_area += double(*figures[i]);
            ++i;
        }

        if (i == n) {
            break;
        }
    }

    char action;

    while (true) {
        std::cout << "Введите команду, которая вам нужна: t - общая площадь, d - удалить фигуру, c - центр фигуры, e - выйти " << std::endl;
        std::cin >> action;
        if (action == 't') {
            std::cout << "Total area: " << total_area << std::endl;
        }
        
        if (action == 'd') {
            std::cout << "Введите индекс" << std::endl;
            int16_t ind = 0;
            std::cin >> ind;
            if (ind < n) {
                total_area -= double(*figures[ind]);
                delete figures[ind];
            
                for (int i = ind; i < n - 1; ++i) {
                    figures[i] = figures[i + 1];
                }
                figures[n - 1] = nullptr;
                --n;
            }
            else {
                std::cout << "Неверный инедкс" << std::endl;
            }
        }

        if (action == 'c') {
            std::cout << "Введите номер фигуры " << std::endl;
            int16_t k = 0;
            std::cin >> k;
            std::cout << figures[k]->calc_geom_center();
        }

        if (action == 'e') {
            break;
        }
    }
    for (int i = 0; i < n; ++i) {
        delete figures[i];
    }
    delete [] figures;
}
