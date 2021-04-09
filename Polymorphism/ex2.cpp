#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <memory>


using namespace std;


class Figure {
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};


class Triangle : public Figure {
public:

    Triangle(const double& a, const double& b, const double& c) : a_(a), b_(b), c_(c) {};

    string Name() const override {
        return "TRIANGLE";
    }

    double Perimeter() const override {
        return a_ + b_ + c_;
    }

    double Area() const override {
        double p = (a_ + b_ + c_) / 2;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    const double a_;
    const double b_;
    const double c_;
};


class Rect : public Figure {
public:

    Rect(const double& width, const double& height) : width_(width), height_(height) {};

    string Name() const override {
        return "RECT";
    }

    double Perimeter() const override {
        return 2 * width_ + 2 * height_;
    }

    double Area() const override {
        return width_ * height_;
    }

private:
    const double width_;
    const double height_;
};


class Circle : public Figure {
public:

    Circle(const double& radius) : r_(radius) {};

    string Name() const override {
        return "CIRCLE";
    }

    double Perimeter() const override {
        return 3.14 * 2 * r_;
    }

    double Area() const override {
        return 3.14 * r_ * r_;
    }

private:
    const double r_;
};

shared_ptr<Figure> CreateFigure(istream& info) {
    string type;
    info >> type;
    
    if (type == "TRIANGLE") {
        double a, b, c;

        info >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    }

    if (type == "CIRCLE") {
        double radius;
        info >> radius;

        return make_shared<Circle>(radius);
    }

    if (type == "RECT") {
        double width, height;
        info >> width >> height;

        return make_shared<Rect>(width, height);  
    }
}

/*
базовый класс Figure с чисто виртуальными методами Name, Perimeter и Area;
классы Triangle, Rect и Circle, которые являются наследниками класса Figure и переопределяют его виртуальные методы;
функцию CreateFigure, которая в зависимости от содержимого входного потока создаёт shared_ptr<Rect>, shared_ptr<Triangle> или shared_ptr<Circle>.
Гарантируется, что размеры всех фигур — это натуральные числа не больше 1000. В качестве значения PI используйте 3,14.
*/

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        }
        else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                    << current_figure->Name() << " "
                    << current_figure->Perimeter() << " "
                    << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}