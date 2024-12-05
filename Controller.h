#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Document.h"
#include "Circle.h"
#include "Rectangle.h"
#include <memory>
#include <string>
#include <iostream>

class Controller {
private:
    std::shared_ptr<Document> document; // Оставляем как private

public:
    Controller() : document(nullptr) {} // Изначально документ не создан

    void HandleCreateDocument() {
        std::string documentName;
        std::cout << "Введите имя документа: ";
        std::cin >> documentName;

        document = std::make_shared<Document>(documentName); // Создаем документ с именем
        std::cout << "Документ \"" << documentName << "\" создан." << std::endl; // Подтверждение создания документа
    }

    void HandleImportDocument(const std::string& filename) {
        if (document) {
            document->ImportDocument(filename);
        } else {
            std::cout << "Документ не создан. Пожалуйста, создайте документ сначала." << std::endl;
        }
    }

    void HandleExportDocument(const std::string& filename) {
        if (document) {
            document->ExportDocument(filename);
        } else {
            std::cout << "Документ не создан. Пожалуйста, создайте документ сначала." << std::endl;
        }
    }

    void HandleAddShape(const std::string& shapeType, const std::string& color) {
        if (document) { // Проверяем, что документ существует
            std::shared_ptr<IShape> shape;
            if (shapeType == "circle") {
                shape = std::make_shared<Circle>(color);
            } else if (shapeType == "rectangle") {
                shape = std::make_shared<Rectangle>(color);
            } else {
                std::cout << "Неизвестный тип фигуры: " << shapeType << std::endl;
                return; // Прекращаем выполнение метода при ошибке
            }
            document->AddShape(shape);
            // Выводим текущее состояние файла после добавления фигуры
            document->PrintCurrentFileContent(document->GetName()); // Предполагается, что у Document есть метод GetName()
        } else {
            std::cout << "Документ не создан. Пожалуйста, создайте документ сначала." << std::endl;
        }
    }

    void HandleRemoveShape(std::shared_ptr<IShape> shape) {
    if (document) { // Проверяем, что документ существует
        if (shape) {
            document->RemoveShape(shape);
            // Проверяем количество фигур после удаления
            if (document->GetShapeCount() > 0) {
                std::cout << "Фигура " << shape->GetType() << " с цветом " << shape->GetColor() << " была удалена." << std::endl;
            } else {
                std::cout << "Все фигуры были удалены." << std::endl;
            }
            // Выводим текущее состояние файла после удаления фигуры
            document->PrintCurrentFileContent(document->GetName());
        } else {
            std::cout << "Нет фигур для удаления." << std::endl;
        }
    } else {
        std::cout << "Документ не создан. Пожалуйста, создайте документ сначала." << std::endl;
    }
    }


    size_t GetShapeCount() const { // Метод для получения количества фигур
        return document ? document->GetShapeCount() : 0;
    }

    std::shared_ptr<IShape> GetLastShape() const { // Метод для получения последней фигуры
        return document ? document->GetLastShape() : nullptr;
    }
};

#endif 
