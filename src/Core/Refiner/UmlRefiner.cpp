/*
    UmlRefiner.cpp
*/

#include "UmlRefiner.hpp"
#include "UmlMethod.hpp"


namespace uml
{
    void UmlRefiner::applyGettersSetters(UmlClass& uml_class) {
        for (auto attr : uml_class.attributes) {
            if (attr.name.empty()) {
                continue;
            }
            
            // name format: get/set + Name + ()
            std::string capitalizedName = attr.name;
            capitalizedName[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(capitalizedName[0])));

            if (attr.generateGetter) {
            // generate Getter function
                UmlMethod getterMethod("public", attr.type, ("get" + capitalizedName ) );
                uml_class.AddMethod(getterMethod);
            }
            if (attr.generateSetter) {
                // generate Setter function
                UmlMethod setterMethod("public", "void", ("set" + capitalizedName ) );
                // add parameters

                setterMethod.parameters.push_back({attr.type, attr.name});

                uml_class.AddMethod(setterMethod);
            }
        }
    }    

    void UmlRefiner::applyConstructor(UmlClass& uml_class) {
        UmlMethod constructor("public", "", uml_class.class_name);
        constructor.isConstructor = true;
        bool hasParameters = false;
        
        for (auto attr : uml_class.attributes) {
            if (attr.inConstructor) {
                constructor.parameters.push_back({attr.type, attr.name});
                hasParameters = true;
            }
        }
        if (hasParameters) {
            uml_class.AddMethod(constructor);
        }
    }    

} // namespace uml
