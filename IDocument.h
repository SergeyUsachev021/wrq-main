#ifndef IDOCUMENT_H
#define IDOCUMENT_H

#include <string>
//При вызове виртуальной функции будет выполнена версия из
// производного класса, если объект фактически является экземпляром этого класса
class IDocument {
public:
    virtual ~IDocument() = default;
    virtual void CreateDocument() = 0;
    virtual void ImportDocument(const std::string& filename) = 0;
    virtual void ExportDocument(const std::string& filename) = 0;
};

#endif 
