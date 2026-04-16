#include <iostream>
#include <memory> // dla make_unique

#include "UmlClass.hpp"
#include "UmlRefiner.hpp"
#include "CodeGenerator.hpp"

#include "generators/CppGenerator.hpp"
#include "generators/PythonGenerator.hpp"

using namespace uml;

int main() {
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
    std::unique_ptr<generator::CodeGenerator> generator = nullptr;
    generator = std::make_unique<generator::CppGenerator>();
    
    std::string cpp_code = generator->generateClassCode(myClass);
    
    generator = std::make_unique<generator::PythonGenerator>();
    std::string python_code = generator->generateClassCode(myClass);
    
    // 4. Show results (future GUI)
    std::cout << "\n--- GENERATORY ---" <<std::endl<<std::endl;
    
    std::cout << "--- python ---" <<std::endl;
    std::cout<<python_code<<std::endl;
    std::cout << "--- cpp ---" <<std::endl;
    std::cout<<cpp_code<<std::endl;

/*
    std::cout << "\n--- WYGENEROWANY KOD ---" <<std::endl;
    // myClass.GenerateCode();
    std::cout<<"Class"<<'\t';
    std::cout<<myClass.class_name<<std:: endl;
    
    std::cout<<"Attributes"<<std:: endl;
    for (auto attr : myClass.attributes) {
        std::cout<<'\t'<<attr.visibility<<'\t'<<attr.type<<'\t'<<attr.name<<'\n';
    }
    
    std::cout<<"\nMethods"<<std:: endl;
    for (auto method : myClass.methods) {
        std::cout<<'\t'<<method.visibility<<'\t'<<method.type<<'\t'<<method.name<<'\n';
    }
    std::cout<<std:: endl;
*/
    
    return 0;
}
