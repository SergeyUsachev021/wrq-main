#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "IShape.h"
#include "Circle.h"
#include "Rectangle.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <algorithm>

class Document {
private:
    std::string name;
    std::vector<std::shared_ptr<IShape>> shapes;

public:
    Document(const std::string& docName) : name(docName) {}

    void AddShape(std::shared_ptr<IShape> shape) {
        shapes.push_back(shape);
        std::cout << "Фигура добавлена: " << shape->GetType() << " с цветом " << shape->GetColor() << std::endl;
        ExportDocument(name); // Экспортируем текущие фигуры в файл
        PrintCurrentFileContent(name); // Выводим содержимое файла
        PrintShapes(); // Выводим текущее состояние фигур
    }

    void RemoveShape(std::shared_ptr<IShape> shape) {
        auto it = std::remove(shapes.begin(), shapes.end(), shape);
        if (it != shapes.end()) {
            shapes.erase(it, shapes.end());
            std::cout << "Фигура удалена." << std::endl;
            ExportDocument(name); // Обновляем файл после удаления
            PrintCurrentFileContent(name); // Выводим содержимое файла
            PrintShapes(); // Выводим текущее состояние фигур
        } else {
            std::cout << "Фигура не найдена." << std::endl;
        }
    }

    size_t GetShapeCount() const {
        return shapes.size();
    }

    const std::string& GetName() const { // Метод для получения имени документа
        return name;
    }

    std::shared_ptr<IShape> GetLastShape() const { // Метод для получения последней фигуры
        return shapes.empty() ? nullptr : shapes.back();
    }

    void ImportDocument(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл для импорта." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string shapeType, color;
            if (!(iss >> shapeType >> color)) { 
                std::cout << "Ошибка чтения строки: " << line << std::endl; 
                continue; // Пропускаем некорректные строки
            }
            auto shape = CreateShape(shapeType, color);
            if (shape) {
                AddShape(shape); // Добавляем только корректные фигуры
            } else {
                std::cout << "Неизвестный тип фигуры: " << shapeType << std::endl;
            }
        }
        file.close();
        std::cout << "Импорт завершен." << std::endl;
    }

    void ExportDocument(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл для экспорта." << std::endl;
            return;
        }

        for (const auto& shape : shapes) {
            file << shape->GetType() << " " << shape->GetColor() << "\n"; // Предполагается, что у фигур есть эти методы
        }
        file.close();
        std::cout << "Экспорт завершен." << std::endl;
    }

    void PrintCurrentFileContent(const std::string& filename) const { // Метод для вывода содержимого файла
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Не удалось открыть файл для чтения." << std::endl;
            return;
        }

        std::string line;
        std::cout << "Содержимое файла " << filename << ":\n";
        while (std::getline(file, line)) {
            std::cout << line << std::endl; // Выводим каждую строку
        }
        file.close();
    }

    void PrintShapes() const { // Метод для вывода всех фигур
        if (shapes.empty()) {
            std::cout << "Документ пуст. Нет фигур для отображения." << std::endl;
            return;
        }

        std::cout << "Содержимое документа:\n";
        for (const auto& shape : shapes) {
            std::cout << shape->GetType() << " с цветом " << shape->GetColor() << std::endl;
        }
    }

private:
    std::shared_ptr<IShape> CreateShape(const std::string& shapeType, const std::string& color) {
        if (shapeType == "circle") {
            return std::make_shared<Circle>(color);
        } else if (shapeType == "rectangle") {
            return std::make_shared<Rectangle>(color);
        }
        return nullptr; // Если тип фигуры не распознан
    }
};

#endif
