/*
CppGenerator.hpp
*/

#pragma once

#include "CodeGenerator.hpp"

namespace generator 
{

    class CppGenerator : public CodeGenerator {
    public:
        CppGenerator() {
            class_start_char = " {\n";
            class_end_char = "};\n";  
            line_end_char = ";\n";   
        }
    protected:
        std::string formatClassStart(const std::string& name) const override {
            return "class " + name;
        }

        std::string formatVisibilitySection(const std::string& visibility) const override {
            return visibility + ":\n";
        }

        std::string formatAttribute(const uml::UmlAttribute& attr) const override {
            return attr.type + " " + attr.name;
        }

        std::string formatMethod(const uml::UmlMethod& method) const override {
            std::string methodCode = method.type + " " + method.name + "()";
            // methodCode += " {\n";
            // methodCode += "\t\t// implementation\n";
            // methodCode += "\t}\n";
            return methodCode;
        }

        std::string formatClassEnd() const override {
            return ""; 
        }
    };

} // namespace generator