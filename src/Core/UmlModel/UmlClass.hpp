/*
UmlClass.hpp
*/

#pragma once

#include <string>
#include <vector>

#include "UmlAttribute.hpp"
#include "UmlMethod.hpp"   

namespace uml {

class UmlClass {
private:
public:
    std::string class_name;
    std::vector<UmlAttribute> attributes;
    std::vector<UmlMethod> methods;
    
    explicit UmlClass(std::string name) : class_name(std::move(name)) {}
    void AddAttribute(const UmlAttribute& attr);
    void AddMethod(const UmlMethod& method);
    std::string GetName() const;
    
};             
    
} // namespace uml