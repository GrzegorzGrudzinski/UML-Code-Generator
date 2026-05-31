#include <iostream>
#include <memory> // dla make_unique
#include <vector>

#include <QApplication>
#include "mainwindow.h"

#include "UmlClass.hpp"
#include "UmlRefiner.hpp"
// #include "CodeGenerator.hpp"

#include "generators.h"

using namespace uml;

int main(int argc, char *argv[]) {
    // 1. Create class
    UmlClass myClass("moja_klasa");

    UmlAttribute attribute("public", "int", "moja_zmienna1");
    attribute.generateGetter = true;
    attribute.generateSetter = true;
    attribute.inConstructor = true;

    myClass.AddAttribute(attribute);
    
    UmlMethod method("public", "void", "moja_metoda1");
    
    myClass.AddMethod(method);

    UmlAttribute attribute1("private", "string", "moja_zmienna2");
    attribute1.generateGetter = false;
    attribute1.generateSetter = true;
    attribute1.inConstructor = true;

    myClass.AddAttribute(attribute1);
    
    // 2. Prepare class for code generation
    UmlRefiner refiner;
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
    
    // 4. Show results (future GUI)
    std::cout << "\n--- GENERATORY ---" <<std::endl<<std::endl;
    
    for (const auto& generator : generators){
        std::cout << "--- " << generator->getGeneratorName() << " ---" <<std::endl;
        std::cout << generator->generateClassCode(myClass) <<std::endl<<std::endl;
    }
    ///////////////

    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();

    return 0;
}
