#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "UmlClassItem.hpp"
#include "UmlClass.hpp"



void MainWindow::handleAddAttribute()
{
    if (currentSelectedItem == nullptr) return;

    QString nameInput = ui->attrNameEdit->text();
    QString typeInput = ui->attrTypeEdit->text();
    QString visibilityInput = ui->attrVisibilityList->currentText();
    
    if (visibilityInput == "visibility") visibilityInput = "private"; 
    if (typeInput.isEmpty() || nameInput.isEmpty()) return;

    uml::UmlAttribute newAttr(visibilityInput.toStdString(), typeInput.toStdString(), nameInput.toStdString());
    currentSelectedItem->addAttribute(newAttr);

    // clear when added
    ui->attrTypeEdit->clear();
    ui->attrNameEdit->clear();

    refreshAttrList();
}

void MainWindow::refreshAttrList() {
    ui->attrList->blockSignals(true); 
    ui->attrList->clear(); 
    
    if (currentSelectedItem != nullptr) {
        for (const auto& attr : currentSelectedItem->getBackendClass().attributes) {
            QString itemText = QString::fromStdString(attr.visibility + " " + attr.type + " " + attr.name);
            ui->attrList->addItem(itemText);
        }
    }
    
    ui->attrList->blockSignals(false); 

    if (ui->attrList->count() > 0) {
        handleAttrSelection(0);
    }
}

void MainWindow::refreshMethodList() {
    ui->methodList->blockSignals(true); 
    ui->methodList->clear(); 
    
    if (currentSelectedItem != nullptr) {
        for (const auto& method : currentSelectedItem->getBackendClass().methods) {
            QString itemText = QString::fromStdString(method.visibility + " " + method.type + " " + method.name + "()");
            ui->methodList->addItem(itemText);
        }
    }
    
    ui->methodList->blockSignals(false); 

    if (ui->methodList->count() > 0) {
        handleMethodSelection(0);
    }
}


void MainWindow::handleAttrSelection(int index) {
    if (currentSelectedItem == nullptr || index < 0) return;

    auto attr = currentSelectedItem->getBackendClass().attributes[index];

    ui->attrTypeEdit->setText(QString::fromStdString(attr.type));
    ui->attrNameEdit->setText(QString::fromStdString(attr.name));
    
    ui->attrVisibilityList->setCurrentText(QString::fromStdString(attr.visibility));
}

void MainWindow::handleEditAttribute() {
    if (currentSelectedItem == nullptr) return;
    
    int index = ui->attrList->currentIndex(); 
    if (index < 0) return; 

    QString newType = ui->attrTypeEdit->text();
    QString newName = ui->attrNameEdit->text();
    QString newVisibility = ui->attrVisibilityList->currentText();
    
    if (newType.isEmpty() || newName.isEmpty()) return;
    if (newVisibility == "visibility") newVisibility = "private";

    uml::UmlAttribute updatedAttr("private", newType.toStdString(), newName.toStdString());
    currentSelectedItem->updateAttribute(index, updatedAttr);
    
    refreshAttrList(); 
}

void MainWindow::handleDeleteAttribute() {
    if (currentSelectedItem == nullptr) return;
    
    int index = ui->attrList->currentIndex();
    if (index < 0) return;

    currentSelectedItem->removeAttribute(index);
    
    ui->attrTypeEdit->clear();
    ui->attrNameEdit->clear();
    refreshAttrList(); 
}
