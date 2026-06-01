#include "UmlClassItem.hpp"

#include <QFont>
#include <QString>

UmlClassItem::UmlClassItem(const std::string& className, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), backendClass(className) 
{
    // 
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    // visuals
    setRect(0, 0, 150, 60);
    setBrush(QBrush(QColor(255, 255, 200))); 
    setPen(QPen(Qt::black, 2));              

    // Class title
    titleText = new QGraphicsTextItem(QString::fromStdString(className), this);
    QFont titleFont = titleText->font();
    titleFont.setBold(true);
    titleText->setFont(titleFont);
    titleText->setPos(10, 5);
    titleText->setDefaultTextColor(Qt::black);

    // Text for attributes and methods
    contentText = new QGraphicsTextItem("", this);
    contentText->setPos(10, 30);
    contentText->setDefaultTextColor(Qt::black);
}


void UmlClassItem::setClassName(const std::string& newName) {
    backendClass.class_name = newName;
    
    titleText->setPlainText(QString::fromStdString(newName));
    updateVisuals(); 
}

void UmlClassItem::addAttribute(const uml::UmlAttribute& attr) {
    backendClass.AddAttribute(attr); 
    updateVisuals();                 
}
void UmlClassItem::addMethod(const uml::UmlMethod& method) {
    backendClass.AddMethod(method); 
    updateVisuals();                 
}

void UmlClassItem::updateVisuals() {
    QString content = "";
    
    for (const auto& attr : backendClass.attributes ) {
        QString visibility = attr.visibility == "public" ? "+" : "-";
        content += visibility + " " + QString::fromStdString(attr.name + " : " + attr.type ) + "\n";
    }
    
    // separate attributes and methods (if there are both)
    if (!backendClass.attributes.empty() && !backendClass.methods.empty() ) {
        content += "-------------------\n";
    }
    
    for (const auto& method : backendClass.methods ) {
        QString visibility = method.visibility == "public" ? "+" : "-";
        content += visibility + " " + QString::fromStdString(method.name + " : " + method.type ) + "\n";
    }
    

    contentText->setPlainText(content);
    
    int dynamicHeight = 50 + contentText->boundingRect().height();
    setRect(0, 0, 150, dynamicHeight < 60 ? 60 : dynamicHeight);
}