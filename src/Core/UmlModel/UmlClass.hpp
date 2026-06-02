/*
UmlClass.hpp
*/

#pragma once

#include <string>
#include <vector>

#include "UmlAttribute.hpp"
#include "UmlMethod.hpp"   

namespace uml {

/// @class UmlClass
/// @brief A class representing a UML class model in the backend data structure.
///
/// This class holds the core state of a single UML diagram node, including its name,
/// list of fields (attributes), and list of operations (methods). It serves as the
/// primary input for the structural code generators.
class UmlClass {
private:
public:
    std::string class_name; ///< The name of the UML class (e.g., "Vehicle").
    std::vector<UmlAttribute> attributes; ///< Collection of all attributes (member variables) belonging to the class.
    std::vector<UmlMethod> methods; ///< Collection of all methods (member functions) belonging to the class.
    
    /// @brief Explicit constructor to initialize a UML class with a given name.
    /// @param name The initial name of the UML class.
    explicit UmlClass(std::string name) : class_name(std::move(name)) {}
    
    /// @brief Appends a new attribute to the class definition.
    /// @param attr The UmlAttribute object containing type, name, and visibility data.
    void AddAttribute(const UmlAttribute& attr);
    
    /// @brief Appends a new method to the class definition.
    /// @param method The UmlMethod object containing signature and parameter data.
    void AddMethod(const UmlMethod& method);
    
    /// @brief Retrieves the current name of the UML class.
    /// @return The class name as a std::string.
    std::string GetName() const;
    
};             
    
} // namespace uml