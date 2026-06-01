#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "UmlClassItem.hpp"
#include "UmlClass.hpp"


//
void MainWindow::handleAddClassOnScene()
{
    // add class
    UmlClassItem* newClassItem = new UmlClassItem("NowaKlasa");
    
    // add attribute
    // newClassItem->addAttribute(uml::UmlAttribute("private", "int", "testVar"));
    
    mainScene->addItem(newClassItem);
}


void MainWindow::handleUpdateClassName()
{
    if (currentSelectedItem == nullptr) return; 

    QString newName = ui->classNameEdit->text();
    if (!newName.isEmpty()) {
        currentSelectedItem->setClassName(newName.toStdString()); 
    }
}
