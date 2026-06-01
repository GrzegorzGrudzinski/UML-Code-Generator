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
    
    // adds Attribute and Method
    void addAttribute(const uml::UmlAttribute& attr);
    void addMethod(const uml::UmlMethod& attr);
    void setClassName(const std::string& newName);

private:
    uml::UmlClass backendClass;
    
    QGraphicsTextItem* titleText;
    QGraphicsTextItem* contentText;

    void updateVisuals(); // updates the screen
};