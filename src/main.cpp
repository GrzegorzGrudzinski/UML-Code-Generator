#include <iostream>
#include <memory> // dla make_unique

#include "UmlClass.hpp"
#include "UmlRefiner.hpp"
#include "CodeGenerator.hpp"

#include "generators/CppGenerator.hpp"
#include "generators/PythonGenerator.hpp"

using namespace uml;

int main() {
    // 1. Użytkownik "rysuje" klasę
    UmlClass myClass("moja_klasa");

    UmlAttribute attribute("public", "int", "moja_zmienna");
    attribute.generateGetter = true;
    attribute.generateSetter = true;
    attribute.inConstructor = true;

    myClass.AddAttribute(attribute);

    // 2. Aplikacja przygotowuje klasę
    UmlRefiner refiner;
    refiner.applyGettersSetters(myClass);
    


    // 3. Aplikacja generuje kod
    std::cout << "\n--- GENERATOR ---" <<std::endl;
    
    std::unique_ptr<generator::CodeGenerator> generator = nullptr;
    generator = std::make_unique<generator::CppGenerator>();

    std::string code = generator->generateClassCode(myClass);
    std::cout<<code<<std::endl;
    
    generator = std::make_unique<generator::PythonGenerator>();
    code = generator->generateClassCode(myClass);
    std::cout<<code<<std::endl;


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
    
    return 0;
}



// class CodeGenerator {
// // void GenerateCode() {
// //     cout<<"class "<<GetName()<<" {\n";
// //     cout<<"private: \n";
// //     for (const UMLAttribute attribute : attributes) {
// //         cout<<'\t'<<attribute.type<<" "<<attribute.name<<"\n";
// //     }   
// //     cout<<"}\n";
// // }
// };

