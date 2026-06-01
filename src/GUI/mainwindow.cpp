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
    
    // Sygnały od panelu bocznego (upewnij się, że dodałeś te przyciski w Qt Designerze!)
    connect(ui->updateClassBtn, &QPushButton::clicked, this, &MainWindow::handleUpdateClassName);
    connect(ui->addAttrBtn, &QPushButton::clicked, this, &MainWindow::handleAddAttribute);
    connect(ui->addMethodBtn, &QPushButton::clicked, this, &MainWindow::handleAddMethod);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::handleSelectionChanged()
{
    auto selectedItems = mainScene->selectedItems();

    if (selectedItems.isEmpty()) {
        currentSelectedItem = nullptr;
        ui->classNameEdit->clear(); // clears when background is clicked
        return; 
    }

    currentSelectedItem = dynamic_cast<UmlClassItem*>(selectedItems.first());

    if (currentSelectedItem != nullptr) {
        std::string className = currentSelectedItem->getBackendClass().GetName();
        ui->classNameEdit->setText(QString::fromStdString(className));
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
}



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
