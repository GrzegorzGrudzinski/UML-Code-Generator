#include "UmlClass.hpp"
#include "UmlAttribute.hpp"
#include "UmlMethod.hpp"   

#include <string>
#include <vector>
#include <utility> // move


namespace uml {            
    void UmlClass::AddAttribute(const UmlAttribute& attr) {
        attributes.push_back(attr);
    }
    void UmlClass::AddMethod(const UmlMethod& method) {
        methods.push_back(method);
    }
    std::string UmlClass::GetName() const{
        return class_name;
    }
}