#ifndef ISHAPE_H
#define ISHAPE_H

#include <string>
//Создание фигуры и ее методов
class IShape {
public:
    virtual ~IShape() = default;
    virtual void Draw() = 0;
    virtual void Erase() = 0;
    virtual std::string GetType() const = 0; // Добавляем метод для получения типа фигуры
    virtual std::string GetColor() const = 0; // Добавляем метод для получения цвета фигуры
};

#endif // ISHAPE_H
