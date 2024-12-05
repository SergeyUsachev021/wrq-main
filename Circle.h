#ifndef CIRCLE_H
#define CIRCLE_H

#include "IShape.h"
#include <iostream>
//Присвоение цвета фигуре
class Circle : public IShape {
private:
    std::string color;

public:
    Circle(const std::string& color) : color(color) {}

    void Draw() override {
        std::cout << "Drawing a " << color << " circle." << std::endl;
    }

    void Erase() override {
        std::cout << "Erasing a " << color << " circle." << std::endl;
    }

    std::string GetType() const override {
        return "circle"; // Возвращаем тип фигуры
    }

    std::string GetColor() const override {
        return color; // Возвращаем цвет фигуры
    }
};

#endif // CIRCLE_H
