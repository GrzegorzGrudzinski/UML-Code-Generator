#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "UmlClassItem.hpp"

//
#include "UmlClass.hpp"
#include "UmlRefiner.hpp"
#include "generators.h"

#include <memory> // for make_unique
#include <vector>


using namespace uml;

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

    // 3. Generate code
    std::string output = "\t--- WYGENEROWANY KOD ---\n";
    for (const auto& generator : generators){
        output += "\n--- " + generator->getGeneratorName() + " ---\n"; 
        output += generator->generateClassCode(classToGenerate) ;
    }
    output += "// ========================================\n\n";

    std::cout<<output<<endl;

*/
