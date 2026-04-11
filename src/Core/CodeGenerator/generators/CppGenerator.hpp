/*
CppGenerator.hpp
*/

#pragma once

#include "CodeGenerator.hpp"

namespace generator 
{

    class CppGenerator : public CodeGenerator {
    public:
        std::string generateClassCode(const uml::UmlClass& uml_class) const override {
            std::string code = "class " + uml_class.class_name + " {\n";
            // ... (tutaj Twoja pętla for po atrybutach i metodach dla C++) ...
            code += "};\n";
            return code;
        }
    };

} // namespace generator