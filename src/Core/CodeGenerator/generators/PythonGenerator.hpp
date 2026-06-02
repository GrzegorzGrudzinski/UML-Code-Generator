/*
PythonGenerator.hpp
*/

#pragma once

#include "CodeGenerator.hpp"

namespace generator 
{

    /// @class PythonGenerator
    /// @brief A concrete code generator implementation for the Python language.
    ///
    /// This class overrides the structural formatting hooks defined in CodeGenerator
    /// to output PEP 8 compliant Python class definitions. It automatically handles
    /// Python-specific features such as the 'self' parameter, mapping constructors to '__init__',
    /// type hints, and suppressing explicit visibility sections.
    class PythonGenerator : public CodeGenerator {
    public:
        /// @brief Default constructor initializing Python specific syntax tokens.
        ///
        /// Sets up the class header delimiter (colons), disables trailing end characters,
        /// and configures the default indentation level to 4 spaces according to PEP 8.
        PythonGenerator() {
            _lang = "python";

            class_start_char = ":\n";
            class_end_char = "";  
            line_start_char = "    ";   
            line_end_char = "\n";   
        }
    protected:
        /// @brief Formats the beginning of a Python class declaration.
        /// @param name The name of the class to declaration.
        /// @return A string formatted as "class Name".
        std::string formatClassStart(const std::string& name) const override {
            return "class " + name;
        }

        /// @brief Formats a visibility modifier section.
        /// @param visibility The target visibility access level.
        /// @return An empty string, since Python does not use bracketed visibility blocks (like public:/private:).
        std::string formatVisibilitySection(const std::string& visibility) const override {
            return "";
        }

        /// @brief Formats a Python attribute line using type hinting notation.
        /// @param attr The UmlAttribute object containing the name and type.
        /// @return A string formatted as "name: type".
        std::string formatAttribute(const uml::UmlAttribute& attr) const override {
            return attr.name + ": " + attr.type;
        }

        /// @brief Formats a Python method definition with type hints and a default body.
        ///
        /// Automatically remaps methods flagged as constructors to Python's built-in `__init__` method.
        /// It explicitly prepends the mandatory `self` argument, appends input parameter type hints,
        /// formats return type annotations (converting `void` to `None`), and appends a default `pass` statement.
        /// @param method The UmlMethod object containing signature and parameter data.
        /// @return A fully formatted multiline Python method block.
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

        /// @brief Hook method for handling specific trailing class structures.
        /// @return An empty string, as Python relies purely on indentation blocks to close scopes.
        std::string formatClassEnd() const override {
            return ""; 
        }
    };
} // namespace generator