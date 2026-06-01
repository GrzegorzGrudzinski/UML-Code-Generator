

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UmlClassItem.hpp"
#include "UmlClass.hpp"

void MainWindow::handleAddMethod()
{
    if (currentSelectedItem == nullptr) return;

    QString typeInput = ui->methodTypeEdit->text();
    QString nameInput = ui->methodNameEdit->text();
    QString visibilityInput = ui->methodVisibilityList->currentText();
    
    if (visibilityInput == "visibility") visibilityInput = "private"; 
    if (typeInput.isEmpty() || nameInput.isEmpty()) return;

    uml::UmlMethod newMethod(visibilityInput.toStdString(), typeInput.toStdString(), nameInput.toStdString());
    currentSelectedItem->addMethod(newMethod);

    ui->methodTypeEdit->clear();
    ui->methodNameEdit->clear();

    refreshMethodList();
}

void MainWindow::handleMethodSelection(int index) {
    if (currentSelectedItem == nullptr || index < 0) return;

    auto method = currentSelectedItem->getBackendClass().methods[index];

    ui->methodTypeEdit->setText(QString::fromStdString(method.type));
    ui->methodNameEdit->setText(QString::fromStdString(method.name));
    
    ui->methodVisibilityList->setCurrentText(QString::fromStdString(method.visibility));
}

void MainWindow::handleEditMethod() {
    if (currentSelectedItem == nullptr) return;
    
    int index = ui->methodList->currentIndex(); 
    if (index < 0) return; 

    QString newType = ui->methodTypeEdit->text();
    QString newName = ui->methodNameEdit->text();
    QString newVisibility = ui->methodVisibilityList->currentText();

    if (newVisibility == "visibility") newVisibility = "private";
    if (newType.isEmpty() || newName.isEmpty()) return;

    uml::UmlMethod updatedMethod("private", newType.toStdString(), newName.toStdString());
    currentSelectedItem->updateMethod(index, updatedMethod);
    
    refreshMethodList(); 
}

void MainWindow::handleDeleteMethod() {
    if (currentSelectedItem == nullptr) return;
    
    int index = ui->methodList->currentIndex();
    if (index < 0) return;

    currentSelectedItem->removeMethod(index);
    
    ui->methodTypeEdit->clear();
    ui->methodNameEdit->clear();
    refreshMethodList(); 
}

