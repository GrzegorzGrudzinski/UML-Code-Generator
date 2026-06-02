/*
UmlMethod.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <utility> // move

namespace uml {
    
    /// @struct UmlParameter
    /// @brief Represents a single parameter inside a UML method signature.
    ///
    /// This structure couples a type and a name together, representing an argument
    /// that can be passed into a class method or initializer function.
    struct UmlParameter
    {
        std::string type; ///< The data type of the parameter (e.g., "int", "std::string").
        std::string name; ///< The identifier name of the parameter (e.g., "index", "data").

        /// @brief Constructor to initialize a method parameter with a type and name.
        /// @param t The parameter type.
        /// @param n The parameter name.
        UmlParameter(std::string t, std::string n)
            : type(std::move(t)), name(std::move(n)) {}
    };
    

    /// @class UmlMethod
    /// @brief A class representing a UML method (member function) model.
    ///
    /// This class stores all critical structural metadata for a single operation belonging
    /// to a UML class, including visibility, return type, name, input arguments, and behavioral 
    /// modifiers (like static or abstract traits).
    class UmlMethod {
    public:
        std::string visibility; ///< Access modifier of the method ("public", "private", "protected").
        std::string type;       ///< Return type of the method (e.g., "void", "int"). Left empty for constructors.
        std::string name;       ///< The identifier name of the method.
        
        bool isConstructor = false; ///< True if this method serves as the class constructor/initializer.
        bool isStatic = false;      ///< True if this is a static/class-level method.
        bool isAbstract = false;    ///< True if this is a pure virtual or abstract method blueprint.
        std::vector<UmlParameter> parameters; ///< List of input arguments/parameters accepted by the method.
        
        /// @brief Constructor to initialize a UML method signature.
        /// @param v Initial access visibility tier.
        /// @param s Return type designation (can be empty for constructors).
        /// @param n The functional name of the operation.
        UmlMethod(std::string v, std::string s, std::string n)
            : visibility(std::move(v)), type(std::move(s)), name(std::move(n)) {}
        // void Add
    };
} // namespace uml