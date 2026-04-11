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
                uml_class.AddMethod(setterMethod);
            }
        }
    }    

    void UmlRefiner::applyConstructor(UmlClass& uml_class) {
        for (auto attr : uml_class.attributes) {
            if (attr.inConstructor) {
                // add to the Constructor
            }
        }
    }    

} // namespace uml
