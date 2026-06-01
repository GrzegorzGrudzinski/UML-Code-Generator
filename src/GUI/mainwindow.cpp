/*
    mainwindow.cpp
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "UmlClassItem.hpp"

//
#include "UmlClass.hpp"
#include "UmlRefiner.hpp"
#include "generators.h" // Zmień na odpowiednią nazwę pliku, jeśli jest inna

#include <memory> // for make_unique
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // ui->outputWindow->setStyleSheet // for output text

    //
    mainScene = new QGraphicsScene(this);
    mainScene->setSceneRect(-2500, -2500, 5000, 5000);

    ui->graphicsView->setScene(mainScene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    
    //
    connect(ui->generateCodeBtn, &QPushButton::clicked, this, &MainWindow::handleGenerateClick);
    connect(ui->addClassBtn, &QPushButton::clicked, this, &MainWindow::handleAddClassOnScene);
    connect(mainScene, &QGraphicsScene::selectionChanged, this, &MainWindow::handleSelectionChanged);
    
    connect(ui->updateClassBtn, &QPushButton::clicked, this, &MainWindow::handleUpdateClassName);
    
    connect(ui->addAttrBtn, &QPushButton::clicked, this, &MainWindow::handleAddAttribute);
    connect(ui->removeAttrBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteAttribute);
    connect(ui->attrList, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleAttrSelection);
    // connect(ui->attrVisibilityList, &QComboBox::currentTextChanged, this, &MainWindow::handleAVisibilitySelection);
    
    connect(ui->addMethodBtn, &QPushButton::clicked, this, &MainWindow::handleAddMethod);
    connect(ui->removeMethodBtn, &QPushButton::clicked, this, &MainWindow::handleDeleteMethod);
    connect(ui->methodList, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handleMethodSelection);
    // connect(ui->methodVisibilityList, &QComboBox::currentTextChanged, this, &MainWindow::handleMVisibilitySelection);
    

    // connect(ui->editAttrBtn, &QPushButton::clicked, this, &MainWindow::handleEditAttribute);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleSelectionChanged()
{
    auto selectedItems = mainScene->selectedItems();

    if (selectedItems.isEmpty()) {
        // clears when background is clicked        
        currentSelectedItem = nullptr;
        ui->classNameEdit->clear();

        ui->attrList->clear();
        ui->attrNameEdit->clear();
        ui->attrTypeEdit->clear();
        ui->attrVisibilityList->clear();

        ui->methodList->clear();
        ui->methodNameEdit->clear();
        ui->methodTypeEdit->clear();
        ui->methodVisibilityList->clear();

        return; 
    }

    currentSelectedItem = dynamic_cast<UmlClassItem*>(selectedItems.first());

    if (currentSelectedItem != nullptr) {
        std::string className = currentSelectedItem->getBackendClass().GetName();
        ui->classNameEdit->setText(QString::fromStdString(className));

        refreshAttrList(); 
        refreshMethodList(); 
    }
}

using namespace uml;

//
void MainWindow::handleAddClassOnScene()
{
    // add class
    UmlClassItem* newClassItem = new UmlClassItem("NowaKlasa");
    
    // add attribute
    // newClassItem->addAttribute(uml::UmlAttribute("private", "int", "testVar"));
    
    mainScene->addItem(newClassItem);
}

/*
    // 1. Create class
    uml::UmlClass myClass("moja_klasa");

    uml::UmlAttribute attribute("public", "int", "moja_zmienna1");
    attribute.generateGetter = true;
    attribute.generateSetter = true;
    attribute.inConstructor = true;

    myClass.AddAttribute(attribute);
    
    uml::UmlMethod method("public", "void", "moja_metoda1");
    
    myClass.AddMethod(method);

    uml::UmlAttribute attribute1("private", "string", "moja_zmienna2");
    attribute1.generateGetter = false;
    attribute1.generateSetter = true;
    attribute1.inConstructor = true;

    myClass.AddAttribute(attribute1);
    
    // 2. Prepare class for code generation
    uml::UmlRefiner refiner;
    refiner.applyConstructor(myClass);
    refiner.applyGettersSetters(myClass);

*/


