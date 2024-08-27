#include <iostream>
#include <cmath>
using namespace std;

class Quadrilateral {
private:
    double a, b, c, d; 

public:
    Quadrilateral() : a(0), b(0), c(0), d(0) {}

    Quadrilateral(double sideA, double sideB, double sideC, double sideD) 
        : a(sideA), b(sideB), c(sideC), d(sideD) {}

    ~Quadrilateral() {}

    double getPerimeter() const {
        return a + b + c + d;
    }

    double getDiagonal() const {
        return sqrt(a * a + c * c);
    }

    double getArea() const {
        double s = getPerimeter() / 2.0;
        return sqrt((s - a) * (s - b) * (s - c) * (s - d));
    }

    bool isTrapezoid() const {
        return (a == c || b == d); 
    }

    void printInfo() const {
        cout << "Стороны: " << a << ", " << b << ", " << c << ", " << d << endl;
        cout << "Периметр: " << getPerimeter() << endl;
        cout << "Диагональ: " << getDiagonal() << endl;
        cout << "Площадь: " << getArea() << endl;
        cout << (isTrapezoid() ? "Это трапеция" : "Это не трапеция") << endl;
    }

    bool isSquare() const {
        return (a == b && b == c && c == d);
    }
};

int main() {
    int N;
    cout << "Введите количество четырехугольников: ";
    cin >> N;

    Quadrilateral* quads = new Quadrilateral[N];

    for (int i = 0; i < N; ++i) {
        double a, b, c, d;
        cout << "Введите длины сторон четырехугольника " << i + 1 << ": ";
        cin >> a >> b >> c >> d;
        quads[i] = Quadrilateral(a, b, c, d);
    }

    double maxArea = 0;
    Quadrilateral* maxSquare = nullptr;

    for (int i = 0; i < N; ++i) {
        if (quads[i].isSquare()) {
            double area = quads[i].getArea();
            if (area > maxArea) {
                maxArea = area;
                maxSquare = &quads[i];
            }
        }
    }

    if (maxSquare) {
        cout << "Квадрат с максимальной площадью:" << endl;
        maxSquare->printInfo();
    } else {
        cout << "Квадратов среди введенных четырехугольников нет." << endl;
    }

    delete[] quads;

    return 0;
}
