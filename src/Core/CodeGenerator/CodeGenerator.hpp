/*
CodeGenerator.hpp
*/

#pragma once

#include "UmlClass.hpp"
// #include "UmlRefiner.hpp"

namespace generator
{
    class CodeGenerator {
    public:
        virtual std::string generateClassCode(const uml::UmlClass& uml_class) const = 0;

        virtual ~CodeGenerator() = default;
    };

} // namespace generator
