/*
    UmlRefiner.hpp
*/

#pragma once

#include <string>
#include <utility> // move
#include "UmlClass.hpp"

namespace uml {
    
    /// @class UmlRefiner
    /// @brief A preprocessing component that refines the UML model before code generation.
    ///
    /// This class is responsible for automatically expanding a UmlClass model by inspecting
    /// the configuration flags of its attributes. It programmatically injects boilerplate
    /// methods—such as constructors, getters, and setters—directly into the class definition
    /// so that target-language generators do not need to handle this logic independently.
    class UmlRefiner {
    public:
        /// @brief Inspects attributes and appends public getter/setter methods to the class.
        ///
        /// Iterates through the class attributes. For any attribute with 'generateGetter' 
        /// or 'generateSetter' flagged as true, it automatically generates a public method 
        /// with capitalized naming convention (e.g., 'getName' or 'setName') and appends it 
        /// to the class methods collection. Setters are automatically assigned the appropriate input parameter.
        /// @param uml_class The reference to the UmlClass model to be modified.
        void applyGettersSetters(UmlClass& uml_class);

        /// @brief Generates and appends a parameterized constructor based on attribute traits.
        ///
        /// Scans all attributes within the target class. If any attribute is flagged with 
        /// 'inConstructor' set to true, its type and name are packaged as a method parameter.
        /// If at least one attribute requires initialization, a public constructor method 
        /// matching the class name is injected into the model.
        /// @param uml_class The reference to the UmlClass model to be modified.
        void applyConstructor(UmlClass& uml_class);
    }; 

} // namespace uml