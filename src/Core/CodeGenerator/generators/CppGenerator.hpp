/*
    CppGenerator.hpp
*/

#pragma once

#include "CodeGenerator.hpp"

namespace generator 
{

    /// @class CppGenerator
    /// @brief A concrete code generator implementation for the C++ language.
    ///
    /// This class overrides the structural formatting hooks defined in CodeGenerator
    /// to output fully compliant C++ class definitions, including visibility labels,
    /// standard member layouts, and default inline method blocks.
    class CppGenerator : public CodeGenerator {
    public:
        /// @brief Default constructor initializing C++ specific syntax tokens.
        ///
        /// Sets up brace layouts, semicolons for line endings, and identifies
        /// this generator with the language code "cpp".
        CppGenerator() {
            _lang = "cpp";

            class_start_char = " {\n";
            class_end_char = "};\n";  
            line_end_char = ";\n";   
        }
        
    protected:
        /// @brief Formats the beginning of a C++ class declaration.
        /// @param name The name of the class to declaration.
        /// @return A string formatted as "class Name".
        std::string formatClassStart(const std::string& name) const override {
            return "class " + name;
        }

        /// @brief Formats a C++ visibility modifier label section.
        /// @param visibility The target visibility access level ("public", "private", "protected").
        /// @return A string formatted as "visibility:\n".
        std::string formatVisibilitySection(const std::string& visibility) const override {
            return visibility + ":\n";
        }

        /// @brief Formats a C++ member variable attribute line.
        /// @param attr The UmlAttribute object containing type and name.
        /// @return A string formatted as "Type Name".
        std::string formatAttribute(const uml::UmlAttribute& attr) const override {
            return attr.type + " " + attr.name;
        }

        /// @brief Formats a C++ member function method signature with a dummy body implementation.
        ///
        /// Correctly suppresses return types if the target method is flagged as a constructor,
        /// and automatically processes the internal list of parameters into a comma-separated signature list.
        /// @param method The UmlMethod object containing parameters, name, and attributes.
        /// @return A fully formatted inline C++ method block string.
        std::string formatMethod(const uml::UmlMethod& method) const override {
            // std::string methodCode = (method.type.empty() ? "" : method.type + " ") + method.name + "()";
            std::string methodCode = "";

            if (!method.isConstructor && !method.type.empty()) {
               methodCode += method.type + " ";
            }
            methodCode += method.name + "(";

            bool first = true;
            for (const auto& param : method.parameters) {
                if (!first) {
                   methodCode += ", ";
                }
                methodCode += param.type + " " + param.name;
                first = false;
            }
            methodCode += ")";
            methodCode += " {\n";
            methodCode += "        // implementation\n";
            methodCode += "    }";

            return methodCode;
        }

        /// @brief Hook method for handling specific trailing class structures.
        /// @return An empty string, since C++ closing tokens are entirely handled by class_end_char.
        std::string formatClassEnd() const override {
            return ""; 
        }

    };

} // namespace generator