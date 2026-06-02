#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>

#include "UmlClass.hpp"

/// @class UmlClassItem
/// @brief A graphical component representing a UML class node on the scene canvas.
///
/// This class extends QGraphicsRectItem to provide a draggable and selectable visual box 
/// within the QGraphicsScene workspace. It encapsulates a backend uml::UmlClass entity,
/// and automatically handles dynamic formatting, line separators, and boundary updates
/// whenever structural modifications occur.
class UmlClassItem : public QGraphicsRectItem {
public:
    /// @brief Constructs a graphical representation of a UML class.
    /// @param className The initial default name assigned to the class.
    /// @param parent Optional pointer to a parent QGraphicsItem container.
    UmlClassItem(const std::string& className, QGraphicsItem* parent = nullptr);

    /// @brief Extracts the underlying backend domain logic instance for the code generators.
    /// @return A copy of the encapsulated UmlClass object containing attributes and methods.
    uml::UmlClass getBackendClass() const { return backendClass; }
    
    /// @brief Updates the class identifier name and synchronizes the header text element.
    /// @param newName The new class name string.
    void setClassName(const std::string& newName);

    /// @brief Injects a new attribute record into the backend class and triggers a visual redraw.
    /// @param attr The target UmlAttribute object to append.
    void addAttribute(const uml::UmlAttribute& attr);

    /// @brief Modifies an existing attribute configuration at a specified index slot.
    /// @param index The sequence tracking position within the attribute collection vector.
    /// @param newAttr The updated attribute data structure.
    void updateAttribute(int index, const uml::UmlAttribute& newAttr);

    /// @brief Removes an attribute from the data container and triggers a layout rebuild.
    /// @param index The sequence tracking position of the target attribute to delete.
    void removeAttribute(int index);

    /// @brief Injects a new method definition into the backend class and triggers a visual redraw.
    /// @param method The target UmlMethod object containing operation traits to append.
    void addMethod(const uml::UmlMethod& method);

    /// @brief Modifies an existing method signature blueprint at a specified index slot.
    /// @param index The sequence tracking position within the method collection vector.
    /// @param newMethod The updated method configuration structure.
    void updateMethod(int index, const uml::UmlMethod& newMethod);

    /// @brief Removes a method function from the data container and triggers a layout rebuild.
    /// @param index The sequence tracking position of the target method to delete.
    void removeMethod(int index);

private:
    uml::UmlClass backendClass; ///< The localized logic data layer instance mapped to this UI block.
    
    QGraphicsTextItem* titleText;   ///< Visual text layer rendering the bold header component of the class name.
    QGraphicsTextItem* contentText; ///< Visual text layer compounding sequenced list blocks of fields and operations.

    /// @brief Evaluates current field/operation configurations, formats string rows, and expands the rect size dynamically.
    void updateVisuals(); // updates the screen
};