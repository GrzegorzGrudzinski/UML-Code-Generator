/*
    UmlRefiner.hpp
*/

#pragma once

#include <string>
#include <utility> // move
#include "UmlClass.hpp"

namespace uml {
    
    class UmlRefiner {
    public:
        void applyGettersSetters(UmlClass& uml_class);
        void applyConstructor(UmlClass& uml_class);
    }; 

}