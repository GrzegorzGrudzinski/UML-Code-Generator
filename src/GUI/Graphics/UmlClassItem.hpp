#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>

#include "UmlClass.hpp"

class UmlClassItem : public QGraphicsRectItem {
public:
    UmlClassItem(const std::string& className, QGraphicsItem* parent = nullptr);

    // returns logic for the generator
    uml::UmlClass getBackendClass() const { return backendClass; }
    
    void setClassName(const std::string& newName);
    void addAttribute(const uml::UmlAttribute& attr);
    void updateAttribute(int index, const uml::UmlAttribute& newAttr);
    void removeAttribute(int index);
    void addMethod(const uml::UmlMethod& attr);
    void updateMethod(int index, const uml::UmlMethod& newMethod);
    void removeMethod(int index);
private:
    uml::UmlClass backendClass;
    
    QGraphicsTextItem* titleText;
    QGraphicsTextItem* contentText;

    void updateVisuals(); // updates the screen
};