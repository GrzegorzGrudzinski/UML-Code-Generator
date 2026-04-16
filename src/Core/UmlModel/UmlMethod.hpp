/*
UmlMethod.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <utility> // move

namespace uml {
    struct UmlParameter
    {
        std::string type;
        std::string name;

        UmlParameter(std::string t, std::string n)
            : type(std::move(t)), name(std::move(n)) {}
    };
    

    class UmlMethod {
    public:
        std::string visibility;
        std::string type;
        std::string name;
        
        bool isConstructor = false; 
        bool isStatic = false;
        bool isAbstract = false;
        std::vector<UmlParameter> parameters;
        
        UmlMethod(std::string v, std::string s, std::string n)
            : visibility(std::move(v)), type(std::move(s)), name(std::move(n)) {}
        // void Add
    };
}