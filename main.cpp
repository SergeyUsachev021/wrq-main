#include <iostream>
#include <memory>
#include <limits> // Добавляем этот заголовок для использования std::numeric_limits
#include "Circle.h"
#include "Controller.h"

void ShowMenu() {
    std::cout << "\nВыберите действие:\n";
    std::cout << "1. Создать новый документ\n";
    std::cout << "2. Импортировать документ из файла\n";
    std::cout << "3. Экспортировать документ в файл\n";
    std::cout << "4. Добавить фигуру (круг/прямоугольник)\n";
    std::cout << "5. Удалить фигуру\n";
    std::cout << "0. Выход\n";
}
//wqe
int main() {
    Controller controller;
    int choice;

    do {
        ShowMenu();
        std::cout << "Введите номер действия: ";
        if (!(std::cin >> choice)) { // Проверка ввода
            std::cin.clear(); // Сброс состояния потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем некорректный ввод
            std::cout << "Пожалуйста, введите корректный номер действия." << std::endl;
            continue; // Возвращаемся к началу цикла
        }

        switch (choice) {
            case 1:
                controller.HandleCreateDocument(); // Запрашивает имя документа
                break;
            case 2: {
                std::string filename;
                std::cout << "Введите путь к файлу для импорта: ";
                std::cin >> filename;
                controller.HandleImportDocument(filename);
                break;
            }
            case 3: {
                std::string filename;
                std::cout << "Введите путь к файлу для экспорта: ";
                std::cin >> filename;
                controller.HandleExportDocument(filename);
                break;
            }
            case 4: {
                std::string shapeType, color;
                std::cout << "Введите тип фигуры (circle/rectangle): ";
                std::cin >> shapeType;
                std::cout << "Введите цвет фигуры: ";
                std::cin >> color;
                controller.HandleAddShape(shapeType, color);
                break;
            }
            case 5: { // Удаление фигуры
                if (controller.GetShapeCount() > 0) { // Проверяем, есть ли фигуры
                    auto shape = controller.GetLastShape(); // Получаем последнюю фигуру
                    controller.HandleRemoveShape(shape); // Удаляем её
                    std::cout << "Последняя фигура была удалена." << std::endl; // Сообщение об удалении
                } else {
                    std::cout << "Нет фигур для удаления." << std::endl; // Сообщение на русском
                }
                break;
            }
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, попробуйте снова." << std::endl;
        }

    } while (choice != 0);

    return 0;
}
