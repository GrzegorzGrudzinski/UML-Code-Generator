/*
CodeGenerator.hpp
*/

#pragma once

#include <map>
#include <vector>

#include "UmlClass.hpp"
// #include "UmlRefiner.hpp"

namespace generator
{
    /// @class CodeGenerator
    /// @brief Abstract base class providing a framework for target-language code generation.
    ///
    /// This class implements the Template Method design pattern. The public method
    /// generateClassCode() outlines the structural skeleton of how a UML class diagram 
    /// component is translated into actual text code. Specific syntax formatting tokens 
    /// and formatting functions are deferred to derived subclasses (e.g., CppGenerator, PythonGenerator).
    class CodeGenerator {
    public:
        /// @brief Orchestrates the code generation algorithm for a given UML class.
        ///
        /// Groups class members by their visibility tier and processes them sequentially
        /// using the private order configuration. It coordinates calls to structural hooks
        /// to assemble the complete text output.
        /// @param uml_class The refined target UML class containing attributes and methods to generate.
        /// @return A complete text block representing the generated code in the target language.
        std::string generateClassCode(const uml::UmlClass& uml_class) const;

        /// @brief Returns the identifier token of the target programming language.
        /// @return The language name string (e.g., "cpp", "python").
        std::string getGeneratorName() const;
        
        /// @brief Virtual destructor ensuring safe polymorphic cleanups of derived generators.
        virtual ~CodeGenerator() = default;

    protected:
        std::string _lang = "generic"; ///< Identifier name of the generator's target language.

        std::string class_start_char = "\n"; ///< Character(s) appended immediately after the class opening declaration.
        std::string class_end_char = "\n";   ///< Character(s) appended immediately after the class body layout terminates.
        
        std::string line_start_char = "    "; ///< Default token string used for line indentation blocks.
        std::string line_end_char = "\n";     ///< Character(s) representing field line termination statements.
        
        /// @brief Hook method to format the introductory class definition keyword and identifier.
        /// @param name The name of the target class.
        /// @return Formatted class introduction string.
        virtual std::string formatClassStart(const std::string& name) const = 0;

        /// @brief Hook method to format target-language scope/visibility blocks if required.
        /// @param visibility The access string tier ("public", "private", "protected").
        /// @return Formatted visibility label block or empty if unsupported by the target syntax.
        virtual std::string formatVisibilitySection(const std::string& visibility) const = 0;

        /// @brief Hook method to format an individual member variable signature.
        /// @param attr Data object representing a single field's metadata.
        /// @return Formatted single line attribute declaration text.
        virtual std::string formatAttribute(const uml::UmlAttribute& attr) const = 0;

        /// @brief Hook method to format an individual member function or initializer method block.
        /// @param method Data object containing parameters, traits, and names for a single operation.
        /// @return Formatted code block representing the complete method signature and a default body wrapper.
        virtual std::string formatMethod(const uml::UmlMethod& method) const = 0;

        /// @brief Hook method to handle custom finalization blocks inside the class syntax scope.
        /// @return Structural tail string or empty if unused.
        virtual std::string formatClassEnd() const = 0;

    private:
        std::vector<std::string> order = {"private", "protected", "public"}; ///< Internal prioritization sequence for class member visibility layout rendering.
      
    };

} // namespace generator