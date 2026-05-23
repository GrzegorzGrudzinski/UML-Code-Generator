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
    class CodeGenerator {
    public:
        std::string generateClassCode(const uml::UmlClass& uml_class) const;
        std::string getGeneratorName() const;
        
        virtual ~CodeGenerator() = default;

    protected:
        std::string _lang = "generic";

        std::string class_start_char = "\n";
        std::string class_end_char = "\n";
        
        std::string line_start_char = "\t";
        std::string line_end_char = "\n";
        
        virtual std::string formatClassStart(const std::string& name) const = 0;
        virtual std::string formatVisibilitySection(const std::string& visibility) const = 0;
        virtual std::string formatAttribute(const uml::UmlAttribute& attr) const = 0;
        virtual std::string formatMethod(const uml::UmlMethod& method) const = 0;
        virtual std::string formatClassEnd() const = 0;
    private:
        std::vector<std::string> order = {"private", "protected", "public"};
      
    };

} // namespace generator
