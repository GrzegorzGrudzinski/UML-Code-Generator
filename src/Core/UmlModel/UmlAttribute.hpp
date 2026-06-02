/*
    UmlAttribute.hpp
*/

#pragma once

#include <string>
#include <utility> // move


namespace uml {
    
    /// @class UmlAttribute
    /// @brief A class representing an attribute of a UML class.
    class UmlAttribute {
    public:
        std::string visibility; ///< Attribute visibility (e.g., public, private)
        std::string type;   ///<  Attribute type.
        std::string name;   ///<  Attribute name
        
        bool inConstructor  = false; ///< Flag specifying if the attribute should be in a constructor
        bool generateGetter = false; ///< Flag specifying if a getter should be generated for the attribute.
        bool generateSetter = false; ///< Flag specifying if a setter should be generated for the attribute.

        /// @brief attributes constructor
        /// @param visibility 
        /// @param type 
        /// @param name 
        UmlAttribute(std::string visibility, std::string type, std::string name)
            : visibility(std::move(visibility)), type(std::move(type)), name(std::move(name)) {}
    };
}

