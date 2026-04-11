/*
CodeGenerator.cpp
*/

#include "CodeGenerator.hpp"


std::string generator::CodeGenerator::
generateClassCode(const uml::UmlClass& uml_class) const {
    std::string code = "";

    // group attributes and methods by visibility type
    std::map<std::string, std::vector<uml::UmlAttribute>> groupedAttributes;
    std::map<std::string, std::vector<uml::UmlMethod>> groupedMethods;

    for (const auto& attr : uml_class.attributes) {
        groupedAttributes[attr.visibility].push_back(attr);
    }
    for (const auto& method : uml_class.methods) {
        groupedMethods[method.visibility].push_back(method);
    }

    ////

    code += formatClassStart(uml_class.class_name) + class_start_char;

    // class body
    for (const auto& vis : order) {
        bool hasAttrs = groupedAttributes.count(vis) > 0;
        bool hasMethods = groupedMethods.count(vis) > 0;
        if (!hasAttrs && !hasMethods) continue;
        
        code += formatVisibilitySection(vis);

        if (hasAttrs) {
            for (const auto& attr : groupedAttributes.at(vis)) {
                code += line_start_char + formatAttribute(attr) + line_end_char;
            }
        }
        if (hasMethods) {
            for (const auto& method : groupedMethods.at(vis)) {
                code += line_start_char + formatMethod(method) + line_end_char;
            }
        }

        code += "\n";
    }

    // for (const auto& attr : uml_class.attributes) {
    //     code += formatAttribute(attr);
    // }
    // for (const auto& method : uml_class.methods) {
    //     code += formatMethod(method);
    // }

    code += formatClassEnd() + class_end_char;

    return code;
};


