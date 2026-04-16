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
            std::string Name = method.isConstructor ? "__init__" : method.name;
            
            std::string methodCode = "def " + Name + "(self";
            
            for (const auto& param : method.parameters) {
                methodCode += ", " + param.name + ": " + param.type;
            }
            methodCode += ")";

            if (!method.isConstructor && !method.type.empty()) {
                std::string retType = (method.type == "void") ? "None" : method.type;
                methodCode += " -> " + retType;
            }

            methodCode += ":\n";
            methodCode += "        pass"; // 8 spacji wcięcia

            return methodCode;
        }

        std::string formatClassEnd() const override {
            return ""; 
        }
    };
} // namespace generator