void MainWindow::handleUpdateClassName()
{
    if (currentSelectedItem == nullptr) return; 

    QString newName = ui->classNameEdit->text();
    if (!newName.isEmpty()) {
        currentSelectedItem->setClassName(newName.toStdString()); 
    }
}


void MainWindow::handleAddAttribute()
{
    if (currentSelectedItem == nullptr) return;

    QString nameInput = ui->attrNameEdit->text();
    QString typeInput = ui->attrTypeEdit->text();
    if (typeInput.isEmpty() || nameInput.isEmpty()) return;

    uml::UmlAttribute newAttr("private", typeInput.toStdString(), nameInput.toStdString());
    currentSelectedItem->addAttribute(newAttr);

    // clear when added
    ui->attrTypeEdit->clear();
    ui->attrNameEdit->clear();

    refreshAttrList();
}

void MainWindow::handleAddMethod()
{
    if (currentSelectedItem == nullptr) return;

    QString typeInput = ui->methodTypeEdit->text();
    QString nameInput = ui->methodNameEdit->text();
    if (typeInput.isEmpty() || nameInput.isEmpty()) return;

    uml::UmlMethod newMethod("public", typeInput.toStdString(), nameInput.toStdString());
    currentSelectedItem->addMethod(newMethod);

    ui->methodTypeEdit->clear();
    ui->methodNameEdit->clear();

    refreshMethodList();
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
    
    // ui->attrVisibilityList->setCurrentText(QString::fromStdString(attr.visibility));
}

void MainWindow::handleEditAttribute() {
    if (currentSelectedItem == nullptr) return;
    
    int index = ui->attrList->currentIndex(); 
    if (index < 0) return; 

    QString newType = ui->attrTypeEdit->text();
    QString newName = ui->attrNameEdit->text();
    if (newType.isEmpty() || newName.isEmpty()) return;

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
///////////

void MainWindow::handleMethodSelection(int index) {
    if (currentSelectedItem == nullptr || index < 0) return;

    auto method = currentSelectedItem->getBackendClass().methods[index];

    ui->methodTypeEdit->setText(QString::fromStdString(method.type));
    ui->methodNameEdit->setText(QString::fromStdString(method.name));
    
    // ui->methodVisibilityList->setCurrentText(QString::fromStdString(method.visibility));
}

void MainWindow::handleEditMethod() {
    if (currentSelectedItem == nullptr) return;
    
    int index = ui->methodList->currentIndex(); 
    if (index < 0) return; 

    QString newType = ui->methodTypeEdit->text();
    QString newName = ui->methodNameEdit->text();
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



///////////////



//
void MainWindow::handleGenerateClick() 
{
    ui->outputWindow->clear();
    std::string output = "\t--- WYGENEROWANY KOD ---\n";

    // 1. Initialize the generators
    std::vector<std::unique_ptr<generator::CodeGenerator>> generators;
    std::unique_ptr<generator::CodeGenerator> generic_generator = nullptr;
    generators.push_back(std::make_unique<generator::CppGenerator>());
    generators.push_back( std::make_unique<generator::PythonGenerator>());
    
    bool foundAnyClass = false;
    for (QGraphicsItem* item : mainScene->items()) {
        UmlClassItem* umlItem = dynamic_cast<UmlClassItem*>(item);
        if (umlItem != nullptr) {
            foundAnyClass = true;

            // 
            uml::UmlClass classToGenerate = umlItem->getBackendClass();

            // prepare the class for generation
            uml::UmlRefiner refiner;
            refiner.applyConstructor(classToGenerate);
            refiner.applyGettersSetters(classToGenerate);

            for (const auto& generator : generators){
                output += "\n--- " + generator->getGeneratorName() + " ---\n"; 
                output += generator->generateClassCode(classToGenerate) ;
            }
            output += "// ========================================\n\n";
        }
        if (!foundAnyClass) {
           output = "Brak klas do wygenerowania!";
        }
    }

    ui->outputWindow->setPlainText(QString::fromStdString(output));
}
