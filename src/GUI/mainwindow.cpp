#include "mainwindow.h"
#include "ui_mainwindow.h"

//
#include "UmlClass.hpp"
#include "UmlAttribute.hpp"
#include "UmlMethod.hpp"
#include "UmlRefiner.hpp"
#include "generators.h" // Zmień na odpowiednią nazwę pliku, jeśli jest inna

#include <memory> // for make_unique
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->generateCodeButton, &QPushButton::clicked, this, &MainWindow::handleGenerateClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//
void MainWindow::handleGenerateClick() 
{
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

    // 3. Generate class code
    std::vector<std::unique_ptr<generator::CodeGenerator>> generators;
    std::unique_ptr<generator::CodeGenerator> generic_generator = nullptr;

    generic_generator = std::make_unique<generator::CppGenerator>();
    generators.push_back(std::move(generic_generator));
    // std::string cpp_code = generator->generateClassCode(myClass);
    
    generic_generator = std::make_unique<generator::PythonGenerator>();
    generators.push_back(std::move(generic_generator));
    // std::string python_code = generator->generateClassCode(myClass);
    
    // 4. Show results 
    std::string output = "\t--- GENERATORY ---\n";
    for (const auto& generator : generators){
        output += "\t--- " + generator->getGeneratorName() + " ---\n"; 
        output += generator->generateClassCode(myClass) ;
    }

    QString textToShow = QString::fromStdString(output);

    ui->outputWindow->setPlainText(textToShow);
}
