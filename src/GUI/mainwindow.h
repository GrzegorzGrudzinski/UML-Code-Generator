#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
// #include <QGraphicsItem>

#include "UmlClassItem.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/// @class MainWindow
/// @brief The main application window acting as the controller for the UML editor.
///
/// This class orchestrates the overall application workflow. It manages the graphical canvas
/// (QGraphicsScene) where users manipulate diagram nodes, captures user input from the 
/// properties side panel (inspector area), handles form updates for attributes/methods, 
/// and routes model extraction to the multilingual code generation subsystem.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Explicit constructor initializing the main editor interface layout.
    /// @param parent Optional pointer to a parent QWidget container.
    explicit MainWindow(QWidget *parent = nullptr);

    /// @brief Destructor that safely disposes of the internal UI object allocations.
    ~MainWindow() override;

private slots:
    /// @brief Scans all elements on the canvas and triggers structural source code generation.
    void handleGenerateClick(); 

    /// @brief Synchronizes property sidebar forms whenever a node is selected or deselected on the canvas.
    void handleSelectionChanged(); 
    
    /// @brief Instantiates and appends a new visual UmlClassItem onto the active canvas environment.
    void handleAddClassOnScene();

    /// @brief Commits name updates from the class text editor form field to the active node entity.
    void handleUpdateClassName();
    
    // --- ATTRIBUTE SLOTS ---

    /// @brief Extracts form inputs to attach a brand-new UmlAttribute to the selected class node.
    void handleAddAttribute();

    /// @brief Erases, populates, and refreshes the items indexed inside the attribute ComboBox drop-down list.
    void refreshAttrList();                 

    /// @brief Populates the form inputs with data matching the chosen attribute selection row index.
    /// @param currentRow The selected attribute selection index inside the dropdown.
    void handleAttrSelection(int currentRow); 

    /// @brief Commits modified field type/name configurations to the active attribute vector location.
    void handleEditAttribute();             

    /// @brief Discards the selected attribute row index from the active class data structure.
    void handleDeleteAttribute();           
    
    // --- METHOD SLOTS ---

    /// @brief Extracts form inputs to attach a brand-new UmlMethod signature to the selected class node.
    void handleAddMethod();

    /// @brief Erases, populates, and refreshes the items indexed inside the method ComboBox drop-down list.
    void refreshMethodList();                 

    /// @brief Populates the form inputs with data matching the chosen method selection row index.
    /// @param currentRow The selected method selection index inside the dropdown.
    void handleMethodSelection(int currentRow); 

    /// @brief Commits modified signature traits and names to the active method vector location.
    void handleEditMethod();             

    /// @brief Discards the selected method row index from the active class data structure.
    void handleDeleteMethod();           
    
private:
    Ui::MainWindow *ui; ///< Pointer containing bound reference objects compiled from the Qt Designer .ui blueprint layout.

    QGraphicsScene *mainScene; ///< The central canvas workspace layout managing interactive graphic nodes and drag actions.

    UmlClassItem* currentSelectedItem = nullptr; ///< Tracks and mirrors a pointer reference to the currently active diagram node selection (nullptr if inactive).
};
#endif // MAINWINDOW_H