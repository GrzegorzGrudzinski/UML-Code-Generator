/*
    UmlAttribute.hpp
*/

#pragma once

#include <string>
#include <utility> // move

namespace uml {
    class UmlAttribute {
    public:
        std::string visibility;
        std::string type;
        std::string name;
        
        bool inConstructor = false;
        bool generateGetter = false;
        bool generateSetter = false;

        UmlAttribute(std::string visibility, std::string type, std::string name)
            : visibility(std::move(visibility)), type(std::move(type)), name(std::move(name)) {}
    };
}

