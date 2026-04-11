/*
PythonGenerator.hpp
*/

#pragma once

#include "CodeGenerator.hpp"

namespace generator 
{

    class PythonGenerator : public CodeGenerator {
    public:
        PythonGenerator() {
            class_start_char = ":\n";
            class_end_char = "";  
            line_start_char = "    ";   
            line_end_char = "\n";   
        }
    protected:
        std::string formatClassStart(const std::string& name) const override {
            return "class " + name;
        }

        std::string formatVisibilitySection(const std::string& visibility) const override {
            return "";
        }

        std::string formatAttribute(const uml::UmlAttribute& attr) const override {
            return attr.name + ": " + attr.type;
        }

        std::string formatMethod(const uml::UmlMethod& method) const override {
            std::string methodCode = "def " + method.name + "()" + ": " + method.type;
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