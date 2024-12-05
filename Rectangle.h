#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "IShape.h"
#include <iostream>
//Присвоение цвета фигуре
class Rectangle : public IShape {
private:
    std::string color;

public:
    Rectangle(const std::string& color) : color(color) {}

    void Draw() override {
        std::cout << "Drawing a " << color << " rectangle." << std::endl;
    }

    void Erase() override {
        std::cout << "Erasing a " << color << " rectangle." << std::endl;
    }

    std::string GetType() const override {
        return "rectangle"; // Возвращаем тип фигуры
    }

    std::string GetColor() const override {
        return color; // Возвращаем цвет фигуры
    }
};

#endif // RECTANGLE_H
